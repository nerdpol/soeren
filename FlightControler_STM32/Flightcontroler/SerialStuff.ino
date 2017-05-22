

void readSerial1()
{
   while (Serial1.available() > 0)
  {
     ringbuf_put(&protocol_buffer, Serial1.read());
     decode(&protocol_buffer, &handle);
  }
}



void printP()
{
  update_volt_amp();
  resetTeleChecksum();
  writeTeleData('P');
  int16_t tmp = (int16_t) flightcontrol_sensors.amp * 1000;
  writeTeleData(tmp >> 8); //MSB
  writeTeleData(tmp & B11111111); //LSB
  tmp = (int16_t) flightcontrol_sensors.volt * 1000;
  writeTeleData(tmp >> 8); //MSB
  writeTeleData(tmp & B11111111); //LSB
  writeTeleChecksum();

}
void printM()
{
  update_mag();
  resetTeleChecksum();
  writeTeleData('M');
  writeTeleData(flightcontrol_sensors.mag[0] >> 8); //MSB
  writeTeleData(flightcontrol_sensors.mag[0]&B11111111); //LSB
  writeTeleData(flightcontrol_sensors.mag[1] >> 8); //MSB
  writeTeleData(flightcontrol_sensors.mag[1]&B11111111); //LSB
  writeTeleData(flightcontrol_sensors.mag[2] >> 8); //MSB
  writeTeleData(flightcontrol_sensors.mag[2]&B11111111); //LSB
  writeTeleChecksum();
}

void printTP()
{
  update_pres_temp();
  resetTeleChecksum();
  writeTeleData('T');
  writeTeleData(flightcontrol_sensors.pres >> 8); //MSB
  writeTeleData(flightcontrol_sensors.pres & B11111111); //LSB
  int16_t tmp = (int16_t) flightcontrol_sensors.temp * 10.0;
  writeTeleData(tmp >> 8); //MSB
  writeTeleData(tmp & B11111111); //LSB
  writeTeleChecksum();

}

void printG()
{
  // G lat s32bit long s32 alt u16 links u8 yan s16/100 grad, velocity u16 cm/s
int32_t tmp;
uint16_t tmp1;
uint8_t tmp2;
resetTeleChecksum();
writeTeleData('G');
tmp=(int32_t) (gps.location.lat()*10000000);
writeTeleData(tmp>>24);
writeTeleData(tmp>>16 &0xFF);
writeTeleData(tmp>>8 &0xFF);
writeTeleData(tmp&0xFF);

tmp=(int32_t) (gps.location.lng()*10000000);
writeTeleData(tmp>>24);
writeTeleData(tmp>>16 &0xFF);
writeTeleData(tmp>>8 &0xFF);
writeTeleData(tmp&0xFF);

tmp1= (uint16_t) gps.altitude.meters();
writeTeleData(tmp1>>8 &0xFF);
writeTeleData(tmp1&0xFF);

writeTeleData((uint8_t) gps.hdop.value());

tmp1=(uint16_t) gps.course.deg()*100;
writeTeleData(tmp1>>8 &0xFF);
writeTeleData(tmp1&0xFF);

tmp1=(uint16_t) gps.speed.kmph()*100;
writeTeleData(tmp1>>8 &0xFF);
writeTeleData(tmp1&0xFF);

 writeTeleChecksum();
  
}
void printF()
{
  update_gyr_acc();
  //Gyro xyz
  //Acc xyz
  resetTeleChecksum();
  writeTeleData('F');
  writeTeleData(flightcontrol_sensors.gyr[0] >> 8); //MSB
  writeTeleData(flightcontrol_sensors.gyr[0]&B11111111); //LSB
  writeTeleData(flightcontrol_sensors.gyr[1] >> 8); //MSB
  writeTeleData(flightcontrol_sensors.gyr[1]&B11111111); //LSB
  writeTeleData(flightcontrol_sensors.gyr[2] >> 8); //MSB
  writeTeleData(flightcontrol_sensors.gyr[2]&B11111111); //LSB
  writeTeleData(flightcontrol_sensors.acc[0] >> 8); //MSB
  writeTeleData(flightcontrol_sensors.acc[0]&B11111111); //LSB
  writeTeleData(flightcontrol_sensors.acc[1] >> 8); //MSB
  writeTeleData(flightcontrol_sensors.acc[1]&B11111111); //LSB
  writeTeleData(flightcontrol_sensors.acc[2] >> 8); //MSB
  writeTeleData(flightcontrol_sensors.acc[2]&B11111111); //LSB
  writeTeleChecksum();
}

uint8_t checksumdata = 0;
void resetTeleChecksum()
{
  checksumdata = 0;
}
void writeTeleData(uint8_t data)
{
  checksumdata = checksumdata ^ data;
  Serial1.write(data);
}

void writeTeleChecksum()
{
  Serial1.write(checksumdata);
  checksumdata = 0;
}

void sendTelemetry()
{
  printF();

  if (tele_cnt == 5 || tele_cnt == 10 )
  {
    printM();
  }
  if (tele_cnt >= 16)
  {
    printP();
    printTP();
    printG();
    tele_cnt = 0;
  }

  tele_cnt++;
}









