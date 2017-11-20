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

  uint8_t val[8] = {127, 127, 127, 127, 127};
  rudders_update(val);
  delay(200);
}

void rudders_update(uint8_t * values) { //8 Werte als uint8_t
  for (uint8_t cnt = 0; cnt < 8; cnt++) {
    if (servos.values[cnt] != values[cnt])
    {
      servos.values[cnt] = values[cnt];
      setServo(cnt, servos.values[cnt]);
    }
  }
}

void setServo(uint8_t ch, uint8_t pos)
{
  uint32_t res = (SERVOMAX - SERVOMIN) * pos  / 256;
  pwm.setPWM(ch, 0, (res + SERVOMIN));
}
