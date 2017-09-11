#include <TinyGPS++.h>
TinyGPSPlus gps;
uint16_t cnt = 0;
void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  Serial1.println("$D TEstGPS V0.1 awesome DM Project");
  Serial3.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  char data;
  // Serial11.println("Loop:");
  while (Serial3.available()) {
    data = Serial3.read();
    gps.encode(data);
    Serial1.print(data);
  }
  cnt = cnt + 1;
  if (cnt > 10000) {
    cnt = 0;
    displayInfo();
  }
}

void displayInfo() {
  Serial1.print(F("Location: "));
  if (gps.location.isValid()) {
    Serial1.print(gps.location.lat(), 6);
    Serial1.print(F(","));
    Serial1.print(gps.location.lng(), 6);
  } else {
    Serial1.print(F("INVALID"));
  }

  Serial1.print(F("  Date/Time: "));
  if (gps.date.isValid()) {
    Serial1.print(gps.date.month());
    Serial1.print(F("/"));
    Serial1.print(gps.date.day());
    Serial1.print(F("/"));
    Serial1.print(gps.date.year());
  } else {
    Serial1.print(F("INVALID"));
  }

  Serial1.print(F(" "));
  if (gps.time.isValid()) {
    if (gps.time.hour() < 10)
      Serial1.print(F("0"));
    Serial1.print(gps.time.hour());
    Serial1.print(F(":"));
    if (gps.time.minute() < 10)
      Serial1.print(F("0"));
    Serial1.print(gps.time.minute());
    Serial1.print(F(":"));
    if (gps.time.second() < 10)
      Serial1.print(F("0"));
    Serial1.print(gps.time.second());
    Serial1.print(F("."));
    if (gps.time.centisecond() < 10)
      Serial1.print(F("0"));
    Serial1.print(gps.time.centisecond());
  } else {
    Serial1.print(F("INVALID"));
  }

  Serial1.println();
}
