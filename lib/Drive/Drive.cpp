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
#include "Drive.h"

/**
 * @file Drive.cpp
 * @author Ladislas de Toldi
 * @version 1.0
 */


bool Drive::_isStarted = false;
Motor Drive::_rMotor = Motor(RIGHT_MOTOR_DIRECTION_PIN, RIGHT_MOTOR_SPEED_PIN);
Motor Drive::_lMotor = Motor(LEFT_MOTOR_DIRECTION_PIN, LEFT_MOTOR_SPEED_PIN);
Semaphore Drive::_sem = _SEMAPHORE_DATA(Drive::_sem, 0);
uint8_t Drive::_rSpeed = 0;
uint8_t Drive::_lSpeed = 0;
Direction Drive::_rDirection = FORWARD;
Direction Drive::_lDirection = FORWARD;

static WORKING_AREA(driveThreadArea, 128);


/**
 * @brief Tells the motors to spin in a given direction, at a given speed
 * @param direction the direction (FORWARD | BACKWARD)
 * @param speed the speed (0 - MOTOR_MAX_SPEED)
 */
void Drive::go(Direction direction, uint8_t speed) {
	if (!_isStarted)
		Drive::start();

	_lDirection = direction;
	_rDirection = direction;

	_rSpeed = speed;
	_lSpeed = speed;

	chSemSignal(&_sem);
}

/**
 * @brief Tells the motors to spin in a given direction, at a given speed, with different speed for right and left motors
 * @param direction the direction (FORWARD | BACKWARD)
 * @param speedR the speed of the right motor (0 - MOTOR_MAX_SPEED)
 * @param speedL the speed of the left motor (0 - MOTOR_MAX_SPEED)
 */
void Drive::turn(Direction direction, uint8_t speedR, uint8_t speedL) {
	if (!_isStarted)
		Drive::start();

	_lDirection = direction;
	_rDirection = direction;

	_rSpeed = speedR;
	_lSpeed = speedL;

	chSemSignal(&_sem);
}

/**
 * @brief Tells the motors to spin in the opposite direction (rotation), at a given speed
 * @param rotation the rotation side (RIGHT | LEFT)
 * @param speed the speed (0 - MOTOR_MAX_SPEED)
 */
void Drive::spin(Rotation rotation, uint8_t speed) {
	if (!_isStarted)
		Drive::start();

	switch (rotation) {
	case LEFT:
		_lDirection = BACKWARD;
		_rDirection = FORWARD;
		break;

	case RIGHT:
		_lDirection = FORWARD;
		_rDirection = BACKWARD;
		break;
	}

	_rSpeed = speed;
	_lSpeed = speed;

	chSemSignal(&_sem);
}

/**
 * @brief Tells the motors to immediately stop spinning
 */
void Drive::stop(void) {
	if (!_isStarted)
		Drive::start();

	_rDirection = _lDirection = FORWARD;
	_rSpeed = _lSpeed = 0;

	chSemSignal(&_sem);
}


void Drive::start(void* arg, tprio_t priority) {
	if (!_isStarted) {
		_isStarted = true;

		(void)chThdCreateStatic(driveThreadArea, sizeof(driveThreadArea),
								priority, thread, arg);
	}
}

msg_t Drive::thread(void* arg) {
	while (!chThdShouldTerminate()) {
		chSemWait(&_sem);

		_rMotor.spin(_rDirection, _rSpeed);
		_lMotor.spin(_lDirection, _lSpeed);
	}

	return (msg_t)0;
}
