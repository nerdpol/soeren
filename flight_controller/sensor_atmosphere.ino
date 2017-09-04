#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

void atmosphere_setup() {
	if(!bmp.begin()) {
		radio_debug("BMP085 failed to initialize (check I2C wiring/addr)");
		while(1);
	}

	//displaySensorDetails();
}

void atmosphere_update() {
	/* Get a new sensor event */ 
	sensors_event_t event;
	bmp.getEvent(&event);

	/* Display the results (barometric pressure is measure in hPa) */
	if (event.pressure) {
		flightcontrol_sensors.pressure = event.pressure*10;

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

		bmp.getTemperature(&flightcontrol_sensors.temperature);

		/* Then convert the atmospheric pressure, and SLP to altitude         */
		/* Update this next line with the current SLP for better results      */
		/* float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
		Serial1.print("Altitude:    "); 
		Serial1.print(bmp.pressureToAltitude(seaLevelPressure, event.pressure));
		Serial1.println(" m");
		Serial1.println("");*/
	}
	else {
		radio_debug("Sensor error");
	}
}

/*void displaySensorDetails(void) {
	sensor_t sensor;
	bmp.getSensor(&sensor);
	Serial1.println("------------------------------------");
	Serial1.print  ("Sensor:       "); Serial1.println(sensor.name);
	Serial1.print  ("Driver Ver:   "); Serial1.println(sensor.version);
	Serial1.print  ("Unique ID:    "); Serial1.println(sensor.sensor_id);
	Serial1.print  ("Max Value:    "); Serial1.print(sensor.max_value); Serial1.println(" hPa");
	Serial1.print  ("Min Value:    "); Serial1.print(sensor.min_value); Serial1.println(" hPa");
	Serial1.print  ("Resolution:   "); Serial1.print(sensor.resolution); Serial1.println(" hPa");
	Serial1.println("------------------------------------");
	Serial1.println("");
	delay(500);
}*/