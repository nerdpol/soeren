void setup_9axis(void)
{
  I2CwriteByte(MPU9250_ADDRESS,27,GYRO_FULL_SCALE_2000_DPS);
  // Configure accelerometers range
  I2CwriteByte(MPU9250_ADDRESS,28,ACC_FULL_SCALE_4_G);
  // Request first magnetometer single measurement
  I2CwriteByte(MAG_ADDRESS,0x0A,0x11);
}

uint16_t update_gyr_acc(void)
{
  //  // Read accelerometer and gyroscope
  uint8_t Buf[14];
  I2Cread(MPU9250_ADDRESS,0x3B,14,Buf);

//  // Create 16 bits values from 8 bits data
 
//  // Accelerometer
// AFS_SEL = 0    +-2g    16384 LSB/g
// AFS_SEL = 1    +-4g     8192 LSB/g
// AFS_SEL = 2    +-8g     4096 LSB/g
// AFS_SEL = 3   +-16g     2048 LSB/g
//flightcontrol_sensors.acc[1]=(float)(-(Buf[0]<<8 | Buf[1]))/8192;
//flightcontrol_sensors.acc[2]=(float)(-(Buf[2]<<8 | Buf[3]))/8192;
//flightcontrol_sensors.acc[3]=(float)(Buf[4]<<8 | Buf[5])/8192;
flightcontrol_sensors.acc[1]=(-(Buf[0]<<8 | Buf[1]));
flightcontrol_sensors.acc[2]=(-(Buf[2]<<8 | Buf[3]));
flightcontrol_sensors.acc[3]=(Buf[4]<<8 | Buf[5]);


  // Gyroscope
// AFS_SEL = 0    +-250°/s    131 LSB/(°/s)
// AFS_SEL = 1    +-500°/s   65.5 LSB/(°/s)
// AFS_SEL = 2    +-1000°/s  32.8 LSB/(°/s)
// AFS_SEL = 3    +-2000°/s  16.4 LSB/(°/s)
//flightcontrol_sensors.gyr[1]=(float)(-(Buf[8]<<8 | Buf[9]))/16.4;
//flightcontrol_sensors.gyr[2]=(float)(-(Buf[10]<<8 | Buf[11]))/16.4;
//flightcontrol_sensors.gyr[3]=(float)(Buf[12]<<8 | Buf[13])/16.4;
flightcontrol_sensors.gyr[1]=(-(Buf[8]<<8 | Buf[9]));
flightcontrol_sensors.gyr[2]=(-(Buf[10]<<8 | Buf[11]));
flightcontrol_sensors.gyr[3]=(Buf[12]<<8 | Buf[13]);
}

bool update_mag(void)
{
 
    // Read magnetometer data  
  uint8_t Mag[7];  
  I2Cread(MAG_ADDRESS,0x03,6,Mag);
  // Create 16 bits values from 8 bits data
  
  // Magnetometer
//flightcontrol_sensors.mag[1]=((float)(-(Mag[0]<<8 | Mag[1])))/0.6;
//flightcontrol_sensors.mag[2]=(-(Mag[2]<<8 | Mag[3]))/0.6;
//flightcontrol_sensors.mag[3]=(-(Mag[4]<<8 | Mag[5]))/0.6;
flightcontrol_sensors.mag[1]=(-(Mag[0]<<8 | Mag[1]));
flightcontrol_sensors.mag[2]=(-(Mag[2]<<8 | Mag[3]));
flightcontrol_sensors.mag[3]=(-(Mag[4]<<8 | Mag[5]));
  // Request first magnetometer single measurement
  I2CwriteByte(MAG_ADDRESS,0x0A,0x11);
 
}

uint16_t update_volt_amp(void)
{
  flightcontrol_sensors.volt = ina219.getShuntVoltage_mV()/1000; // Voltage between Vin- and Vin+
  //flightcontrol_sensors.voltbus = ina219.getBusVoltage_V();      //Voltage between Vin- and Gnd
  flightcontrol_sensors.amp = ina219.getCurrent_mA()/1000;    //Current over Klemme
}

uint16_t update_pres_temp(void)
{
    /* Get a new sensor event */ 
  sensors_event_t event;
  bmp.getEvent(&event);
 
  /* Display the results (barometric pressure is measure in hPa) */
  if (event.pressure)
  {
    flightcontrol_sensors.pres=event.pressure*10;

    /* Calculating altitude with reasonable accuracy requires pressure    *
     * sea level pressure for your position at the moment the data is     *
     * converted, as well as the ambient temperature in degress           *
     * celcius.  If you don't have these values, a 'generic' value of     *
     * 1013.25 hPa can be used (defined as SENSORS_PRESSURE_SEALEVELHPA   *
     * in sensors.h), but this isn't ideal and will give variable         *
     * results from one day to the next.                                  *
     *                                                                    *
     * You can usually find the current SLP value by looking at weather   *
     * websites or from environmental information centers near any major  *
     * airport.                                                           *
     *                                                                    *
     * For example, for Paris, France you can check the current mean      *
     * pressure and sea level at: http://bit.ly/16Au8ol                   */
     
    
    bmp.getTemperature(&flightcontrol_sensors.temp);
    flightcontrol_sensors.temp=flightcontrol_sensors.temp;
    

    /* Then convert the atmospheric pressure, and SLP to altitude         */
    /* Update this next line with the current SLP for better results      */
   /* float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
    Serial.print("Altitude:    "); 
    Serial.print(bmp.pressureToAltitude(seaLevelPressure,
                                        event.pressure)); 
    Serial.println(" m");
    Serial.println("");*/
  }
  else
  {
    Serial.println("Sensor error");
  }
}

void setup_pres_temp(void)
{
    Serial.println("Pressure Sensor Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!bmp.begin())
  {
    /* There was a problem detecting the BMP085 ... check your connections */
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  /* Display some basic information on this sensor */
  displaySensorDetails();
}

// This function read Nbytes bytes from I2C device at address Address. 
// Put read bytes starting at register Register in the Data array. 
void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();
  
  // Read Nbytes
  Wire.requestFrom(Address, Nbytes); 
  uint8_t index=0;
  while (Wire.available())
    Data[index++]=Wire.read();
}


// Write a byte (Data) in device (Address) at register (Register)
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}


void displaySensorDetails(void)
{
  sensor_t sensor;
  bmp.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" hPa");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" hPa");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" hPa");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}
