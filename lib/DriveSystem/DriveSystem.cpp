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
float DriveSystem::_angle = 0.0f;
float DriveSystem::_originAngle = 0.0f;
bool DriveSystem::_jump = false;

static WORKING_AREA(drivesystemThreadArea, 512);


/**
 * @brief Tells the drivesystem to go straight in a given direction, at a given speed, during a given duration
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
 * @brief Tells the drivesystem to spin
 * @param rotation the rotation direction (LEFT | RIGHT)
 * @param speed the speed (0 - MOTOR_MAX_SPEED)
 * @param angle the angle to spin (in radians)
 */
void DriveSystem::spin(Rotation rotation, uint8_t speed, float angle) {
	if (!_isStarted)
		DriveSystem::start();

	_rotation = rotation;
	_speed = speed;
	_angle = angle;
	_originAngle = Sensors::getEulerPhi();
	_jump = false;
	_action = SPIN;

	chSemSignal(&_sem);
}

/**
 * @brief Tells the drivesystem to spin
 * @param rotation the rotation direction (LEFT | RIGHT)
 * @param speed the speed (0 - MOTOR_MAX_SPEED)
 * @param angle the angle to spin (in degrees)
 */
void DriveSystem::spinDeg(Rotation rotation, uint8_t speed, float angle) {
	spin(rotation, speed, angle * M_PI / 180.0f);
}

/**
 * @brief Tells the drivesystem to stop
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

float DriveSystem::computeAimAngle(Rotation rotation, float originAngle, float angle) {
	float aimAngle = originAngle;

	switch (rotation) {
	case LEFT:
		aimAngle -= angle;
		break;

	case RIGHT:
		aimAngle += angle;
		break;
	}

	if (aimAngle < -M_PI) {
		_jump = true;
		return aimAngle + 2 * M_PI;
	}
	else if (aimAngle > M_PI) {
		_jump = true;
		return aimAngle - 2 * M_PI;
	}

	return aimAngle;
}

bool DriveSystem::rotationEnded(Rotation rotation, float aimAngle, float* lastAngle) {
	float currentAngle = Sensors::getEulerPhi();

	Serial.print(F("Current angle: "));
	Serial.println(currentAngle);
	Serial.println(*lastAngle);
	Serial.println(_jump);
	Serial.println(aimAngle);

	if (_jump && (*lastAngle * currentAngle < -3.0f)) {
		Serial.println(F("lol"));
		_jump = false;
	}

	*lastAngle = currentAngle;

	Serial.println(_jump);

	switch (rotation) {
	case LEFT:
		return (!_jump && currentAngle < aimAngle);
	case RIGHT:
		return (!_jump && currentAngle > aimAngle);
	}

	return false;
}

msg_t DriveSystem::thread(void* arg) {
	uint16_t count = 0;
	float lastAngle = 0.0f;
	float aimAngle = 0.0f;

	while (!chThdShouldTerminate()) {
		chSemWait(&_sem);

		switch (_action) {
		case GO:
			count = 0;
			while ((_action == GO) && ((_duration == 0) || (count++) * DRIVESYSTEM_THREAD_DELAY < _duration)) {
				Drive::go(_direction, _speed);
				waitMs(DRIVESYSTEM_THREAD_DELAY);
			}
			Drive::stop();
			break;

		case SPIN:
			while (_angle > 0.0f) {
				aimAngle = computeAimAngle(_rotation, _originAngle, _angle);
				lastAngle = 0.0f;

				while ((_action == SPIN) && !rotationEnded(_rotation, aimAngle, &lastAngle)) {
					Drive::spin(_rotation, _speed);
					waitMs(DRIVESYSTEM_THREAD_DELAY);
				}

				_angle -= 2 * M_PI;
			}

			Drive::stop();
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

