/*
   ATTN: Change the board settings to disable USB
   genericSTM32F103C.menu.upload_method.STLinkMethod.build.upload_flags=-DCONFIG_MAPLE_MINI_NO_DISABLE_DEBUG=1 -DGENERIC_BOOTLOADER

   I2C
      SCL   B6
      SDA   B7

   HC-12 (UART1)
      TX   A9 (TX1)
      RX   A10 (RX1)
      SET  A12

   GPS (UART3)
      TX  B10 (TX3)
      RX  B11 (RX2)

   Servos
      Servo1  A0
      Servo2  A1
      Servo3  A2
      Servo4  A3
      Servo5  A6

   For switching between GyroMeters / ADO Port
   To overcome problem of same I2C Adress
      Enable/Disable_Gyro1  A11
      Enable/Disable_Gyro2  A15

   weiter PWM
      A7
      B0
      B1

   SPI for SD-Card (SPI2
      NSS2    B12 (NSS2)
      SCK2    B13 (SCK2)
      MISO2   B14 (MISO2)
      MOSI2   B15 (MOSI2)
      CS      A15
      INT     B5
*/


#include "includes.h"
#include "radio_packet.h"
#include <Wire.h>
#define looplength 100
unsigned int calibrationData[7];
typedef struct {
  uint16_t pressure;
  uint16_t acc[3];
  uint16_t mag[3];
  uint16_t gyr[3];
  float temperature;
  float current;
  float voltage;
  float latitude;
  float longitude;
  uint16_t altitude;
  uint8_t links;
  float yaw;
  float velocity;
} flightcontrol_sensors_t;
flightcontrol_sensors_t flightcontrol_sensors;

unsigned long time;
int16_t mag_bias[3] = {0, 0, 0}, mag_scale[3] = {0, 0, 0};
void setup() {
  radio_setup(&Serial, PA12, 115200);
  radio_configure_baud(115200);
  radio_configure_channel(5);
  radio_debug("SOEREN - Self On Earth Returning Experimental Navigator\n");
  radio_debug("Radio check:\n");
  radio_debug("\t115200 Baud.\n");
  // radio_configure_baud(9600);
  // radio_debug("\t9600 Baud.\n");
  // radio_configure_baud(115200);
  radio_debug("Radio check complete.\n");
  delay(1000);

  Serial.println("Starte setup");
  mpu_init();


  getMres();
  Serial.print("Mres:");
  Serial.println(mRes);

  //calMagSensor();
}


void loop() {


  if (readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01) {  // On interrupt, check if data ready interrupt
    readAccelData(accelCount);  // Read the x/y/z adc values
    getAres();

    // Now we'll calculate the accleration value into actual g's
    ax = (float)accelCount[0] * aRes; // - accelBias[0];  // get actual g value, this depends on scale being set
    ay = (float)accelCount[1] * aRes; // - accelBias[1];
    az = (float)accelCount[2] * aRes; // - accelBias[2];

    readGyroData(gyroCount);  // Read the x/y/z adc values
    getGres();

    // Calculate the gyro value into actual degrees per second
    gx = (float)gyroCount[0] * gRes; // get actual gyro value, this depends on scale being set
    gy = (float)gyroCount[1] * gRes;
    gz = (float)gyroCount[2] * gRes;

    readMagData(magCount);  // Read the x/y/z adc values
    getMres();
    //    magbias[0] = +470.;  // User environmental x-axis correction in milliGauss, should be automatically calculated
    //    magbias[1] = +120.;  // User environmental x-axis correction in milliGauss
    //    magbias[2] = +125.;  // User environmental x-axis correction in milliGauss

    // Calculate the magnetometer values in milliGauss
    // Include factory calibration per data sheet and user environmental corrections
    /*
      mx = (float)magCount[0] * mRes * magCalibration[0] - magbias[0]; // get actual magnetometer value, this depends on scale being set
      my = (float)magCount[1] * mRes * magCalibration[1] - magbias[1];
      mz = (float)magCount[2] * mRes * magCalibration[2] - magbias[2];

    */

    //Franz routines
//    mag_bias[0] = -29;
//    mag_bias[0] = 158;
//    mag_bias[0] = -164;

//    Serial.print( (int)magCount[0] );
//    Serial.print(","); Serial.print( (int)magCount[1]  );
//    Serial.print(","); Serial.print( (int)magCount[2]  ); Serial.print("->");
//    Serial.print( (int)(magCount[0] - mag_bias[0]) );
//    Serial.print(","); Serial.print( (int)(magCount[1] - mag_bias[1])  );
//    Serial.print(","); Serial.print( (int)(magCount[2] - mag_bias[2])  ); Serial.println(" :)");

    mx = (float)(magCount[0] - mag_bias[0]) * mRes * magCalibration[0];
    my = (float)(magCount[1] - mag_bias[1]) * mRes * magCalibration[1];
    mz = (float)(magCount[2] - mag_bias[2]) * mRes * magCalibration[2];


  }
  Now = micros();
  deltat = ((Now - lastUpdate) / 1000000.0f); // set integration time by time elapsed since last filter update
  lastUpdate = Now;

  sum += deltat; // sum for averaging filter update rate
  sumCount++;

  // Sensors x (y)-axis of the accelerometer is aligned with the y (x)-axis of the magnetometer;
  // the magnetometer z-axis (+ down) is opposite to z-axis (+ up) of accelerometer and gyro!
  // We have to make some allowance for this orientationmismatch in feeding the output to the quaternion filter.
  // For the MPU-9250, we have chosen a magnetic rotation that keeps the sensor forward along the x-axis just like
  // in the LSM9DS0 sensor. This rotation can be modified to allow any convenient orientation convention.
  // This is ok by aircraft orientation standards!
  // Pass gyro rate as rad/s
  //  MadgwickQuaternionUpdate(ax, ay, az, gx*PI/180.0f, gy*PI/180.0f, gz*PI/180.0f,  my,  mx, mz);
  MahonyQuaternionUpdate(ax, ay, az, gx * PI / 180.0f, gy * PI / 180.0f, gz * PI / 180.0f, my, mx, mz);

  yaw   = atan2(2.0f * (q[1] * q[2] + q[0] * q[3]), q[0] * q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3]);
  pitch = -asin(2.0f * (q[1] * q[3] - q[0] * q[2]));
  roll  = atan2(2.0f * (q[0] * q[1] + q[2] * q[3]), q[0] * q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3]);
  pitch *= 180.0f / PI;
  yaw   *= 180.0f / PI;
  yaw   -= 3; // Angeblich fuer Muenchen
  roll  *= 180.0f / PI;
  float heading = atan2(my, mx);

  Serial.print("Yaw, Pitch, Roll: ");
  Serial.print(yaw, 2);
  Serial.print(", ");
  Serial.print(pitch, 2);
  Serial.print(", ");
  Serial.print(roll, 2);
  Serial.print(",-> ");
  Serial.print(heading, 2);
  Serial.print("mx = "); Serial.print( (int)mx );
  Serial.print(" my = "); Serial.print( (int)my );
  Serial.print(" mz = "); Serial.print( (int)mz ); Serial.print(" mG ");
  
  Serial.print(" rate = "); Serial.print((float)sumCount / sum, 2); Serial.println(" Hz");



}

void calMagSensor()
{

  int16_t mag_max[3] = { -32767, -32767, -32767}, mag_min[3] = {32767, 32767, 32767}, mag_temp[3] = {0, 0, 0};


  Serial.print("Mag Sensor calibration in 5....4...3....2...1...");
  delay(2000);
  Serial.println("gooooo");


  getMres();
  for (uint16_t cnt = 0; cnt < 1000; cnt++) {
    readMagData(magCount);  // Read the x/y/z adc values

    for (int jj = 0; jj < 3; jj++) {
      if (magCount[jj] > mag_max[jj]) mag_max[jj] = magCount[jj];
      if (magCount[jj] < mag_min[jj]) mag_min[jj] = magCount[jj];
    }

    Serial.print("mx = "); Serial.print( (int)magCount[0] );
    Serial.print(" my = "); Serial.print( (int)magCount[1]  );
    Serial.print(" mz = "); Serial.print( (int)magCount[2]  ); Serial.println(" Count");
    delay(100);

  }
  Serial.println("Cal Finsiehd");

  mag_bias[0]  = (mag_max[0] + mag_min[0]) / 2; // get average x mag bias in counts
  mag_bias[1]  = (mag_max[1] + mag_min[1]) / 2; // get average y mag bias in counts
  mag_bias[2]  = (mag_max[2] + mag_min[2]) / 2; // get average z mag bias in counts

  Serial.print("mx_max,min = "); Serial.print( (int)mag_max[0]);  Serial.print(" "); Serial.print( (int)mag_min[0]);
  Serial.print("my_max,min = "); Serial.print( (int)mag_max[1]);  Serial.print(" "); Serial.print( (int)mag_min[1]);
  Serial.print("mz_max,min = "); Serial.print( (int)mag_max[2]);  Serial.print(" "); Serial.println( (int)mag_min[2]);

  Serial.print("mx_bias = "); Serial.print( (int)mag_bias[0] );
  Serial.print(" my_bias = "); Serial.print( (int)mag_bias[1] );
  Serial.print(" mz_bias = "); Serial.println( (int)mag_bias[2] );

  //  magbias[0] = (float)mag_bias[0] * mRes * magCalibration[0];
  //  magbias[1] = (float)mag_bias[1] * mRes * magCalibration[1];
  //  magbias[2] = (float)mag_bias[2] * mRes * magCalibration[2];

  Serial.print("mx_magbias = "); Serial.print( magbias[0] );
  Serial.print(" my_magbias = "); Serial.print( magbias[1] );
  Serial.print(" mz_magbias = "); Serial.print( magbias[2] ); Serial.println("Conts");
  delay(5000);

}


