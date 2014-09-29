/*
   Copyright (C) 2013-2014 Ladislas de Toldi <ladislas at weareleka dot com>
   and Leka <http://weareleka.com>

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

#ifndef LEKA_MOTI_MODULE_SENSORS_H_
#define LEKA_MOTI_MODULE_SENSORS_H_

/**
 * @file Sensors.h
 * @author Ladislas de Toldi & Flavien Raynaud
 * @version 1.0
 */


#include <Arduino.h>
#include <math.h>

#include "ChibiOS_AVR.h"
#include "FreeIMU.h"
#include "Moti.h"

namespace Sensors {

	// Initialization
	msg_t thread(void* arg);
	void init(void* arg = NULL, tprio_t priority = NORMALPRIO + 2);
	void start(void);
	void stop(void);

	// Accelerometer
	void getAccXYZ(float* x, float* y, float* z);
	float getAccXYZ(uint8_t index);
	float getAccX();
	float getAccY();
	float getAccZ();

	// Gyroscope - Yaw Pitch Roll
	void getGyrYPR(float* y, float* p, float* r);
	float getGyrYPR(uint8_t index);
	float getGyrY();
	float getGyrP();
	float getGyrR();

	void getGyrYPRDeg(float* y, float* p, float* r);
	float getGyrYPRDeg(uint8_t index);
	float getGyrYDeg();
	float getGyrPDeg();
	float getGyrRDeg();

	// Gyroscope - Euler angles
	void getEuler(float* phi, float* theta, float* psi);
	float getEulerPTP(uint8_t index);
	float getEulerPhi();
	float getEulerTheta();
	float getEulerPsi();

	void getEulerDeg(float* y, float* p, float* r);
	float getEulerPTPDeg(uint8_t index);
	float getEulerPhiDeg();
	float getEulerThetaDeg();
	float getEulerPsiDeg();

	// Sensor fusion
	bool isFalling();
	bool isInactive();

	// Helper methods
	void readXYZ(void);
	void readYPR(void);

	float radToDeg(float rad);
	float degToRad(float deg);
}

#endif
