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
    size_t packet_size = radio_packet_size(next);

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
    // not a packet: drop a byte and try again.
    data_size--;
    buf->head = ringbuf_ptr(buf, buf->head, 1);
  }
}

void telemetry_send_accel() {
  union packet packet;
  packet.tag = PKT_ACCEL;
  packet.accel.accel[0] = s16_hton(flightcontrol_sensors.accel[0]);
  packet.accel.accel[1] = s16_hton(flightcontrol_sensors.accel[1]);
  packet.accel.accel[2] = s16_hton(flightcontrol_sensors.accel[2]);
  radio_write(&packet, sizeof(packet.accel));
}

void telemetry_send_battery() {
  union packet packet;
  packet.tag = PKT_BATTERY;
  //TODO
  radio_write(&packet, sizeof(packet.battery));
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

void telemetry_send_mag() {
  union packet packet;
  packet.tag = PKT_MAG;
  packet.mag.mag[0] = s16_hton(flightcontrol_sensors.mag[0]);
  packet.mag.mag[1] = s16_hton(flightcontrol_sensors.mag[1]);
  packet.mag.mag[2] = s16_hton(flightcontrol_sensors.mag[2]);
  radio_write(&packet, sizeof(packet.mag));
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

void telemetry_send_quat() {
  union packet packet;
  packet.tag = PKT_QUAT;
  packet.quat.quat[0] = flightcontrol_sensors.quat[0];
  packet.quat.quat[1] = flightcontrol_sensors.quat[1];
  packet.quat.quat[2] = flightcontrol_sensors.quat[2];
  packet.quat.quat[3] = flightcontrol_sensors.quat[3];
  radio_write(&packet, sizeof(packet.quat));
}

void telemetry_send_radio() {
  //TODO
}

void telemetry_send_status() {
  //TODO
}

void telemetry_send_atmosphere() {
  union packet packet;
  packet.tag = PKT_ATMOSPHERE;
  packet.atmosphere.pressure = u16_hton(flightcontrol_sensors.pressure);
  packet.atmosphere.temperature =
      s16_hton((int16_t)(flightcontrol_sensors.temperature * 10.0));
  radio_write(&packet, sizeof(packet.atmosphere));
}

void telemetry_send_gyro() {
  union packet packet;
  packet.tag = PKT_GYRO;
  packet.gyro.gyro[0] = s16_hton(flightcontrol_sensors.gyro[0]);
  packet.gyro.gyro[1] = s16_hton(flightcontrol_sensors.gyro[1]);
  packet.gyro.gyro[2] = s16_hton(flightcontrol_sensors.gyro[2]);
  radio_write(&packet, sizeof(packet.gyro));
}
