/*
 * Arduino:
 *   Board: Generic STM32F103C series
 *   Variant: STM32F103C8 (20k RAM, 64k Flash)
 *   GPU Speed: 72 MHz
 *   Upload: STLink
 * Modifications:
 *   Board File: don't use USB as serial
 *      Arduino/hardware/Arduino_STM32/STM32F1/boards.txt:394
 *      genericSTM32F103C.menu.upload_method.STLinkMethod.build.upload_flags=-DCONFIG_MAPLE_MINI_NO_DISABLE_DEBUG=1 -DGENERIC_BOOTLOADER
 *   Adafruit PWM Servos Library requires WIRE to be defined to Wire, not Wire1
 *      Arduino/libraries/Adafruit_PWM_Servo_Driver_Library/Adafruit_PWMServoDriver.cpp:27
 *      #define WIRE Wire
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

#define CALL_SIGN {'\r', '\n', 'D', 'F', '0', 'H', 'S', 'A', '-', '1', '\r', '\n'}
#define HEARTBEAT_ID 0x01
#define HEARTBEAT_TIMEOUT 2500

#include "protocol.h"
#include "regler.h"
#include <Wire.h>
#define looplength 100

typedef struct {
  uint16_t accel[3];
  uint16_t mag[3];
  uint16_t gyro[3];
  float quat[4];

  uint16_t pressure;
  float temperature;

  float latitude;
  float longitude;
  uint16_t altitude;
  uint8_t links;
  float yaw;
  float velocity;

  float current;
  float voltage;

  float bat_temp_in;
  float bat_temp_out;
} flightcontrol_sensors_t;
flightcontrol_sensors_t flightcontrol_sensors;

regler_param_t params_reg_pitch = {
  .w =-20,              //-20 Grad Neigung der Flugzeugnase 
  .x =0,
  .Kp =100,
  .Ki =0,
  .Kd =0,
  .esum =0,
  .ealt =0,
};

unsigned long time;

void setup() {
  Wire.begin();

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
  radio_debug("\tRudder servos...");
  rudders_setup();
  radio_debug(" done.\n");
  
  radio_debug("\tGPS...");
  gps_setup(&Serial2);
  radio_debug(" done.\n");

  radio_debug("\tAtmospheric sensors...");
  atmosphere_setup();
  radio_debug(" done.\n");

  radio_debug("\tOrientation sensor...");
  orientation_setup();
  radio_debug(" done.\n");
  
  radio_debug("\tIO Expander...");
  ioexpander_setup(0x27);
  radio_debug(" done.\n");

  radio_debug("Initialization Complete.\n");

  radio_debug("\n\"Look at you, soaring through the air without a care in the "
              "world. Like an eagle. PILOTING A BLIMP!\" - GLaDOS\n");

  time = millis() + looplength;  
}

enum {
  TELEM_FLIGHT = 1,
  TELEM_MAG = 2,
  TELEM_ATMOSPHERE = 4,
  TELEM_POWER = 8,
  TELEM_GPS = 16,
};

void send_telemetry(unsigned telemetry) {
  if (telemetry & TELEM_FLIGHT) {
    telemetry_send_accel();
    telemetry_send_gyro();
  }
  if (telemetry & TELEM_MAG) telemetry_send_mag();
  if (telemetry & TELEM_ATMOSPHERE) telemetry_send_atmosphere();
  if (telemetry & TELEM_POWER) telemetry_send_power();
  if (telemetry & TELEM_GPS) telemetry_send_gps();
}

void handle_packet(union packet *packet) {
  switch (packet->tag) {
  /*case PKT_CONTROL: {
    rudders_update(packet->control.control);
    send_telemetry(~0ul);
    time = millis() + looplength;
  } break; */
  default:
    break;
  }
}

unsigned next_telemetry_flags = ~0ul;
#define PERIOD_TELEMETRY 100
long next_telemetry_update = 0;
#define PERIOD_ORIENTATION 100
long next_orientation_update = 0;
#define PERIOD_ORIENTATION 500
long next_power_update = 0;
#define PERIOD_ATMOSPHERE 500
long next_atmosphere_update = 0;
#define PERIOD_RADIO 50
long next_radio_update = 0;
#define PERIOD_GPS 50
long next_gps_update = 0;
#define PERIOD_HEARTBEAT 1000
long next_heartbeat = 0;

#define PERIOD_REG_PITCH 1000
long next_reg_pitch = 0;
long last_reg_pitch = 0;

void loop() {
  long now = millis();
  //Serial.print("loop="); Serial.println(now);
  // read radio very often for smooth response
  //if (now > next_radio_update) {
  //  next_radio_update = now + PERIOD_RADIO;
    radio_update(&handle_packet);
  //}

  // read gps very often to avoid a buffer overflow (buffer is smaller than complete GPS message)
  //if (now > next_gps_update) {
  //  next_gps_update = now + PERIOD_GPS;
    if (gps_update()) {
      next_telemetry_flags |= TELEM_GPS;
    }
  //}

  if (now > next_heartbeat) {
    //TODO: toggle heartbeat pin
    next_heartbeat = now + PERIOD_HEARTBEAT;
  }

  if (now > next_reg_pitch) {
    next_reg_pitch = now + PERIOD_REG_PITCH;
    last_reg_pitch = next_reg_pitch;
    int16_t tmp = regler_fnc(&params_reg_pitch, next_reg_pitch-last_reg_pitch );
    last_reg_pitch = next_reg_pitch;
  }

  if (now > next_orientation_update) {
    //Serial.print("orientation="); Serial.println(now);
    next_orientation_update = now + PERIOD_ORIENTATION;
    orientation_update();
    next_telemetry_flags |= TELEM_FLIGHT | TELEM_MAG;
  }

  if (now > next_atmosphere_update) {
    //Serial.print("atmo="); Serial.println(now);
    next_atmosphere_update = now + PERIOD_ATMOSPHERE;
   atmosphere_update();
    next_telemetry_flags |= TELEM_ATMOSPHERE;
  }

  if (now > next_power_update) {
    //Serial.print("pwr="); Serial.println(now);
    next_power_update = now + PERIOD_ORIENTATION;
    //power_update();
    next_telemetry_flags |= TELEM_POWER;

    if (flightcontrol_sensors.voltage < 11.0) {
      radio_debug("WARNING low voltage\n");
    }
  }

  if (next_telemetry_flags && now > next_telemetry_update) {
    //Serial.print("telem="); Serial.println(now);
    next_telemetry_update = now + PERIOD_TELEMETRY;

    send_telemetry(next_telemetry_flags);
    next_telemetry_flags = 0;
  }
}

