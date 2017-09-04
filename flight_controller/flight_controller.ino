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

#include "radio_packet.h"

#define looplength 100

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

void setup() {
	radio_setup(&Serial1, PA12, 115200);
	radio_debug("SOEREN - Self On Earth Returning Experimental Navigator\n");
	radio_debug("Radio check:\n");
	radio_debug("\t115200 Baud.\n");
	//radio_config_baud(9600);
	//radio_debug("\t9600 Baud.\n");
	//radio_config_baud(115200);
	radio_debug("Radio check complete.\n");

	radio_debug("Initializing:\n");
	radio_debug("\tRudder servos...");
	rudders_setup();
	radio_debug(" done.\n");

	radio_debug("\tGPS...");
	gps_setup();
	radio_debug(" done.\n");

	radio_debug("\tAtmospheric sensors...");
	atmosphere_setup();
	radio_debug(" done.\n");

	radio_debug("\tPower sensor...");
	power_setup();
	radio_debug(" done.\n");

	radio_debug("\tOrientation sensor...");
	orientation_setup();
	radio_debug(" done.\n");

	radio_debug("Initialization Complete.\n");

	radio_debug("\n\"Look at you, soaring through the air without a care in the world. Like an eagle. PILOTING A BLIMP!\" - GLaDOS\n");

	time = millis() + looplength;
}

void handle_packet(union packet * packet) {
	switch (packet->tag) {
		case PKT_CONTROL:
			rudders_update(packet->control.control[0],
			    packet->control.control[1],
			    packet->control.control[2],
			    packet->control.control[3],
			    packet->control.control[4]);
			break;
		case PKT_REPORT: {
			char info[256];
			snprintf(info, 256, "REPORT{gyr=(%hu %hu %hu), acc=(%hu %hu %hu), mag=(%hu %hu %hu), temp=%f, pres=%hu, volt=%f, cur=%f}\n",
			    flightcontrol_sensors.gyr[0], flightcontrol_sensors.gyr[1], flightcontrol_sensors.gyr[2],
			    flightcontrol_sensors.acc[0], flightcontrol_sensors.acc[1], flightcontrol_sensors.acc[2],
			    flightcontrol_sensors.mag[0], flightcontrol_sensors.mag[1], flightcontrol_sensors.mag[2],
			    flightcontrol_sensors.temperature, flightcontrol_sensors.pressure,
			    flightcontrol_sensors.voltage, flightcontrol_sensors.current);
			radio_debug(info);
		} break;
		default:
			break;
	}
}

void loop() {
	static uint8_t tele_cnt = 0;

	radio_update(&handle_packet);
	gps_update();

	if (millis() >= time) {
		orientation_update();
		telemetry_send_flight();

		if (tele_cnt == 5 || tele_cnt == 10) {
			telemetry_send_mag();
		}

		if (tele_cnt >= 16) {
			atmosphere_update();
			telemetry_send_atmosphere();
			power_update();
			telemetry_send_power();
			gps_update();
			telemetry_send_gps();
			tele_cnt = 0;
		}

		tele_cnt++;
		time += looplength;
	}
}
