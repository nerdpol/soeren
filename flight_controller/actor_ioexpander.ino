#include <Wire.h>

struct ioexpander {
	uint8_t address;
	uint8_t value;
	uint8_t lock;
} ioexpander;

void ioexpander_setup(uint8_t address) {
	ioexpander.address = address;
	ioexpander.value = 0x00;
	ioexpander.lock = 0x00;
	ioexpander_write(ioexpander.value);
}

void ioexpander_bit_set(uint8_t index) {
	uint8_t mask = ((uint8_t)1) << index;
	uint8_t new_value = (ioexpander.value) | mask;
	ioexpander_write(new_value & ~ioexpander.lock | ioexpander.value & ioexpander.lock);
}

void ioexpander_bit_reset(uint8_t index) {
	uint8_t mask = ((uint8_t)1) << index;
	uint8_t new_value = (ioexpander.value) & ~mask;
	ioexpander_write(new_value & ~ioexpander.lock | ioexpander.value & ioexpander.lock);
}

void ioexpander_update(uint8_t mask, uint8_t value) {
	uint8_t new_value = (ioexpander.value & ~mask) | (value & mask);
	ioexpander_write(new_value & ~ioexpander.lock | ioexpander.value & ioexpander.lock);
}

void ioexpander_lock(uint8_t lock) {
	ioexpander.lock |= lock;
}

void ioexpander_unlock(uint8_t unlock) {
	ioexpander.lock &= ~unlock;
}

static inline void ioexpander_write(uint8_t value) {
	Wire.beginTransmission(ioexpander.address);
	Wire.write(ioexpander.value = value);
	Wire.endTransmission(); 
}
