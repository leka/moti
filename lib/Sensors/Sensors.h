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
 * @author Ladislas de Toldi & Flavien Raynaud
 * @version 1.0
 */


#include <math.h>

#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Configuration.h"
#include "FreeIMU.h"
#include "Moti.h"


class Sensors {
	public:
		static void getAccXYZ(float* x, float* y, float* z);
		static float getAccX();
		static float getAccY();
		static float getAccZ();

		static void getGyrYPR(float* y, float* p, float* r);
		static float getGyrY();
		static float getGyrP();
		static float getGyrR();

		static void getEuler(float* phi, float* theta, float* psi);
		static float getEulerPhi();
		static float getEulerTheta();
		static float getEulerPsi();

		static void getGyrYPRDeg(float* y, float* p, float* r);
		static float getGyrYDeg();
		static float getGyrPDeg();
		static float getGyrRDeg();

		static void getEulerDeg(float* y, float* p, float* r);
		static float getEulerPhiDeg();
		static float getEulerThetaDeg();
		static float getEulerPsiDeg();

		static bool isFalling();
		static bool isInactive();

		static float radToDeg(float rad);
		static float degToRad(float deg);

	private:
		static void init(void);
		static void readXYZ(void);
		static void readYPR(void);

		static float _XYZ[6]; /* X, Y, Z */
		static float _YPR[3]; /* Yaw, Pitch, Roll */
		static float _PTP[3]; /* Phi, Theta, Psi */

		static uint32_t _lastTimeXYZ, _lastTimeYPR;

		static FreeIMU _imu;

		static bool _isInit;
};

#endif