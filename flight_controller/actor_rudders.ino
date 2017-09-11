#include <Servo.h>

Servo s1;
Servo s2;
Servo s3;
Servo s4;
Servo s5;

void rudders_setup() {
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
}

void rudders_update(
    uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4, uint8_t c5) {
  s1.write(c1);
  s2.write(c2);
  s3.write(c3);
  s4.write(c4);
  s5.write(c5);
}
