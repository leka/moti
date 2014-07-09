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

#include "DriveSystem.h"

/**
 * @file DriveSystem.cpp
 * @author Ladislas de Toldi
 * @version 1.0
 */

bool DriveSystem::_isStarted = false;
Semaphore DriveSystem::_sem = _SEMAPHORE_DATA(_sem, 0);
DriveState DriveSystem::_action = NONE;
uint8_t DriveSystem::_speed = 0;
uint16_t DriveSystem::_duration = 0;
Direction DriveSystem::_direction = FORWARD;
Rotation DriveSystem::_rotation = LEFT;

static WORKING_AREA(drivesystemThreadArea, 64);


/**
 * @brief Tells the motors to spin in a given direction, at a given speed, during a given duration
 * @param direction the direction (FORWARD | BACKWARD)
 * @param speed the speed (0 - MOTOR_MAX_SPEED)
 * @param duration the duration (in ms)
 */
void DriveSystem::go(Direction direction, uint8_t speed, uint16_t duration) {
	if (!_isStarted)
		DriveSystem::start();

	_direction = direction;
	_speed = speed;
	_duration = duration;
	_action = GO;

	chSemSignal(&_sem);
}

/**
 * @brief Tells the motors to stop spinning
 */
void DriveSystem::stop(void) {
	if (!_isStarted)
		DriveSystem::start();

	_direction = FORWARD;
	_rotation = LEFT;
	_speed = 0;
	_action = STOP;

	chSemSignal(&_sem);
}

/**
 * @brief Gets the state of the DriveSystem (DriveState)
 * @return one of the available DriveStates
 */
DriveState DriveSystem::getState() {
	return _action;
}


void DriveSystem::start(void* arg, tprio_t priority) {
	if (!_isStarted) {
		_isStarted = true;

		(void)chThdCreateStatic(drivesystemThreadArea,
								sizeof(drivesystemThreadArea),
								priority, thread, arg);
	}
}

msg_t DriveSystem::thread(void* arg) {
	uint16_t count = 0;
	
	while (!chThdShouldTerminate()) {
		chSemWait(&_sem);

		switch (_action) {
		case GO:
			count = 0;
			while ((count++) * DRIVESYSTEM_THREAD_DELAY < _duration) {
				Serial.println(_speed);
				Drive::go(_direction, _speed);
				waitMs(DRIVESYSTEM_THREAD_DELAY);
			}
			break;

		case SPIN:
			/* TODO */
			break;

		case TURN:
			/* TODO */
			break;

		case STOP:
			Drive::stop();
			break;

		case NONE:
			break;
		}

		_action = NONE;
	}

	return (msg_t)0;
}

