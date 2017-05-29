
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

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

#define BUFFER_FAIL     0
#define BUFFER_SUCCESS  1

#define BUFFER_SIZE 20

struct Buffer {
  uint8_t data[BUFFER_SIZE];
  uint8_t read; // zeigt auf das Feld mit dem ältesten Inhalt
  uint8_t write; // zeigt immer auf leeres Feld
} buffer = {{}, 0, 0};


#include <Servo.h>
Servo s1;
Servo s2;
Servo s3;
Servo s4;
Servo s5;

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

struct nvp {
  uint8_t type;
  unsigned int length;
};

#define NODATATYPES 1

struct datatypes_t {
  unsigned int noTypes = NODATATYPES;
  struct nvp types[NODATATYPES] = {{'c',5}};
}datatypes;

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
  Serial.begin(115200);
  Serial.println("$D Flightcontroler V0.1 awesome DM Project");
  pinMode(13, OUTPUT);
  s1.attach(7);
  s2.attach(6);
  s3.attach(5);
  s4.attach(4);
  s5.attach(3);
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
  readSerial();

  if (millis() > time)
  {
    //Hier passiert die Regelung irgendwann!
    s1.write(servos[0]);
    s2.write(servos[1]);
    s3.write(servos[2]);
    s4.write(servos[3]);
    s5.write(servos[4]);
    sendTelemetry();
    time = time + looplength;
  }


}
