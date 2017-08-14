void readSerial1() {
	while (Serial1.available() > 0) {
		ringbuf_put(&protocol_buffer, Serial1.read());
		decode(&protocol_buffer, &handle);
	}
}

void printP() {
	update_volt_amp();
	resetTeleChecksum();
	writeTeleData('P');
	int16_t tmp = (int16_t)(flightcontrol_sensors.amp * 1000);
	writeTeleData(tmp >> 8);
	writeTeleData(tmp & 0xff);
	tmp = (int16_t)(flightcontrol_sensors.volt * 1000);
	writeTeleData(tmp >> 8);
	writeTeleData(tmp & 0xff);
	writeTeleChecksum();
}

void printM() {
	update_mag();
	resetTeleChecksum();
	writeTeleData('M');
	writeTeleData(flightcontrol_sensors.mag[0] >> 8);
	writeTeleData(flightcontrol_sensors.mag[0] & 0xff);
	writeTeleData(flightcontrol_sensors.mag[1] >> 8);
	writeTeleData(flightcontrol_sensors.mag[1] & 0xff);
	writeTeleData(flightcontrol_sensors.mag[2] >> 8);
	writeTeleData(flightcontrol_sensors.mag[2] & 0xff);
	writeTeleChecksum();
}

void printTP() {
	update_pres_temp();
	resetTeleChecksum();
	writeTeleData('T');
	writeTeleData(flightcontrol_sensors.pres >> 8);
	writeTeleData(flightcontrol_sensors.pres & 0xff);
	int16_t tmp = (int16_t)(flightcontrol_sensors.temp * 10.0);
	writeTeleData(tmp >> 8);
	writeTeleData(tmp & 0xff);
	writeTeleChecksum();
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
	update_gyr_acc();
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
}

uint8_t checksumdata = 0;
void resetTeleChecksum() {
	checksumdata = 0;
}

void writeTeleData(uint8_t data) {
	checksumdata = checksumdata ^ data;
	Serial1.write(data);
}

void writeTeleChecksum() {
	Serial1.write(checksumdata);
	checksumdata = 0;
}

void sendTelemetry() {
	static uint8_t tele_cnt = 0;

	printF();

	if (tele_cnt == 5 || tele_cnt == 10 ) {
		printM();
	}
	if (tele_cnt >= 16) {
		printP();
		printTP();
		printG();
		tele_cnt = 0;
	}

	tele_cnt++;
}
