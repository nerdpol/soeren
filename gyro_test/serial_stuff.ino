void readSerial1() {
	while (radio_serial->available() > 0) {
		ringbuf_put(&protocol_buffer, radio_serial->read());
		decode(&protocol_buffer, &handle);
	}
}

void printP() {
	
	resetTeleChecksum();
	writeTeleData('P');
	int16_t tmp = (int16_t)(flightcontrol_sensors.amp * 1000);
	writeTeleData(tmp >> 8);
	writeTeleData(tmp & 0xff);
	tmp = (int16_t)(flightcontrol_sensors.volt * 1000);
	writeTeleData(tmp >> 8);
	writeTeleData(tmp & 0xff);
	writeTeleChecksum();
  update_volt_amp();
}

void printM() {
	
	resetTeleChecksum();
	writeTeleData('M');
	writeTeleData(flightcontrol_sensors.mag[0] >> 8);
	writeTeleData(flightcontrol_sensors.mag[0] & 0xff);
	writeTeleData(flightcontrol_sensors.mag[1] >> 8);
	writeTeleData(flightcontrol_sensors.mag[1] & 0xff);
	writeTeleData(flightcontrol_sensors.mag[2] >> 8);
	writeTeleData(flightcontrol_sensors.mag[2] & 0xff);
	writeTeleChecksum();
  update_mag();
}

void printTP() {
	
	resetTeleChecksum();
	writeTeleData('T');
	writeTeleData(flightcontrol_sensors.pres >> 8);
	writeTeleData(flightcontrol_sensors.pres & 0xff);
	int16_t tmp = (int16_t)(flightcontrol_sensors.temp * 10.0);
	writeTeleData(tmp >> 8);
	writeTeleData(tmp & 0xff);
	writeTeleChecksum();
  update_pres_temp();
}

void printG() {
	// G lat s32bit long s32 alt u16 links u8 yan s16/100 grad, velocity u16 cm/s
	uint16_t tmp;
	resetTeleChecksum();
	writeTeleData('G');

	union {
		float f;
		uint32_t u;
	} fu;

	fu.f = gps.location.lat();
	writeTeleData(fu.u >> 24);
	writeTeleData(fu.u >> 16 & 0xff);
	writeTeleData(fu.u >> 8 & 0xff);
	writeTeleData(fu.u & 0xff);

	fu.f = gps.location.lng();
	writeTeleData(fu.u >> 24);
	writeTeleData(fu.u >> 16 & 0xff);
	writeTeleData(fu.u >> 8 & 0xff);
	writeTeleData(fu.u & 0xff);

	tmp = (uint16_t)gps.altitude.meters();
	writeTeleData(tmp >> 8 & 0xff);
	writeTeleData(tmp & 0xff);

	writeTeleData((uint8_t) gps.satellites.value());

	tmp = (uint16_t)(gps.course.deg() * 100);
	writeTeleData(tmp >> 8 & 0xff);
	writeTeleData(tmp & 0xff);

	tmp = (uint16_t)(gps.speed.mps( ) *100);
	writeTeleData(tmp >> 8 & 0xff);
	writeTeleData(tmp & 0xff);
	writeTeleChecksum();
}

void printF() {
	
	resetTeleChecksum();
	writeTeleData('F');
	// Gyro
	writeTeleData(flightcontrol_sensors.gyr[0] >> 8);
	writeTeleData(flightcontrol_sensors.gyr[0] & 0xff);
	writeTeleData(flightcontrol_sensors.gyr[1] >> 8);
	writeTeleData(flightcontrol_sensors.gyr[1] & 0xff);
	writeTeleData(flightcontrol_sensors.gyr[2] >> 8);
	writeTeleData(flightcontrol_sensors.gyr[2] & 0xff);
	// Accelerometer
	writeTeleData(flightcontrol_sensors.acc[0] >> 8);
	writeTeleData(flightcontrol_sensors.acc[0] & 0xff);
	writeTeleData(flightcontrol_sensors.acc[1] >> 8);
	writeTeleData(flightcontrol_sensors.acc[1] & 0xff);
	writeTeleData(flightcontrol_sensors.acc[2] >> 8);
	writeTeleData(flightcontrol_sensors.acc[2] & 0xff);
	writeTeleChecksum();
  update_gyr_acc();
}

uint8_t checksumdata = 0;
void resetTeleChecksum() {
	checksumdata = 0;
}

void writeTeleData(uint8_t data) {
	checksumdata = checksumdata ^ data;
	radio_serial->write(data);
}

void writeTeleChecksum() {
	radio_serial->write(checksumdata);
	checksumdata = 0;
}

void sendTelemetry() {
	static uint8_t tele_cnt = 0;
if (tele_cnt == 2 || tele_cnt == 4 || tele_cnt == 6 || tele_cnt == 8|| tele_cnt == 10 || tele_cnt == 12 || tele_cnt == 14 || tele_cnt == 0  ) {
 printF();
}

	if (tele_cnt == 3 ) {
    printP();
  }
  if (tele_cnt == 9 ) {
    printTP();
  }
 if (tele_cnt == 11 ) {
    printG();
  }
  
	if (tele_cnt == 1 || tele_cnt == 7 ) {
		printM();
	}
	if (tele_cnt >= 15) {

		tele_cnt = 0;
	}

	tele_cnt++;
}

void radio_resetTXBaud_115200b(void){
  digitalWrite(PA12,LOW);
  delay(100);
  radio_serial->begin(2400);
  radio_serial->print("AT+B115200"); 
  delay(300);
  radio_serial->begin(9600);
  radio_serial->print("AT+B115200");
  delay(400);
  radio_serial->begin(38400);
  radio_serial->print("AT+B115200"); 
  delay(300);
  radio_serial->begin(115200);
  radio_serial->print("AT+B115200"); 
    delay(300);
   digitalWrite(PA12,HIGH);
  radio_serial->begin(115200);
delay(300);
  radio_change_channel(4);
  delay(300);
  
}

void radio_changeTXBaud_115200b(void){
  digitalWrite(PA12,LOW);
  delay(100);
  //radio_serial->begin(9600);
  radio_serial->print("AT+B115200");
  delay(100);
  digitalWrite(PA12,HIGH);
  radio_serial->begin(115200);
}


void radio_changeTXBaud_38400b(void){
  digitalWrite(PA12,LOW);
  //radio_serial->begin(115200);
  delay(100);
  radio_serial->print("AT+B38400");
  delay(100);
  digitalWrite(PA12,HIGH);
  radio_serial->begin(38400);
}

void radio_changeTXBaud_9600b(void){
  digitalWrite(PA12,LOW);
  delay(100);
  radio_serial->println("AT+B9600");
   delay(100);
   radio_serial->begin(9600);
  digitalWrite(PA12,HIGH);
}

void radio_changeTXBaud_2400b(void){
  digitalWrite(PA12,LOW);
  delay(100);
  radio_serial->println("AT+B2400");
  delay(100);
  digitalWrite(PA12,HIGH);
  radio_serial->begin(2400);
}
void radio_change_channel(uint8_t ch){
  if (ch>100){
    radio_serial->print("$D Channel to large");
  return;
  }
  
  digitalWrite(PA12,LOW);
  delay(100);
  radio_serial->print("AT+C0");
  if (ch<10)
  {
    radio_serial->print('0');
  }
  radio_serial->print(ch,DEC);
   delay(300);
    digitalWrite(PA12,HIGH);
}

