

/*
 * SCL =B6
 * SDA=B7
 * 
 * TX1=A9
 * RX1=A10
 * 
 * TX3=PB10
 * RX3= PB11
 * Servo1=PA0
 * Servo2=PA1
 * Servo3=PA2
 * Servo4=PA3
 * Servo5=PA6
 * 
 * For switching between GyroMeters / ADO Port
 * To overcome problem of same I2C Adress
 * Enable/Disable_Gyro1=PA11
 * Enable/Disable_Gyro2=PA15
 * 
 * weiter PWM
 * PA7
 * PB0
 * PB1
 * 
 * Transceiver SET
 * PA12
 * 
 * SPI for SD-Card
 * NSS2 = PB12
 * SCK2 = PB13
 * MISO2= PB14
 * MOSI2= PB15
 */
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_INA219.h>
#include <TinyGPS++.h>
Adafruit_INA219 ina219;
TinyGPSPlus gps;
// Nur für 9AxisSensor
#define    MPU9250_ADDRESS            0x68
#define    MAG_ADDRESS                0x0C

#define    GYRO_FULL_SCALE_250_DPS    0x00
#define    GYRO_FULL_SCALE_500_DPS    0x08
#define    GYRO_FULL_SCALE_1000_DPS   0x10
#define    GYRO_FULL_SCALE_2000_DPS   0x18

#define    ACC_FULL_SCALE_2_G        0x00
#define    ACC_FULL_SCALE_4_G        0x08
#define    ACC_FULL_SCALE_8_G        0x10
#define    ACC_FULL_SCALE_16_G       0x18
//Ende nur für 9AxisSensor
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

#include <Servo.h>
Servo s1;
Servo s2;
Servo s3;
Servo s4;
Servo s5;

struct ringbuf {
  uint8_t buffer[64];
  uint8_t * head;
  uint8_t * tail;
};
struct ringbuf protocol_buffer;

#define looplength 100
//#define debug 1

uint8_t tele_cnt = 0;
unsigned long time;
//Prozessabbild

struct control_sensor_struct {
  uint16_t pres;
  uint16_t acc[3];
  uint16_t mag[3];
  uint16_t gyr[3];
  float temp;
  float amp;
  float volt;
};



typedef control_sensor_struct flightcontrol_sensors_t;
flightcontrol_sensors_t flightcontrol_sensors;


uint8_t servos[5]; // c.....P
int16_t acc[3];
int16_t gyro[3];
int16_t mag[3];
uint16_t akku_v, akku_i;
uint16_t pres_s, pres_d;
uint16_t lidar;

// the setup function runs once when you press reset or power the board
void setup() {  
  Serial1.begin(115200);
  Serial1.println("$D Flightcontroler V0.1 awesome DM Project");
  Serial3.begin(9600);
  
  pinMode(13, OUTPUT);
  ringbuf_init(&protocol_buffer);
           
  s1.attach(PA0);
  s2.attach(PA1);
  s3.attach(PA2);
  s4.attach(PA3);
  s5.attach(PA6);

  s1.write(90);
  s2.write(90);
  s3.write(90);
  s4.write(90);
  s5.write(90);
  for (uint8_t cnt = 0; cnt < 5; cnt++)
  {
    servos[cnt] = 90;
  }

  setup_pres_temp();
  ina219.begin(); //setup_volt_amp
  setup_9axis();
  time = millis() + looplength;

}

void loop() {
  readSerial1();
  byte data;
 while (Serial3.available())
 {
       data=Serial3.read();
      gps.encode(data);
      //Serial1.print((char) data);
      
 }
 
  if (millis() > time)
  {
    //Hier passiert die Regelung irgendwann!
    sendTelemetry();
    time = time + looplength;
  }


}
