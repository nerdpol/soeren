

void readSerial1()
{
   while (Serial1.available() > 0)
  {
     ringbuf_put(&protocol_buffer, Serial1.read());
     decode(&protocol_buffer, &handle_packet);
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

  if (tele_cnt == 4 || tele_cnt == 8)
  {
    printM();
  }
  if (tele_cnt >= 9)
  {
    printP();
    printTP();
    tele_cnt = 0;
  }

  tele_cnt++;
}









