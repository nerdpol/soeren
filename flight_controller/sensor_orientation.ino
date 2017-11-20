#define MPU9250_ADDRESS 0x68
#define MAG_ADDRESS 0x0C

#define GYRO_FULL_SCALE_250_DPS 0x00
#define GYRO_FULL_SCALE_500_DPS 0x08
#define GYRO_FULL_SCALE_1000_DPS 0x10
#define GYRO_FULL_SCALE_2000_DPS 0x18

#define ACC_FULL_SCALE_2_G 0x00
#define ACC_FULL_SCALE_4_G 0x08
#define ACC_FULL_SCALE_8_G 0x10
#define ACC_FULL_SCALE_16_G 0x18

void orientation_setup() {
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
  // flightcontrol_sensors.acc[0]=(float)(-(buf[0]<<8 | buf[1]))/8192;
  // flightcontrol_sensors.acc[1]=(float)(-(buf[2]<<8 | buf[3]))/8192;
  // flightcontrol_sensors.acc[2]=(float)(buf[4]<<8 | buf[5])/8192;
  flightcontrol_sensors.accel[0] = (-(buf[0] << 8 | buf[1]));
  flightcontrol_sensors.accel[1] = (-(buf[2] << 8 | buf[3]));
  flightcontrol_sensors.accel[2] = (buf[4] << 8 | buf[5]);

  // Gyroscope
  // AFS_SEL = 0    +-250°/s    131 LSB/(°/s)
  // AFS_SEL = 1    +-500°/s   65.5 LSB/(°/s)
  // AFS_SEL = 2    +-1000°/s  32.8 LSB/(°/s)
  // AFS_SEL = 3    +-2000°/s  16.4 LSB/(°/s)
  // flightcontrol_sensors.gyr[0]=(float)(-(buf[8]<<8 | buf[9]))/16.4;
  // flightcontrol_sensors.gyr[1]=(float)(-(buf[10]<<8 | buf[11]))/16.4;
  // flightcontrol_sensors.gyr[2]=(float)(buf[12]<<8 | buf[13])/16.4;
  flightcontrol_sensors.gyro[0] = (-(buf[8] << 8 | buf[9]));
  flightcontrol_sensors.gyro[1] = (-(buf[10] << 8 | buf[11]));
  flightcontrol_sensors.gyro[2] = (buf[12] << 8 | buf[13]);
}

bool update_mag(void) {
  uint8_t buf[7];
  I2Cread(MAG_ADDRESS, 0x03, 6, buf);

  // flightcontrol_sensors.mag[0]=((float)(-(buf[0]<<8 | buf[1])))/0.6;
  // flightcontrol_sensors.mag[1]=(-(buf[2]<<8 | buf[3]))/0.6;
  // flightcontrol_sensors.mag[2]=(-(buf[4]<<8 | buf[5]))/0.6;
  flightcontrol_sensors.mag[0] = (-(buf[0] << 8 | buf[1]));
  flightcontrol_sensors.mag[1] = (-(buf[2] << 8 | buf[3]));
  flightcontrol_sensors.mag[2] = (-(buf[4] << 8 | buf[5]));
  // Request first magnetometer single measurement
  I2CwriteByte(MAG_ADDRESS, 0x0A, 0x11);
}

void orientation_update() {
  update_gyr_acc();
  update_mag();
}
