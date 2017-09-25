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
      Comment Franz: Fullscalerange ist +- 6V man sollte 5V an I2c anstecken!
*/
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads(0x48);
float Voltage = 0.0;

#include "includes.h"
#include "radio_packet.h"
#include <Wire.h>
#define looplength 100

#define pcf8574_adress 0x27

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

ads.begin();

}


void loop() {


 int16_t adc0;  // we read from the ADC, we have a sixteen bit integer as a result

  adc0 = ads.readADC_SingleEnded(0);
  Voltage = (adc0 * 0.1875)/1000;
  
  Serial.print("AIN0: "); 
  Serial.print(adc0);
  Serial.print("\tVoltage: ");
  Serial.println(Voltage, 7);  
  Serial.println();
 delay(1000);
  adc0 = ads.readADC_SingleEnded(1);
  Voltage = (adc0 * 0.1875)/1000;
  
  Serial.print("AIN1: "); 
  Serial.print(adc0);
  Serial.print("\tVoltage: ");
  Serial.println(Voltage, 7);  
  Serial.println();
   delay(1000);
 adc0 = ads.readADC_SingleEnded(2);
  Voltage = (adc0 * 0.1875)/1000;
   Serial.print("AIN2: "); 
  Serial.print(adc0);
  Serial.print("\tVoltage: ");
  Serial.println(Voltage, 7);  
  Serial.println();
   delay(1000);
   adc0 = ads.readADC_SingleEnded(3);
  Voltage = (adc0 * 0.1875)/1000;
  Serial.print("AIN3: "); 
  Serial.print(adc0);
  Serial.print("\tVoltage: ");
  Serial.println(Voltage, 7);  
  Serial.println();
  
  delay(1000);
  Serial.println("All on ");
  IOexpanderWrite(pcf8574_adress, 0xFF);
  delay(10000);

   Serial.println("All off ");
 IOexpanderWrite(pcf8574_adress, 0x00);


}
void IOexpanderWrite(byte address, byte _data ) 
{
 Wire.beginTransmission(address);
 Wire.write(_data);
 Wire.endTransmission(); 
}


