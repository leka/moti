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

#ifndef LEKA_MOTI_ARDUINO_DRIVE_H_
#define LEKA_MOTI_ARDUINO_DRIVE_H_

/**
 * @file Drive.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Configuration.h"
#include "Motor.h"

/**
 * @class DriveSystem
 * @brief DriveSystem gathers all the driving related functions such as going forward, backward, turning and spinning.
 */
class Drive {
	public:
		static void start(void* arg=NULL, tprio_t priority=NORMALPRIO+2);

		static void go(Direction direction, uint8_t speed);
		static void spin(Rotation rotation, uint8_t speed);
		static void turn(Direction direction, uint8_t rightSpeed, uint8_t leftSpeed);
		static void stop(void);

		static Direction getRightDirection(void);
		static uint8_t getRightSpeed(void);

		static Direction getLeftDirection(void);
		static uint8_t getLeftSpeed(void);


	private:
		static uint8_t _rightSpeed, _leftSpeed;
		static Direction _rightDirection, _leftDirection;
		static Motor _rightMotor, _leftMotor;

		static bool _isStarted;

		static Semaphore _sem;
		static msg_t thread(void* arg);
};

#endif
