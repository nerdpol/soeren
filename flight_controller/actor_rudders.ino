#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  180 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

struct servos {
  uint8_t values[16];
} servos;

void rudders_setup() {
  
  pwm.begin();

  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  uint8_t val[] = {127, 127, 127, 127, 127};
  rudders_update(val);
  delay(200);

/*
  for (uint8_t cnt = 10; cnt < 200; cnt = cnt + 10) {
    uint8_t val[] = {cnt, cnt, cnt, cnt, cnt};
    rudders_update(val);
    delay(100);
    Serial.println(cnt);
  }
  for (uint8_t cnt = 200; cnt > 128; cnt = cnt - 1) {
    uint8_t val[] = {cnt, cnt, cnt, cnt, cnt};
    rudders_update(val);
    delay(10);
    Serial.println(cnt);
  }
  */
}

void rudders_update(uint8_t * values) { //8 Werte als uint8_t
  for (uint8_t cnt = 0; cnt < 5; cnt++) {
    if (servos.values[cnt] != values[cnt])
    {
      servos.values[cnt] = values[cnt];
      //Serial.println("Aenderung!");
      setServo(cnt, servos.values[cnt]);
    }

  }

}

void setServo(uint8_t ch, uint8_t pos)
{
  uint32_t res;
  res = (SERVOMAX - SERVOMIN) * pos  / 256;
  //Serial.print("Debug setServo");
 //,Serial.println(res);
 pwm.setPWM(ch, 0, (res + SERVOMIN));
}

// 
void rudder_neutral()
{
  uint8_t val[] = {127, 127, 127, 127, 127};
  rudders_update(val);
}

typedef struct {
int8_t pitch_trim;
int16_t pitch_p;
int8_t pitch_i;
int16_t pitch_i_past;
uint16_t pitch_i_past_sat;
} pitch_struct;
pitch_struct pitch_t;


void update_pitch_i_past(int8_t val)
{
  pitch_t.pitch_i_past=pitch_t.pitch_i_past+val;
  
  if (pitch_t.pitch_i_past>pitch_t.pitch_i_past_sat){
    pitch_t.pitch_i_past=pitch_t.pitch_i_past_sat;
  }
  if (pitch_t.pitch_i_past<pitch_t.pitch_i_past_sat){
    pitch_t.pitch_i_past=-pitch_t.pitch_i_past_sat;
  }
  
}
void pitch_pi_update(float pitch_ist, float pitch_soll)
{
  //delat in  Grad
  float pitch_delta=pitch_ist-pitch_soll;

  if (pitch_delta>0)
  {
    pitch_t.update_pitch_i_past(pitch_t.pitch_i);
  }
  else
  {
    pitch_t.update_pitch_i_past(-pitch_t.pitch_i);
  }

  float res=pitch_delta*(float)pitch_t.pitch_p/100 +(float)pitch_t.pitch_i_past*0.1 +255;
  //Servo0 elevator
  servos.values[0]=uint8_t(res+pitch_t.pitch_trim );
}

//aileron roll
//Einfluss auf Rudder
//offset int8_t aileron_left_trim
//offset int8_t aileron_right_trim
//

//rudder
//offset int8_t rudder_trim
//





