/*
 * I2C
 *    SCL   B6
 *    SDA   B7
 * 
 * HC-12 (UART1)
 *    TX   A9 (TX1)
 *    RX   A10 (RX1)
 *    SET  A12
 * 
 * GPS (UART3)
 *    TX  B10 (TX3)
 *    RX  B11 (RX2)
 * 
 * Servos
 *    Servo1  A0
 *    Servo2  A1
 *    Servo3  A2
 *    Servo4  A3
 *    Servo5  A6
 * 
 * For switching between GyroMeters / ADO Port
 * To overcome problem of same I2C Adress
 *    Enable/Disable_Gyro1  A11
 *    Enable/Disable_Gyro2  A15
 * 
 * weiter PWM
 *    A7
 *    B0
 *    B1
 * 
 * SPI for SD-Card (SPI2
 *    NSS2    B12 (NSS2)
 *    SCK2    B13 (SCK2)
 *    MISO2   B14 (MISO2)
 *    MOSI2   B15 (MOSI2)
 *    CS      A15
 *    INT     B5
*/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_INA219.h>
#include <TinyGPS++.h>
#include <Servo.h>

#define looplength 100
//#define debug 1

#define    MPU9250_ADDRESS            0x68
#define    MAG_ADDRESS                0x0C

#define    GYRO_FULL_SCALE_250_DPS    0x00
#define    GYRO_FULL_SCALE_500_DPS    0x08
#define    GYRO_FULL_SCALE_1000_DPS   0x10
#define    GYRO_FULL_SCALE_2000_DPS   0x18

#define    ACC_FULL_SCALE_2_G        0x00
#define    ACC_FULL_SCALE_4_G        0x08
#define    ACC_FULL_SCALE_8_G        0x10
#define    ACC_FULL_SCALE_16_G       0x18
//Ende nur für 9AxisSensor

Adafruit_INA219 ina219;
TinyGPSPlus gps;
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);
Servo s1;
Servo s2;
Servo s3;
Servo s4;
Servo s5;

struct ringbuf {
	uint8_t buffer[64];
	uint8_t * head;
	uint8_t * tail;
};
struct ringbuf protocol_buffer;

unsigned long time;

typedef struct {
	uint16_t pres;
	uint16_t acc[3];
	uint16_t mag[3];
	uint16_t gyr[3];
	float temp;
	float amp;
	float volt;
} flightcontrol_sensors_t;
flightcontrol_sensors_t flightcontrol_sensors;

uint8_t servos[5]; // c.....P

void setup() {
	// HC-12 Radio
	pinMode(PA12, OUTPUT);
	digitalWrite(PA12,HIGH);
	delay(100);
	Serial1.begin(115200);
	Serial1.println("$D Flightcontroler V0.1 awesome DM Project");
	Serial3.begin(9600);
	ringbuf_init(&protocol_buffer);

	pinMode(13, OUTPUT);

	//Servos
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
	for (uint8_t cnt = 0; cnt < 5; cnt++) {
		servos[cnt] = 90;
	}

	// Temperature/Pressure
	setup_pres_temp();

	// Voltage/Current
	ina219.begin();

	// Flight data (Gyro/Accelerometer)
	setup_9axis();

	time = millis() + looplength;
}

void loop() {
	readSerial1();
	byte data;
	while (Serial3.available()) {
		data=Serial3.read();
		gps.encode(data);
		//Serial1.print((char) data);   
	}

	if (millis() > time) {
		//Hier passiert die Regelung irgendwann!
		sendTelemetry();
		time = time + looplength;
	}
}
