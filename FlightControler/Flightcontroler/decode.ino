#include <stdint.h>

static inline int16_t be16toh(int16_t x) {
  return __builtin_bswap16(x);
}

static inline uint16_t be16touh(uint16_t x) {
  return __builtin_bswap16(x);
}

union __attribute__((packed)) packet {
  uint8_t tag;
  struct __attribute__((packed)) {
    uint8_t tag;
    int16_t mag[3];
  } mag;
  struct __attribute__((packed)) {
    uint8_t tag;
    int16_t gyr[3];
    int16_t acc[3];
  } flight;
  struct __attribute__((packed)) {
    uint8_t tag;
    uint16_t voltage;
    int16_t current;
  } power;
  struct __attribute__((packed)) {
    uint8_t tag;
    int16_t temp;
    uint16_t pressure;
  } atmos;
  struct __attribute__((packed)) {
    uint8_t tag;
    uint8_t control[5];
  } control;
  uint8_t bytes[0];
};

#include <stdio.h>

#ifdef DEBUG
#define dprintf(...) printf("[DEBUG] "__VA_ARGS__)
#else
#define dprintf(...)
#endif

void decode(struct ringbuf * buf, void (*handle)(union packet *)) {
  size_t data_size = ringbuf_data(buf);
  union packet packet;
  while (data_size > 0) {
    uint8_t next = ringbuf_peek(buf);
    size_t packet_size = 0;
    switch (next) {
      case 'M':
        packet_size = sizeof(packet.mag);
        break;
      case 'F':
        packet_size = sizeof(packet.flight);
        break;
      case 'P':
        packet_size = sizeof(packet.power);
        break;
      case 'T':
        packet_size = sizeof(packet.atmos);
        break;
      case 'c':
        packet_size = sizeof(packet.control);
        break;
    }

    if (packet_size > 0) { //possibly a packet
      if (data_size < packet_size + 1) { //not enough data to verify the packet
        return;
      }

      uint8_t checksum = 0;
      for (size_t i=0; i<packet_size; ++i) {
        checksum ^= packet.bytes[i] = *ringbuf_ptr(buf, buf->head, i);
      }
      uint8_t * checksum_ptr = ringbuf_ptr(buf, buf->head, packet_size);
      if (checksum == *checksum_ptr) { //packet is correct - handle and continue parsing
        handle(&packet);
        data_size -= (packet_size + 1);
        buf->head = ringbuf_ptr(buf, buf->head, packet_size + 1);
        continue;
      }
      else { //incorrect checksum - not a packet after all.
      }
    }
    //not a packet

    //drop a byte and try again.
    data_size--;
    buf->head = ringbuf_ptr(buf, buf->head, 1);
  }
}

void handle(union packet * packet) {
  switch (packet->tag) {
    case 'F':
      packet->flight.gyr[0] = be16toh(packet->flight.gyr[0]);
      packet->flight.gyr[1] = be16toh(packet->flight.gyr[1]);
      packet->flight.gyr[2] = be16toh(packet->flight.gyr[2]);
      packet->flight.acc[0] = be16toh(packet->flight.acc[0]);
      packet->flight.acc[1] = be16toh(packet->flight.acc[1]);
      packet->flight.acc[2] = be16toh(packet->flight.acc[2]);
      break;
    case 'M':
      packet->mag.mag[0] = be16toh(packet->mag.mag[0]);
      packet->mag.mag[1] = be16toh(packet->mag.mag[1]);
      packet->mag.mag[2] = be16toh(packet->mag.mag[2]);
      break;
    case 'P':
      packet->power.voltage = be16toh(packet->power.voltage);
      packet->power.current = be16toh(packet->power.current);
      break;
    case 'c':
      break;
    case 'T':
      packet->atmos.temp = be16toh(packet->atmos.temp);
      packet->atmos.pressure = be16toh(packet->atmos.pressure);
      break;
  }

  switch (packet->tag) {
    case 'c':
      s1.write(packet->control.control[0]);
      s2.write(packet->control.control[1]);
      s3.write(packet->control.control[2]);
      s4.write(packet->control.control[3]);
      s5.write(packet->control.control[4]);
      break;
  }
}

