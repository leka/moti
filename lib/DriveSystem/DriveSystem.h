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

#ifndef LEKA_MOTI_ARDUINO_DRIVE_SYSTEM_H_
#define LEKA_MOTI_ARDUINO_DRIVE_SYSTEM_H_

/**
 * @file DriveSystem.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Motor.h"

#include "Sensors.h"

enum Direction {
	BACK,
	FORTH
};

enum Rotation {
	RIGHT,
	LEFT
};

/**
 * @class DriveSystem
 * @brief DriveSystem gathers all the driving related functions such as going forward, backward, turning and spinning.
 */
class DriveSystem {

	public:

		DriveSystem();

		void go(Direction direction = FORTH, uint8_t speed = DEFAULT_MAX_SPEED, uint32_t time = 0, uint16_t launchTime = 250);

		void launch(Direction direction = FORTH, uint8_t speed = DEFAULT_MAX_SPEED, uint16_t launchTime = 250);

		void spin(Sensors &sensors, Rotation rotationDirection = RIGHT, uint8_t speed = DEFAULT_MAX_SPEED, uint16_t angle = 90);

		// TODO : is it really useful? shouldn't it be part of a dynamic behavior?
		void turn(Rotation rotationDirection = RIGHT, uint8_t speed = DEFAULT_MAX_SPEED);

		// void turn(int16_t angle = 45, bool direction = FORTH, uint8_t speed = DEFAULT_MAX_SPEED) const;

		void stop(uint32_t stopTime = 250);

		void activate();

	private:

		// VARIABLES
		uint8_t rSpeed;
		uint8_t lSpeed;

		Direction rDirection;
		Direction lDirection;

		// MOTOR PINS
		static const uint8_t DEFAULT_LEFT_MOTOR_SPEED_PIN      = 5;
		static const uint8_t DEFAULT_LEFT_MOTOR_DIRECTION_PIN  = 4;
		static const uint8_t DEFAULT_RIGHT_MOTOR_SPEED_PIN     = 6;
		static const uint8_t DEFAULT_RIGHT_MOTOR_DIRECTION_PIN = 7;

		// CONSTANTS
		static const uint8_t DEFAULT_MIN_SPEED = 0;
		static const uint8_t DEFAULT_MAX_SPEED = 220;

		// RIGHT & LEFT MOTOR INSTANCES
		Motor rMotor, lMotor;

		Sensors sensors;
};

#endif
