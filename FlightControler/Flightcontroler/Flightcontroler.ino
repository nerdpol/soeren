
#include <Servo.h>
Servo s1;
Servo s2;
Servo s3;
Servo s4;
Servo s5;

#define looplength 100
#define buflen 64
//#define debug 1
char buf[buflen];
uint8_t pbuf = 0;
uint8_t tele_cnt=0;
unsigned long time;
//Prozessabbild

struct control_sensor_struct{ 
  uint16_t pres; 
  uint16_t acc[3]; 
  uint16_t mag[3]; 
  uint16_t gyr[3]; 
  float temp; 
  float amp; 
  float volt; };
typedef control_sensor_struct flightcontrol_sensors_t;
flightcontrol_sensors_t flightcontrol_sensors;

  
uint8_t servos[5];
int16_t acc[3];
int16_t gyro[3];
int16_t mag[3];
uint16_t akku_v,akku_i;
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
  s1.write(90);
  s2.write(90);
  s3.write(90);
  s4.write(90);
  s5.write(0);

  
  time = millis() + looplength;

}

void loop() {
  readSerial();

  if (millis() > time)
  {
    //Hier passiert die Regelung
    s1.write(servos[0]);
    s2.write(servos[1]);
    s3.write(servos[2]);
    s4.write(servos[3]);
    s5.write(servos[4]);
    sendTelemetry();


    time = time + looplength;
  }


}
