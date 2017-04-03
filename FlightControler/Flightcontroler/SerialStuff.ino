
void clearbuf() {
  for (uint8_t cnt = 0; cnt < buflen; cnt++)
  {
    buf[cnt] = 0;
  }
  pbuf = 0;
}

void parseSerial()
{
  if (buf[0] != '$')
  {
    clearbuf();
    return;
  }

  switch (buf[1]) {
    case 'c': 
    for (uint8_t cnt=0;cnt<5;cnt++)
    {
      servos[cnt]=buf[cnt+2];
      #ifdef debug
      Serial.println("$D Servos update");
      #endif
    }
    
    break;
    
  }

clearbuf();
}

void readSerial()
{
  //Sind Daten verfügbar?
  if (Serial.available() > 0)
  {
    buf[pbuf] = Serial.read();
    if (buf[pbuf] == '\n')
    {
      parseSerial();
      clearbuf();
      return;
    }
    pbuf++;
    if (pbuf > buflen) //Fals der Buffer voll ist einfach löschen!
    {
      clearbuf();
    }
  }
  return;
}

void printP()
{
  update_volt_amp();
  Serial.print("$P");
  int16_t tmp=(int16_t) flightcontrol_sensors.amp*1000;
  Serial.write(tmp>>8); //MSB
  Serial.write(tmp&B11111111); //LSB
  tmp=(int16_t) flightcontrol_sensors.volt*1000;
  Serial.write(tmp>>8); //MSB
  Serial.write(tmp&B11111111); //LSB
  Serial.write('\n');

}
void printM()
{
  update_mag();
  Serial.print("$M");
  Serial.write(flightcontrol_sensors.mag[0]>>8); //MSB
  Serial.write(flightcontrol_sensors.mag[0]&B11111111); //LSB
  Serial.write(flightcontrol_sensors.mag[1]>>8); //MSB
  Serial.write(flightcontrol_sensors.mag[1]&B11111111); //LSB
  Serial.write(flightcontrol_sensors.mag[2]>>8); //MSB
  Serial.write(flightcontrol_sensors.mag[2]&B11111111); //LSB
   Serial.write('\n');
}

void printTP()
{
  update_mag();
  Serial.print("$T");
  Serial.write(flightcontrol_sensors.pres>>8); //MSB
  Serial.write(flightcontrol_sensors.pres&B11111111); //LSB
  int16_t tmp=(int16_t) flightcontrol_sensors.temp*10.0;
  Serial.write(tmp>>8); //MSB
  Serial.write(tmp&B11111111); //LSB
  
  Serial.write('\n');
}

void printF()
{
  update_gyr_acc(); 
  //Gyro xyz
  //Acc xyz
  Serial.print("$F");
  Serial.write(flightcontrol_sensors.gyr[0]>>8); //MSB
  Serial.write(flightcontrol_sensors.gyr[0]&B11111111); //LSB
  Serial.write(flightcontrol_sensors.gyr[1]>>8); //MSB
  Serial.write(flightcontrol_sensors.gyr[1]&B11111111); //LSB
  Serial.write(flightcontrol_sensors.gyr[2]>>8); //MSB
  Serial.write(flightcontrol_sensors.gyr[2]&B11111111); //LSB
  Serial.write(flightcontrol_sensors.acc[0]>>8); //MSB
  Serial.write(flightcontrol_sensors.acc[0]&B11111111); //LSB
  Serial.write(flightcontrol_sensors.acc[1]>>8); //MSB
  Serial.write(flightcontrol_sensors.acc[1]&B11111111); //LSB
  Serial.write(flightcontrol_sensors.acc[2]>>8); //MSB
  Serial.write(flightcontrol_sensors.acc[2]&B11111111); //LSB 
   Serial.write('\n');
}


void sendTelemetry()
{
  printF();

  if (tele_cnt==4 || tele_cnt==8)
  {
    printM();
  }
  if(tele_cnt>=9)
  {
  printP();
  tele_cnt=0;
  }
    
  tele_cnt++;  
}








