/*
Copyright (C) 2013-2014 Ladislas de Toldi <ladislas at weareleka dot com> and Leka <http://weareleka.com>

This file is part of Moti, a spherical robotic smart toy for autistic children.

Moti is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Moti is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Moti. If not, see <http://www.gnu.org/licenses/>.
*/

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

		int getXYZ(uint8_t index);
		int getYPR(uint8_t index);
		float getEuler(uint8_t index);

		void sendJson();
		void sendData();
		void debug();

	private:

		//	VARIABLES
		int _XYZ[3], _tmpXYZ[3];
		int _YPR[3];
		float _tmpYPR[3];

		FreeIMU AccelGyro;

		// MUTEX
		MUTEX_DECL(sensorsDataMutex);

		//	RELATED CLASS
};

#endif