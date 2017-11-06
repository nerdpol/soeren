/*
 * ATTN: Change the board settings to disable USB
 * genericSTM32F103C.menu.upload_method.STLinkMethod.build.upload_flags=-DCONFIG_MAPLE_MINI_NO_DISABLE_DEBUG=1 -DGENERIC_BOOTLOADER
 *
 * I2C
 *    SCL   B6
 *    SDA   B7
 *
 * HC-12 (UART1)
 *    TX   A9 (TX1)
 *    RX   A10 (RX1)
 *    SET  A12
 *
 * GPS (UART3)
 *    TX  B10 (TX3)
 *    RX  B11 (RX2)
 *
 * Servos
 *    Servo1  A0
 *    Servo2  A1
 *    Servo3  A2
 *    Servo4  A3
 *    Servo5  A6
 *
 * For switching between GyroMeters / ADO Port
 * To overcome problem of same I2C Adress
 *    Enable/Disable_Gyro1  A11
 *    Enable/Disable_Gyro2  A15
 *
 * weiter PWM
 *    A7
 *    B0
 *    B1
 *
 * SPI for SD-Card (SPI2
 *    NSS2    B12 (NSS2)
 *    SCK2    B13 (SCK2)
 *    MISO2   B14 (MISO2)
 *    MOSI2   B15 (MOSI2)
 *    CS      A15
 *    INT     B5
*/

#include "radio_packet.h"
#include <Wire.h>
#define looplength 100

typedef struct {
  uint16_t pressure;
  uint16_t acc[3];
  uint16_t mag[3];
  uint16_t gyr[3];
  float temperature;
  float current;
  float voltage;
  float latitude;
  float longitude;
  uint16_t altitude;
  uint8_t links;
  float yaw;
  float velocity;
} flightcontrol_sensors_t;
flightcontrol_sensors_t flightcontrol_sensors;

unsigned long time;

void setup() {
  radio_setup(&Serial, PA12, 115200);
  radio_configure_baud(115200);
  radio_configure_channel(4);
  radio_debug("SOEREN - Self On Earth Returning Experimental Navigator\n");
  radio_debug("Radio check:\n");
  radio_debug("\t115200 Baud.\n");
  // radio_configure_baud(9600);
  // radio_debug("\t9600 Baud.\n");
  // radio_configure_baud(115200);
  radio_debug("Radio check complete.\n");

  radio_debug("Initializing:\n");
  Wire.begin();
  radio_debug("\tRudder servos...");
  rudders_setup();
  radio_debug(" done.\n");
  
  radio_debug("\tGPS...");
  gps_setup(&Serial2);
  radio_debug(" done.\n");

  radio_debug("\tAtmospheric sensors...");
  atmosphere_setup();
  radio_debug(" done.\n");
/*
  radio_debug("\tPower sensor...");
  power_setup();
  radio_debug(" done.\n");
*/
  radio_debug("\tOrientation sensor...");
  orientation_setup();
  radio_debug(" done.\n");
  
 
  
  radio_debug("Initialization Complete.\n");

  radio_debug("\n\"Look at you, soaring through the air without a care in the "
              "world. Like an eagle. PILOTING A BLIMP!\" - GLaDOS\n");

  time = millis() + looplength;
}

void send_report() {
  char info[512];
  snprintf(info, 256, "REPORT{gyr=(%hu %hu %hu), acc=(%hu %hu %hu), mag=(%hu "
                      "%hu %hu), temp=%f, pres=%hu, volt=%f, cur=%f, gps={lat=%f, lng=%f, alt=%hu, lnk=%u, yaw=%f, vel=%f}}\n",
      flightcontrol_sensors.gyr[0], flightcontrol_sensors.gyr[1],
      flightcontrol_sensors.gyr[2], flightcontrol_sensors.acc[0],
      flightcontrol_sensors.acc[1], flightcontrol_sensors.acc[2],
      flightcontrol_sensors.mag[0], flightcontrol_sensors.mag[1],
      flightcontrol_sensors.mag[2], flightcontrol_sensors.temperature,
      flightcontrol_sensors.pressure, flightcontrol_sensors.voltage,
      flightcontrol_sensors.current, flightcontrol_sensors.latitude,
      flightcontrol_sensors.longitude, flightcontrol_sensors.altitude,
      flightcontrol_sensors.links, flightcontrol_sensors.yaw,
      flightcontrol_sensors.velocity);
  radio_debug(info);
}

enum {
  TELEM_FLIGHT = 1,
  TELEM_MAG = 2,
  TELEM_ATMOSPHERE = 4,
  TELEM_POWER = 8,
  TELEM_GPS = 16,
};

void send_telemetry(unsigned telemetry) {
  if (telemetry & TELEM_FLIGHT) telemetry_send_flight();
  if (telemetry & TELEM_MAG) telemetry_send_mag();
  if (telemetry & TELEM_ATMOSPHERE) telemetry_send_atmosphere();
  if (telemetry & TELEM_POWER) telemetry_send_power();
  if (telemetry & TELEM_GPS) telemetry_send_gps();
}

void handle_packet(union packet *packet) {
  switch (packet->tag) {
  case PKT_CONTROL:
    rudders_update(packet->control.control);
    send_telemetry(~0ul);
    time = millis() + looplength;
    break;
  case PKT_REPORT: {
    send_report();
  } break;
  default:
    break;
  }
}

uint8_t tick = 0;

unsigned next_telemetry_flags = ~0ul;
long next_telemetry_update = 0;
long next_orientation_update = 0;
long next_power_update = 0;
long next_atmosphere_update = 0;
long next_radio_update = 0;
long next_gps_update = 0;

void loop() {
  long now = millis();
  //Serial.print("loop="); Serial.println(now);
  // read radio very often for smooth response
  //if (now > next_radio_update) {
  //  next_radio_update = now + 50;
    radio_update(&handle_packet);
  //}

  // read gps very often to avoid a buffer overflow (buffer is smaller than complete GPS message)
  //if (now > next_gps_update) {
  //  next_gps_update = now + 50;
    if (gps_update()) {
      next_telemetry_flags |= TELEM_GPS;
    }
  //}

  if (now > next_orientation_update) {
    //Serial.print("orientation="); Serial.println(now);
    next_orientation_update = now + 100;
    orientation_update();
    next_telemetry_flags |= TELEM_FLIGHT | TELEM_MAG;
  }

  if (now > next_atmosphere_update) {
    //Serial.print("atmo="); Serial.println(now);
    next_atmosphere_update = now + 500;
   atmosphere_update();
    next_telemetry_flags |= TELEM_ATMOSPHERE;
  }

  if (now > next_power_update) {
    //Serial.print("pwr="); Serial.println(now);
    next_power_update = now + 500;
    //power_update();
    next_telemetry_flags |= TELEM_POWER;

    if (flightcontrol_sensors.voltage < 11.0) {
      radio_debug("WARNING low voltage\n");
    }
  }

  if (next_telemetry_flags && now > next_telemetry_update) {
    //Serial.print("telem="); Serial.println(now);
    next_telemetry_update = now + 100;

    send_telemetry(next_telemetry_flags);
    next_telemetry_flags = 0;
  }
}
