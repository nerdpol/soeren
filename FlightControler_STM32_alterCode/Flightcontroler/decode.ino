#include <stdint.h>

static inline int16_t be16toh(int16_t x) {
  return __builtin_bswap16(x);
}

static inline uint16_t be16touh(uint16_t x) {
  return __builtin_bswap16(x);
}

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

