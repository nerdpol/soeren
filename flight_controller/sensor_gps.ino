#include <TinyGPS++.h>

struct {
  TinyGPSPlus parser;
  HardwareSerial * serial;
} gps;

void gps_setup(HardwareSerial * serial) {
  gps.serial = serial;
  gps.serial->begin(9600);
}

int gps_update() {
  int ret = 0;
  while (gps.serial->available()) {
    if (gps.parser.encode(gps.serial->read())) {
      flightcontrol_sensors.latitude = gps.parser.location.lat();
      flightcontrol_sensors.longitude = gps.parser.location.lng();
      flightcontrol_sensors.altitude = (uint16_t)gps.parser.altitude.meters();
      flightcontrol_sensors.links = (uint8_t)gps.parser.satellites.value();
      flightcontrol_sensors.yaw = gps.parser.course.deg();
      flightcontrol_sensors.velocity = gps.parser.speed.mps();
      ret = 1;
    }
  }
  return ret;
}
