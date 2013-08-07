#ifndef LEKA_ARDUINO_ROBOT_MOTI_SENSORS_H_
#define LEKA_ARDUINO_ROBOT_MOTI_SENSORS_H_

/**
 * @file MotiSensors.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include <Arduino.h>
#include <Wire.h>

#include <CommunicationUtils.h>
#include <DebugUtils.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <FreeSixIMU.h>


/**
 * @class MotiSensors
 * @brief MotiSensors class gathers all the Motors functions for Moti.
 */
class MotiSensors {

	public:

		MotiSensors();

		//	SENSORS
		void checkSensors();
		void checkAccelerometer();
		void checkGyroscope();

		int getXYZ(uint8_t index);
		int getYPR(uint8_t index);

		void computeDelta();
		void updateLastValues();


	private:

		//	VARIABLES
		int XYZ[3], lastXYZ[3], deltaXYZ[3];
		int YPR[3], lastYPR[3], deltaYPR[3];

		bool _stateMoving;

		//	RELATED CLASS
		FreeSixIMU AccelGyro;
};

#endif