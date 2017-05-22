#include <stdint.h>
#include <stddef.h>



void ringbuf_init(struct ringbuf * decoder) {
  decoder->head = decoder->buffer;
  decoder->tail = decoder->buffer;
}

size_t ringbuf_data(struct ringbuf * decoder) {
  if (decoder->head > decoder->tail)
    return sizeof(decoder->buffer) - (decoder->head - decoder->tail) - 1;
  else
    return decoder->tail - decoder->head;
}

size_t ringbuf_space(struct ringbuf * decoder) {
  return sizeof(decoder->buffer) - ringbuf_data(decoder);
}

uint8_t * ringbuf_ptr(struct ringbuf * decoder, uint8_t * p, size_t advance) {
  return decoder->buffer + (p - decoder->buffer + advance) % sizeof(decoder->buffer);
}

void ringbuf_put(struct ringbuf * decoder, uint8_t c) {
  if (ringbuf_space(decoder) > 0) {
    *decoder->tail = c;
    decoder->tail = ringbuf_ptr(decoder, decoder->tail, 1);
  }
}

uint8_t ringbuf_peek(struct ringbuf * decoder) {
  return *decoder->head;
}

int ringbuf_get(struct ringbuf * decoder, uint8_t * c) {
  if (ringbuf_data(decoder) > 0) {
    *c = *decoder->head;
    decoder->head = ringbuf_ptr(decoder, decoder->head, 1);
    return 1;
  }
  return 0;
}

