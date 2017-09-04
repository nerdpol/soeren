#include <TinyGPS++.h>

TinyGPSPlus gps;

void gps_setup() {
	Serial3.begin(9600);
}

void gps_update() {
	while (Serial3.available()) {
		gps.encode(Serial3.read());
	}
	if (gps.location.isUpdated()) {
		flightcontrol_sensors.latitude = gps.location.lat();
		flightcontrol_sensors.longitude = gps.location.lng();
	}
	if (gps.altitude.isUpdated()) {
		flightcontrol_sensors.altitude = (uint16_t)gps.altitude.meters();
	}
	if (gps.satellites.isUpdated()) {
		flightcontrol_sensors.links = (uint8_t)gps.satellites.value();
	}
	if (gps.course.isUpdated()) {
		flightcontrol_sensors.yaw = gps.course.deg();
	}
	if (gps.speed.isUpdated()) {
		flightcontrol_sensors.velocity = gps.speed.mps();
	}
}
