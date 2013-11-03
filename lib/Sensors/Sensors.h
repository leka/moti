#ifndef LEKA_MOTI_ARDUINO_SENSORS_H_
#define LEKA_MOTI_ARDUINO_SENSORS_H_

/**
 * @file Sensors.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include <Arduino.h>
#include <Wire.h>

#include "CommunicationUtils.h"
#include "DebugUtils.h"
#include "ADXL345.h"
#include "ITG3200.h"
#include "FreeIMU.h"
#include "Serial.h"

/**
 * @class Sensors
 * @brief Sensors class gathers all the Motors functions for Moti.
 */
class Sensors {

	public:

		Sensors();

		void init();

		//	SENSORS
		void read();
		void readAccelerometer();
		void readGyroscope();

		uint16_t readXYZ(uint8_t index);
		int16_t readYPR(uint8_t index);

		void computeDelta();
		void updateLastValues();

		void sendJson();
		void writeData();

	private:

		//	VARIABLES
		int XYZ[3], lastXYZ[3], deltaXYZ[3];
		int16_t YPR[3], lastYPR[3], deltaYPR[3];

		//	RELATED CLASS
		FreeIMU AccelGyro;
};

#endif