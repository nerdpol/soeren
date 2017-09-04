struct ringbuf {
	uint8_t buffer[64];
	uint8_t * head;
	uint8_t * tail;
};

struct radio {
	HardwareSerial * serial;
	int mode_pin;
	struct ringbuf buffer;
} radio;

void radio_setup(HardwareSerial * serial, int mode_pin, int initial_baud) {
	// SET pin is low active, so set high for data mode
	radio.serial = serial;
	radio.mode_pin = mode_pin;
	pinMode(mode_pin, OUTPUT);
	digitalWrite(mode_pin, HIGH);
	delay(100);
	serial->begin(initial_baud);
	ringbuf_init(&radio.buffer);
}

void radio_configure_baud(int baud) {
}

void radio_update(void (*handle)(union packet *)) {
	while (radio.serial->available() > 0) {
		uint8_t buf[sizeof(radio.buffer.buffer)];
		int buf_bytes = radio.serial->readBytes(buf, sizeof(buf));
		ringbuf_put_many(&radio.buffer, buf, buf_bytes);
		decode(&radio.buffer, handle);
	}
}

void radio_write(void const * buf, size_t len) {
	radio.serial->write(buf, len);
	uint8_t checksum = 0;
	for (size_t i = 0; i < len; ++i) {
		checksum ^= ((uint8_t *)buf)[i];
	}
	radio.serial->write(checksum);
}

void radio_debug(char const * msg) {
	size_t msg_len = strlen(msg);

	for (size_t i = 0; i < msg_len; i += 16) {
		size_t segment_len = min(16, msg_len - i);

		union packet pkt;
		pkt.tag = PKT_DEBUG;
		memset(&pkt.debug.message[segment_len], 0, 16 - segment_len);
		memcpy(&pkt.debug.message, &msg[i], segment_len);
		radio_write(&pkt, sizeof(pkt.debug));
	}
}
