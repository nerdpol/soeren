/*
   ATTN: Change the board settings to disable USB
   genericSTM32F103C.menu.upload_method.STLinkMethod.build.upload_flags=-DCONFIG_MAPLE_MINI_NO_DISABLE_DEBUG=1 -DGENERIC_BOOTLOADER

   I2C
      SCL   B6
      SDA   B7

   HC-12 (UART1)
      TX   A9 (TX1)
      RX   A10 (RX1)
      SET  A12

   GPS (UART3)
      TX  B10 (TX3)
      RX  B11 (RX2)

   Servos
      Servo1  A0
      Servo2  A1
      Servo3  A2
      Servo4  A3
      Servo5  A6

   For switching between GyroMeters / ADO Port
   To overcome problem of same I2C Adress
      Enable/Disable_Gyro1  A11
      Enable/Disable_Gyro2  A15

   weiter PWM
      A7
      B0
      B1

   SPI for SD-Card (SPI2
      NSS2    B12 (NSS2)
      SCK2    B13 (SCK2)
      MISO2   B14 (MISO2)
      MOSI2   B15 (MOSI2)
      CS      A15
      INT     B5
*/

#include "includes.h"
#include "radio_packet.h"
#include <Wire.h>
#define looplength 100
unsigned int calibrationData[7];
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
int16_t mag_bias[3] = {0, 0, 0}, mag_scale[3] = {0, 0, 0};
void setup() {
  radio_setup(&Serial, PA12, 115200);
  radio_configure_baud(115200);
  radio_configure_channel(5);
  radio_debug("SOEREN - Self On Earth Returning Experimental Navigator\n");
  radio_debug("Radio check:\n");
  radio_debug("\t115200 Baud.\n");
  // radio_configure_baud(9600);
  // radio_debug("\t9600 Baud.\n");
  // radio_configure_baud(115200);
  radio_debug("Radio check complete.\n");
  delay(1000);

  Serial.println("Starte setup");
Wire.begin();

}


void loop() {

byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }

  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  } else {
    Serial.println("done\n");
  }

  delay(5000);



}


