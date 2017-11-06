struct ringbuf {
  uint8_t buffer[64];
  uint8_t *head;
  uint8_t *tail;
};

struct radio {
  HardwareSerial *serial;
  int mode_pin;
  long last_baud;
  struct ringbuf buffer;
} radio;

void radio_setup(HardwareSerial *serial, int mode_pin, long initial_baud) {
  // SET pin is low active, so set high for data mode
  radio.serial = serial;
  radio.mode_pin = mode_pin;
  radio.last_baud = initial_baud;
  pinMode(mode_pin, OUTPUT);
  digitalWrite(mode_pin, HIGH);
  delay(100);
  serial->begin(initial_baud);
  serial->setTimeout(0);
  ringbuf_init(&radio.buffer);
}

void radio_configure_baud(int baud) {
  if (!(baud == 115200 || baud == 9600 || baud == 2400 || baud == 38400)) {
    radio_debug("ILLBD");
    return;
  }
  char buf[16];
  sprintf(buf, "AT+B%u\0", baud);
  digitalWrite(radio.mode_pin, LOW);
  delay(300);
  radio.serial->begin(2400);
  radio.serial->print(buf);
  delay(300);
  radio.serial->begin(9600);
  radio.serial->print(buf);
  delay(300);
  radio.serial->begin(38400);
  radio.serial->print(buf);
  delay(300);
  radio.serial->begin(115200);
  radio.serial->print(buf);
  delay(300);
  digitalWrite(radio.mode_pin, HIGH);
  radio.last_baud = baud;
}

void radio_configure_channel(int ch) {
  if (ch > 100) {
    radio_debug("ILLCH");
    return;
  }

  char buf[16];
  sprintf(buf, "AT+C%03u", ch);

  digitalWrite(radio.mode_pin, LOW);
  radio.serial->begin(9600);
  delay(200);
  radio.serial->print(buf);
  delay(200);
  radio.serial->begin(radio.last_baud);
  delay(200);
  radio.serial->print(buf);
  
  digitalWrite(radio.mode_pin, HIGH);
}

void radio_update(void (*handle)(union packet *)) {
  while (radio.serial->available() > 0) {
    uint8_t buf[sizeof(radio.buffer.buffer)];
    int buf_bytes = radio.serial->readBytes(buf, ringbuf_space(&radio.buffer));
    ringbuf_put_many(&radio.buffer, buf, buf_bytes);
    decode(&radio.buffer, handle);
  }
}

void radio_write(void const *buf, size_t len) {
  radio.serial->write(buf, len);
  uint8_t checksum = 0;
  for (size_t i = 0; i < len; ++i) {
    checksum ^= ((uint8_t *)buf)[i];
  }
  radio.serial->write(checksum);
}

void radio_debug(char const *msg) {
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
