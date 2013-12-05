#ifndef LEKA_MOTI_ARDUINO_SENSORS_H_
#define LEKA_MOTI_ARDUINO_SENSORS_H_

/**
 * @file Sensors.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include <Arduino.h>
#include <Wire.h>

#include "ChibiOS_AVR.h"

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

		int readXYZ(uint8_t index) const;
		int readYPR(uint8_t index) const;

		void sendJson() const;
		void sendData() const;

	private:

		//	VARIABLES
		int _XYZ[3], _tmpXYZ[3];
		int _YPR[3];
		float _tmpYPR[3];

		// MUTEX
		MUTEX_DECL(sensorsDataMutex);

		//	RELATED CLASS
		FreeIMU AccelGyro;
};

#endif