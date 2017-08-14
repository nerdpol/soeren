// SCL  B6
// SDA  B7
// TX3  PB10
// RX3  PB11

#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

void setup() {
  Serial3.begin(9600);
  ina219.begin();
  while (!Serial3);
}

char buf[80];

void loop() {
  float u = ina219.getBusVoltage_V();
  float i = ina219.getCurrent_mA();

  Serial.print("\n");
  bar(36, 0.f, 12.5f, u);
  Serial.print(" ");
  bar(36, 0.f, 1000.f, i);
  Serial3.println("");

  snprintf(buf, 79, " u=% 3.2f V                           i=% 3.2f mA\n", u, i);
  Serial3.print(buf);
  Serial.print("\n");

  delay(500);
}

void bar(int width, float min, float max, float value) {
  float r = (value - min) / (max - min);
  int w = (int)(width * r);
  Serial3.print("[");
  for (int i=0; i<width-2; ++i) {
    Serial3.print(i <= w ? '#' : '-');
  }
  Serial3.print("]");
}

