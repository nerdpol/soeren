#include <stdint.h>

union _conv16 {
  uint16_t u;
  int16_t s;
};

static inline int16_t s16_ntoh(int16_t x) {
  union _conv16 c;
  c.s = x;
  c.u = __builtin_bswap16(c.u);
  return c.s;
}

static inline int16_t s16_hton(int16_t x) {
  union _conv16 c;
  c.s = x;
  c.u = __builtin_bswap16(c.u);
  return c.s;
}

static inline uint16_t u16_ntoh(uint16_t x) {
  return __builtin_bswap16(x);
}

static inline uint16_t u16_hton(uint16_t x) {
  return __builtin_bswap16(x);
}

union _conv32 {
  float f;
  uint32_t u;
};

static inline uint32_t f_hton(float x) {
  union _conv32 c;
  c.f = x;
  return __builtin_bswap32(c.u);
}

static inline float f_ntoh(uint32_t x) {
  union _conv32 c;
  c.u = __builtin_bswap32(c.u);
  return c.f;
}

void decode(struct ringbuf *buf, void (*handle)(union packet *)) {
  size_t data_size = ringbuf_data(buf);
  union packet packet;
  while (data_size > 0) {
    uint8_t next = ringbuf_peek(buf);
    size_t packet_size = 0;
    switch (next) {
    case PKT_MAG:
      packet_size = sizeof(packet.mag);
      break;
    case PKT_FLIGHT:
      packet_size = sizeof(packet.flight);
      break;
    case PKT_POWER:
      packet_size = sizeof(packet.power);
      break;
    case PKT_ATMOSPHERE:
      packet_size = sizeof(packet.atmosphere);
      break;
    case PKT_GPS:
      packet_size = sizeof(packet.gps);
      break;
    case PKT_CONTROL:
      packet_size = sizeof(packet.control);
      break;
    case PKT_REPORT:
      packet_size = 1;
      break;
    case PKT_DEBUG:
      packet_size = sizeof(packet.debug);
      break;
    }
    if (packet_size > 0) {
      // possibly a packet
      if (data_size < packet_size + 1) {
        // not enough data to verify the packet
        return;
      }
      uint8_t checksum = 0;
      for (size_t i = 0; i < packet_size; ++i) {
        checksum ^= packet.bytes[i] = *ringbuf_ptr(buf, buf->head, i);
      }
      uint8_t *checksum_ptr = ringbuf_ptr(buf, buf->head, packet_size);
      if (checksum == *checksum_ptr) {
        // packet is correct - handle and continue parsing
        handle(&packet);
        data_size -= (packet_size + 1);
        buf->head = ringbuf_ptr(buf, buf->head, packet_size + 1);
        continue;
      } else {
        // incorrect checksum - not a packet after all.
      }
    }
    // not a packet

    // drop a byte and try again.
    data_size--;
    buf->head = ringbuf_ptr(buf, buf->head, 1);
  }
}

void telemetry_send_flight() {
  union packet packet;
  packet.tag = PKT_FLIGHT;
  packet.flight.gyr[0] = s16_hton(flightcontrol_sensors.gyr[0]);
  packet.flight.gyr[1] = s16_hton(flightcontrol_sensors.gyr[1]);
  packet.flight.gyr[2] = s16_hton(flightcontrol_sensors.gyr[2]);
  packet.flight.acc[0] = s16_hton(flightcontrol_sensors.acc[0]);
  packet.flight.acc[1] = s16_hton(flightcontrol_sensors.acc[1]);
  packet.flight.acc[2] = s16_hton(flightcontrol_sensors.acc[2]);
  radio_write(&packet, sizeof(packet.flight));
}

void telemetry_send_mag() {
  union packet packet;
  packet.tag = PKT_MAG;
  packet.mag.mag[0] = s16_hton(flightcontrol_sensors.mag[0]);
  packet.mag.mag[1] = s16_hton(flightcontrol_sensors.mag[1]);
  packet.mag.mag[2] = s16_hton(flightcontrol_sensors.mag[2]);
  radio_write(&packet, sizeof(packet.mag));
}

void telemetry_send_atmosphere() {
  union packet packet;
  packet.tag = PKT_ATMOSPHERE;
  packet.atmosphere.pressure = u16_hton(flightcontrol_sensors.pressure);
  packet.atmosphere.temperature =
      s16_hton((int16_t)(flightcontrol_sensors.temperature * 10.0));
  radio_write(&packet, sizeof(packet.atmosphere));
}

void telemetry_send_power() {
  union packet packet;
  packet.tag = PKT_POWER;
  packet.power.current =
      s16_hton((int16_t)(flightcontrol_sensors.current * 1000));
  packet.power.voltage =
      u16_hton((uint16_t)(flightcontrol_sensors.voltage * 1000));
  radio_write(&packet, sizeof(packet.power));
}

void telemetry_send_gps() {
  union packet packet;
  packet.tag = PKT_GPS;
  packet.gps.latitude = f_hton(flightcontrol_sensors.latitude);
  packet.gps.longitude = f_hton(flightcontrol_sensors.longitude);
  packet.gps.altitude = u16_hton(flightcontrol_sensors.altitude);
  packet.gps.links = flightcontrol_sensors.links;
  packet.gps.yaw = u16_hton((uint16_t)(flightcontrol_sensors.yaw * 100));
  packet.gps.velocity =
      u16_hton((uint16_t)(flightcontrol_sensors.velocity * 100));
  radio_write(&packet, sizeof(packet.gps));
}
