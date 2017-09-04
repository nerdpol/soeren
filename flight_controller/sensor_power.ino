#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

void power_setup() {
	ina219.begin();
}

void power_update() {
	flightcontrol_sensors.voltage = ina219.getBusVoltage_V();
	flightcontrol_sensors.current = ina219.getCurrent_mA() / 1000.f;
}
