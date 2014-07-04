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


bool Drive::_is_started = false;
Motor Drive::_r_motor = Motor(7, 6);
Motor Drive::_l_motor = Motor(4, 5);
Semaphore Drive::_sem = _SEMAPHORE_DATA(Drive::_sem, 0);
uint8_t Drive::_r_speed = 0;
uint8_t Drive::_l_speed = 0;
Direction Drive::_r_direction = FORWARD;
Direction Drive::_l_direction = FORWARD;

static WORKING_AREA(drive_thread_area, 128);

void Drive::__start__(void* arg, tprio_t priority) {
	if (!_is_started) {
		_is_started = true;

		(void)chThdCreateStatic(drive_thread_area, sizeof(drive_thread_area),
								priority, thread, arg);
	}
}

void Drive::go(Direction direction, uint8_t speed) {
	if (!_is_started)
		Drive::__start__();

	_l_direction = direction;
	_r_direction = direction;

	_r_speed = speed;
	_l_speed = speed;

	chSemSignal(&_sem);
}

void Drive::turn(Direction direction, uint8_t speedR, uint8_t speedL) {
	if (!_is_started)
		Drive::__start__();

	_l_direction = direction;
	_r_direction = direction;

	_r_speed = speedR;
	_l_speed = speedL;

	chSemSignal(&_sem);
}

void Drive::spin(Rotation rotation, uint8_t speed) {
	if (!_is_started)
		Drive::__start__();

	switch (rotation) {
	case LEFT:
		_l_direction = BACKWARD;
		_r_direction = FORWARD;
		break;

	case RIGHT:
		_l_direction = FORWARD;
		_r_direction = BACKWARD;
		break;
	}

	_r_speed = speed;
	_l_speed = speed;

	chSemSignal(&_sem);
}

void Drive::stop(void) {
	_r_direction = _l_direction = FORWARD;
	_r_speed = _l_speed = 0;

	chSemSignal(&_sem);
}

Direction Drive::getRDirection(void) {
	return _r_direction;
}

Direction Drive::getLDirection(void) {
	return _l_direction;
}

uint8_t Drive::getRSpeed(void) {
	return _r_speed;
}

uint8_t Drive::getLSpeed(void) {
	return _l_speed;
}

msg_t Drive::thread(void* arg) {
	while (!chThdShouldTerminate()) {
		chSemWait(&_sem);

		_r_motor.spin(_r_direction, _r_speed);
		_l_motor.spin(_l_direction, _l_speed);
	}

	return (msg_t)0;
}
