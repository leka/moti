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

#include <Arduino.h>
#include "DriveSystem.h"

/**
 * @file DriveSystem.cpp
 * @author Ladislas de Toldi
 * @version 1.0
 */

namespace DriveSystem {

bool _isStarted = false;
Motor _rightMotor = Motor(RIGHT_MOTOR_DIRECTION_PIN, RIGHT_MOTOR_SPEED_PIN);
Motor _leftMotor = Motor(LEFT_MOTOR_DIRECTION_PIN, LEFT_MOTOR_SPEED_PIN);
Semaphore _sem = _SEMAPHORE_DATA(DriveSystem::_sem, 0);
uint8_t _rightSpeed = 0;
uint8_t _leftSpeed = 0;
Direction _rightDirection = FORWARD;
Direction _leftDirection = FORWARD;

msg_t thread(void* arg);

static WORKING_AREA(driveThreadArea, 128);


/**
 * @brief Tells the motors to spin in a given direction, at a given speed
 * @param direction the direction (FORWARD | BACKWARD)
 * @param speed the speed (0 - MOTOR_MAX_SPEED)
 */
void go(Direction direction, uint8_t speed) {
	if (!_isStarted)
		start();

	_leftDirection = direction;
	_rightDirection = direction;

	_rightSpeed = speed;
	_leftSpeed = speed;

	chSemSignal(&_sem);
}

/**
 * @brief Tells the motors to spin in a given direction, at a given speed, with different speed for right and left motors
 * @param direction the direction (FORWARD | BACKWARD)
 * @param rightSpeed the speed of the right motor (0 - MOTOR_MAX_SPEED)
 * @param leftSpeed the speed of the left motor (0 - MOTOR_MAX_SPEED)
 */
void turn(Direction direction, uint8_t rightSpeed, uint8_t leftSpeed) {
	if (!_isStarted)
		start();

	_leftDirection = direction;
	_rightDirection = direction;

	_rightSpeed = rightSpeed;
	_leftSpeed = leftSpeed;

	chSemSignal(&_sem);
}

/**
 * @brief Tells the motors to spin in the opposite direction (rotation), at a given speed
 * @param rotation the rotation side (RIGHT | LEFT)
 * @param speed the speed (0 - MOTOR_MAX_SPEED)
 */
void spin(Rotation rotation, uint8_t speed) {
	if (!_isStarted)
		start();

	switch (rotation) {
		case LEFT:
			_leftDirection = BACKWARD;
			_rightDirection = FORWARD;
			break;

		case RIGHT:
			_leftDirection = FORWARD;
			_rightDirection = BACKWARD;
			break;
	}

	_rightSpeed = speed;
	_leftSpeed = speed;

	chSemSignal(&_sem);
}

/**
 * @brief Tells the motors to immediately stop spinning
 */
void stop(void) {
	if (!_isStarted)
		start();

	_rightDirection = _leftDirection = FORWARD;
	_rightSpeed = _leftSpeed = 0;

	chSemSignal(&_sem);
}

Direction getRightDirection(void) {
	return _rightDirection;
}

uint8_t getRightSpeed(void) {
	return _rightSpeed;
}

Direction getLeftDirection(void) {
	return _leftDirection;
}

uint8_t getLeftSpeed(void) {
	return _leftSpeed;
}


void start(void* arg, tprio_t priority) {
	if (!_isStarted) {
		_isStarted = true;

		(void)chThdCreateStatic(driveThreadArea, sizeof(driveThreadArea),
				priority, thread, arg);
	}
}

msg_t thread(void* arg) {
	while (!chThdShouldTerminate()) {
		chSemWait(&_sem);

		_rightMotor.spin(_rightDirection, _rightSpeed);
		_leftMotor.spin(_leftDirection, _leftSpeed);
	}

	return (msg_t)0;
}

}
