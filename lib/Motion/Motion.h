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

#ifndef LEKA_MOTI_ARDUINO_MOTION_H_
#define LEKA_MOTI_ARDUINO_MOTION_H_

/**
 * @file Motion.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include <Arduino.h>
#include <math.h>

#include "ChibiOS_AVR.h"
#include "DriveSystem.h"
#include "Sensors.h"

typedef enum {
	GO,
	SPIN,
	TURN,
	STOP,
	NONE
} MotionState;

/**
 * @class Motion
 * @brief Motion gathers all the driving related functions such as going forward, backward, turning and spinning.
 */

namespace Motion {

	// Thread
	msg_t moduleThread(void* arg);
	void init(void* arg = NULL, tprio_t priority = NORMALPRIO + 1);

	// Methods
	void go(Direction direction, uint8_t speed, uint16_t duration, uint16_t goDelay = 0);
	void spin(Rotation rotation, uint8_t speed, float angle);
	void spinDeg(Rotation rotation, uint8_t speed, float angle);
	void stop(uint16_t stopDuration);

	// Get methods
	MotionState getState();

	// Simple methods
	void goForward(uint8_t speed, uint16_t duration);
	void goBackward(uint8_t speed, uint16_t duration);

	void spinRight(uint8_t speed, float angle);
	void spinLeft(uint8_t speed, float angle);

	void spinRightDeg(uint8_t speed, float angle);
	void spinLeftDeg(uint8_t speed, float angle);
	void stopNow(void);

	// Helpers methods
	float computeAimAngle(Rotation rotation, float originAngle, float angle);
	bool rotationEnded(Rotation rotation, float aimAngle, float* lastAngle);

}

#endif
