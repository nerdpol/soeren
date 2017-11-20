#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads(0x48);

void battery_setup() {
	;
}

void battery_update() {
	flightcontrol_sensors.voltage = (ads.readADC_SingleEnded(0) * 0.1875) / 1000;
	flightcontrol_sensors.current = (ads.readADC_SingleEnded(1) * 0.1875) / 1000;
	flightcontrol_sensors.bat_temp_in = (ads.readADC_SingleEnded(2) * 0.1875) / 1000;
	flightcontrol_sensors.bat_temp_out = (ads.readADC_SingleEnded(3) * 0.1875) / 1000;
}
