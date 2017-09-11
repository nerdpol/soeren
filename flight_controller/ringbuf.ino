#include <stddef.h>
#include <stdint.h>

void ringbuf_init(struct ringbuf *rngbf) {
  rngbf->head = rngbf->buffer;
  rngbf->tail = rngbf->buffer;
}

size_t ringbuf_data(struct ringbuf *rngbf) {
  if (rngbf->head > rngbf->tail)
    return sizeof(rngbf->buffer) - (rngbf->head - rngbf->tail) - 1;
  else
    return rngbf->tail - rngbf->head;
}

size_t ringbuf_space(struct ringbuf *rngbf) {
  return sizeof(rngbf->buffer) - ringbuf_data(rngbf);
}

uint8_t *ringbuf_ptr(struct ringbuf *rngbf, uint8_t *p, size_t advance) {
  return rngbf->buffer + (p - rngbf->buffer + advance) % sizeof(rngbf->buffer);
}

size_t ringbuf_put(struct ringbuf *rngbf, uint8_t c) {
  if (ringbuf_space(rngbf) > 0) {
    *rngbf->tail = c;
    rngbf->tail = ringbuf_ptr(rngbf, rngbf->tail, 1);
    return 1;
  }
  return 0;
}

size_t ringbuf_put_many(
    struct ringbuf *rngbf, uint8_t const *buf, size_t count) {
  size_t original_count = count;
  if (rngbf->head <= rngbf->tail) { // write to the space between tail and end
    size_t writing =
        min(count, rngbf->buffer + sizeof(rngbf->buffer) - rngbf->tail);
    memcpy(rngbf->tail, buf, writing);
    rngbf->tail = ringbuf_ptr(rngbf, rngbf->tail, writing);
    buf += writing;
    count -= writing;
    // count is 0 or head is start
  }
  if (count > 0) { // write between head and tail
    size_t writing = min(count, rngbf->head - rngbf->tail);
    memcpy(rngbf->tail, buf, writing);
    rngbf->tail = ringbuf_ptr(rngbf, rngbf->tail, writing);
    count -= writing;
  }
  return original_count - count;
}

uint8_t ringbuf_peek(struct ringbuf *rngbf) { return *rngbf->head; }

int ringbuf_get(struct ringbuf *rngbf, uint8_t *c) {
  if (ringbuf_data(rngbf) > 0) {
    *c = *rngbf->head;
    rngbf->head = ringbuf_ptr(rngbf, rngbf->head, 1);
    return 1;
  }
  return 0;
}
