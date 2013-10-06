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

		void open();

		//	SENSORS
		void read();
		void readAccelerometer();
		void readGyroscope();

		int readXYZ(uint8_t index);
		int readYPR(uint8_t index);

		void computeDelta();
		void updateLastValues();

		void sendJson();
		void writeData();


	private:

		//	VARIABLES
		int XYZ[3], lastXYZ[3], deltaXYZ[3];
		int YPR[3], lastYPR[3], deltaYPR[3];

		static const int numberOfReadings = 10;

		int readings[numberOfReadings];     
		int readingsIndex = 0;                 
		int readingsSum = 0;                  
		int readingsAverage = 0;                



		//	RELATED CLASS
		FreeSixIMU AccelGyro;
};

#endif