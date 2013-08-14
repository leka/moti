#ifndef LEKA_MOTI_ARDUINO_SENSORS_H_
#define LEKA_MOTI_ARDUINO_SENSORS_H_

/**
 * @file Sensors.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include <Arduino.h>
#include <Serial.h>
#include <Wire.h>
#include <CommunicationUtils.h>
#include <DebugUtils.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <FreeSixIMU.h>


/**
 * @class Sensors
 * @brief Sensors class gathers all the Motors functions for Moti.
 */
class Sensors {

	public:

		Sensors();

		void init();

		//	SENSORS
		void checkSensors();
		void checkAccelerometer();
		void checkGyroscope();

		int getXYZ(uint8_t index);
		int getYPR(uint8_t index);

		void computeDelta();
		void updateLastValues();

		void sendJson();


	private:

		//	VARIABLES
		int XYZ[3], lastXYZ[3], deltaXYZ[3];
		int YPR[3], lastYPR[3], deltaYPR[3];

		bool _stateMoving;

		//	RELATED CLASS
		FreeSixIMU AccelGyro;
};

#endif