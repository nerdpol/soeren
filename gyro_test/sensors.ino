void setup_9axis(void) {
  I2CwriteByte(MPU9250_ADDRESS, 27, GYRO_FULL_SCALE_2000_DPS);
  // Configure accelerometers range
  I2CwriteByte(MPU9250_ADDRESS, 28, ACC_FULL_SCALE_4_G);
  // Request first magnetometer single measurement
  I2CwriteByte(MAG_ADDRESS, 0x0A, 0x11);
}

uint16_t update_gyr_acc(void) {
  uint8_t buf[14];
  I2Cread(MPU9250_ADDRESS, 0x3B, 14, buf);

  // Accelerometer
  // AFS_SEL = 0    +-2g    16384 LSB/g
  // AFS_SEL = 1    +-4g     8192 LSB/g
  // AFS_SEL = 2    +-8g     4096 LSB/g
  // AFS_SEL = 3   +-16g     2048 LSB/g
  //flightcontrol_sensors.acc[1]=(float)(-(buf[0]<<8 | buf[1]))/8192;
  //flightcontrol_sensors.acc[2]=(float)(-(buf[2]<<8 | buf[3]))/8192;
  //flightcontrol_sensors.acc[3]=(float)(buf[4]<<8 | buf[5])/8192;
  flightcontrol_sensors.acc[1] = (-(buf[0] << 8 | buf[1]));
  flightcontrol_sensors.acc[2] = (-(buf[2] << 8 | buf[3]));
  flightcontrol_sensors.acc[3] = (buf[4] << 8 | buf[5]);

  // Gyroscope
  // AFS_SEL = 0    +-250°/s    131 LSB/(°/s)
  // AFS_SEL = 1    +-500°/s   65.5 LSB/(°/s)
  // AFS_SEL = 2    +-1000°/s  32.8 LSB/(°/s)
  // AFS_SEL = 3    +-2000°/s  16.4 LSB/(°/s)
  //flightcontrol_sensors.gyr[1]=(float)(-(buf[8]<<8 | buf[9]))/16.4;
  //flightcontrol_sensors.gyr[2]=(float)(-(buf[10]<<8 | buf[11]))/16.4;
  //flightcontrol_sensors.gyr[3]=(float)(buf[12]<<8 | buf[13])/16.4;
  flightcontrol_sensors.gyr[1] = (-(buf[8] << 8 | buf[9]));
  flightcontrol_sensors.gyr[2] = (-(buf[10] << 8 | buf[11]));
  flightcontrol_sensors.gyr[3] = (buf[12] << 8 | buf[13]);

  for (uint8_t idx = 0; idx < 12; idx++)
  {
    radio_serial->print(buf[idx], HEX);
  }
  radio_serial->print("\nUmgewandelt:\n");
  radio_serial->println(flightcontrol_sensors.acc[1] *4.0/32768.0 );
radio_serial->println(flightcontrol_sensors.acc[2] *4.0/32768.0 );
radio_serial->println(flightcontrol_sensors.acc[3] *4.0/32768.0 );

}

bool update_mag(void) {
  uint8_t buf[7];
  I2Cread(MAG_ADDRESS, 0x03, 6, buf);

  //flightcontrol_sensors.mag[1]=((float)(-(buf[0]<<8 | buf[1])))/0.6;
  //flightcontrol_sensors.mag[2]=(-(buf[2]<<8 | buf[3]))/0.6;
  //flightcontrol_sensors.mag[3]=(-(buf[4]<<8 | buf[5]))/0.6;
  flightcontrol_sensors.mag[1] = (-(buf[0] << 8 | buf[1]));
  flightcontrol_sensors.mag[2] = (-(buf[2] << 8 | buf[3]));
  flightcontrol_sensors.mag[3] = (-(buf[4] << 8 | buf[5]));
  // Request first magnetometer single measurement
  I2CwriteByte(MAG_ADDRESS, 0x0A, 0x11);
}

uint16_t update_volt_amp(void) {
  flightcontrol_sensors.volt = ina219.getBusVoltage_V();
  flightcontrol_sensors.amp = ina219.getCurrent_mA() / 1000.f;
}

uint16_t update_pres_temp(void) {
  /* Get a new sensor event */
  sensors_event_t event;
  bmp.getEvent(&event);

  /* Display the results (barometric pressure is measure in hPa) */
  if (event.pressure) {
    flightcontrol_sensors.pres = event.pressure * 10;

    /* Calculating altitude with reasonable accuracy requires pressure    *
       sea level pressure for your position at the moment the data is
       converted, as well as the ambient temperature in degress
       celcius.  If you don't have these values, a 'generic' value of
       1013.25 hPa can be used (defined as SENSORS_PRESSURE_SEALEVELHPA
       in sensors.h), but this isn't ideal and will give variable
       results from one day to the next.
     *                                                                    *
       You can usually find the current SLP value by looking at weather
       websites or from environmental information centers near any major
       airport.
     *                                                                    *
       For example, for Paris, France you can check the current mean
       pressure and sea level at: http://bit.ly/16Au8ol                   */

    bmp.getTemperature(&flightcontrol_sensors.temp);
    flightcontrol_sensors.temp = flightcontrol_sensors.temp;

    /* Then convert the atmospheric pressure, and SLP to altitude         */
    /* Update this next line with the current SLP for better results      */
    /* float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
      radio_serial->print("Altitude:    ");
      radio_serial->print(bmp.pressureToAltitude(seaLevelPressure, event.pressure));
      radio_serial->println(" m");
      radio_serial->println("");*/
  }
  else {
    radio_serial->println("Sensor error");
  }
}

void setup_pres_temp(void) {
  radio_serial->println("Pressure Sensor Test"); radio_serial->println("");

  /* Initialise the sensor */
  if (!bmp.begin()) {
    /* There was a problem detecting the BMP085 ... check your connections */
    radio_serial->print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }

  /* Display some basic information on this sensor */
  displaySensorDetails();
}

// This function read Nbytes bytes from I2C device at address Address.
// Put read bytes starting at register Register in the Data array.
void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data) {
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();

  // Read Nbytes
  Wire.requestFrom(Address, Nbytes);
  uint8_t index = 0;
  while (Wire.available()) {
    Data[index++] = Wire.read();
  }
}

// Write a byte (Data) in device (Address) at register (Register)
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data) {
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}

void displaySensorDetails(void) {
  sensor_t sensor;
  bmp.getSensor(&sensor);
  radio_serial->println("------------------------------------");
  radio_serial->print  ("Sensor:       "); radio_serial->println(sensor.name);
  radio_serial->print  ("Driver Ver:   "); radio_serial->println(sensor.version);
  radio_serial->print  ("Unique ID:    "); radio_serial->println(sensor.sensor_id);
  radio_serial->print  ("Max Value:    "); radio_serial->print(sensor.max_value); radio_serial->println(" hPa");
  radio_serial->print  ("Min Value:    "); radio_serial->print(sensor.min_value); radio_serial->println(" hPa");
  radio_serial->print  ("Resolution:   "); radio_serial->print(sensor.resolution); radio_serial->println(" hPa");
  radio_serial->println("------------------------------------");
  radio_serial->println("");
  delay(500);
}
