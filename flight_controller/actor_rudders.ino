#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  200 // this is the 'minimum' pulse length count (out of 4096)
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

  for (uint8_t cnt = 10; cnt < 200; cnt = cnt + 10) {
    uint8_t val[] = {cnt, cnt, cnt, cnt, cnt};
    rudders_update(val);
    delay(100);
    Serial.println(cnt);
  }
  for (uint8_t cnt = 255; cnt > 127; cnt = cnt - 1) {
    uint8_t val[] = {cnt, cnt, cnt, cnt, cnt};
    rudders_update(val);
    delay(10);
    Serial.println(cnt);
  }
}

void rudders_update(uint8_t * values) { //8 Werte als uint8_t
  Serial.print("\nRudders(");
  Serial.print(values[0]);
  Serial.print(",");
  Serial.print(values[1]);
  Serial.print(",");
  Serial.print(values[2]);
  Serial.print(",");
  Serial.print(values[3]);
  Serial.print(",");
  Serial.print(values[4]);
  Serial.println(")");
  for (uint8_t cnt = 0; cnt < 5; cnt++) {
    if (servos.values[cnt] != values[cnt])
    {
      servos.values[cnt] = values[cnt];
      Serial.println("Aenderung!");
      setServo(cnt, servos.values[cnt]);
    }

  }

}

void setServo(uint8_t ch, uint8_t pos)
{
  uint32_t res;
  res = (SERVOMAX - SERVOMIN) * pos  / 256;
  Serial.print("Debug setServo");
 Serial.println(res);
 pwm.setPWM(ch, 0, (res + SERVOMIN));
}
