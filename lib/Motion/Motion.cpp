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
#include "Motion.h"

/**
 * @file Motion.cpp
 * @author Ladislas de Toldi
 * @version 1.0
 */

static WORKING_AREA(motionThreadArea, 256);

namespace Motion {


float _computeAimAngle(Rotation rotation, float originAngle, float angle);
bool _rotationEnded(Rotation rotation, float aimAngle, float* last_angle);

MotionState _action = NONE;
MotionState _oldAction = NONE;
Direction _direction = FORWARD;
Rotation _rotation = LEFT;
uint8_t _speed = 0;
uint16_t _duration = 0;
uint16_t _launchDuration = 0;
float _angle = 0.f;
float _originAngle = 0.f;
bool _jump = false;

bool _isStarted = false;
Semaphore _sem = _SEMAPHORE_DATA(_sem, 0);
static msg_t thread(void *arg);

MUTEX_DECL(_dataMutex);

/**
 * @brief Tells the drivesystem to go straight in a given direction, at a given speed, during a given duration
 * @param direction the direction (FORWARD | BACKWARD)
 * @param speed the speed (0 - MOTOR_MAX_SPEED)
 * @param duration the duration (in ms)
 */
void go(Direction direction, uint8_t speed, uint16_t duration, uint16_t launchDuration) {
	if (!_isStarted)
		start();

	chMtxLock(&_dataMutex);

	_direction = direction;
	_speed = speed;
	_duration = duration;
	_launchDuration = launchDuration;
	_oldAction = _action;
	_action = GO;

	chMtxUnlock();

	chSemSignal(&_sem);
}

/**
 * @brief Tells the drivesystem to spin
 * @param rotation the rotation direction (LEFT | RIGHT)
 * @param speed the speed (0 - MOTOR_MAX_SPEED)
 * @param angle the angle to spin (in radians)
 */
void spin(Rotation rotation, uint8_t speed, float angle) {
	if (!_isStarted)
		start();

	chMtxLock(&_dataMutex);

	_rotation = rotation;
	_speed = speed;
	_angle = angle;
	_originAngle = Sensors::getEulerPhi();
	_jump = false;
	_oldAction = _action;
	_action = SPIN;

	chMtxUnlock();

	chSemSignal(&_sem);
}

/**
 * @brief Tells the drivesystem to spin
 * @param rotation the rotation direction (LEFT | RIGHT)
 * @param speed the speed (0 - MOTOR_MAX_SPEED)
 * @param angle the angle to spin (in degrees)
 */
void spinDeg(Rotation rotation, uint8_t speed, float angle) {
	spin(rotation, speed, angle * M_PI / 180.0f);
}

/**
 * @brief Tells the drivesystem to stop
 */
void stop(uint16_t stopDuration) {
	if (!_isStarted)
		start();

	chMtxLock(&_dataMutex);

	_duration = stopDuration;
	_oldAction = _action;
	_action = STOP;

	chMtxUnlock();

	chSemSignal(&_sem);
}

/**
 * @brief Gets the state of the DriveSystem (DriveState)
 * @return one of the available DriveStates
 */
MotionState getState() {
	return _action;
}


void goForward(uint8_t speed, uint16_t duration) {
	go(FORWARD, speed, duration, 0);
}

void goBackward(uint8_t speed, uint16_t duration) {
	go(BACKWARD, speed, duration, 0);
}

void spinRight(uint8_t speed, float angle) {
	spin(RIGHT, speed, angle);
}

void spinLeft(uint8_t speed, float angle) {
	spin(LEFT, speed, angle);
}

void spinRightDeg(uint8_t speed, float angle) {
	spinDeg(RIGHT, speed, angle);
}

void spinLeftDeg(uint8_t speed, float angle) {
	spinDeg(LEFT, speed, angle);
}

void stopNow(void) {
	stop(0);
}


void start(void* arg, tprio_t priority) {
	if (!_isStarted) {
		_isStarted = true;

		(void)chThdCreateStatic(motionThreadArea,
				sizeof(motionThreadArea),
				priority, thread, arg);
	}
}

float _computeAimAngle(Rotation rotation, float originAngle, float angle) {
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

bool _rotationEnded(Rotation rotation, float aimAngle, float* lastAngle) {
	if (_action != SPIN) /* The action changed, maybe we need to stop */
		return true;

	float currentAngle = Sensors::getEulerPhi();

	if (_jump && ((*lastAngle) * currentAngle < -3.0f))
		_jump = false;

	*lastAngle = currentAngle;

	switch (rotation) {
		case LEFT:
			return (!_jump && (currentAngle < aimAngle));
		case RIGHT:
			return (!_jump && (currentAngle > aimAngle));
	}

	return false;
}

msg_t thread(void* arg) {
	uint16_t count = 0;
	uint16_t nSteps = 0;

	float lastAngle = 0.0f;
	float aimAngle = 0.0f;
	uint32_t spinStart = 0;

	uint8_t delay = DRIVESYSTEM_THREAD_DELAY;

	while (!chThdShouldTerminate()) {
		chSemWait(&_sem);

		if (_action == GO) {
			count = 0;
			while ((_action == GO) && ((_duration == 0) || (count++) * delay < _duration)) {
				if (_launchDuration / delay > count)
					DriveSystem::go(_direction, (count * _speed) / (_launchDuration / delay));
				else
					DriveSystem::go(_direction, _speed);

				waitMs(delay);
			}

			if (_action == GO) {
				chMtxLock(&_dataMutex);

				_oldAction = GO;
				_action = STOP;
				_duration = 0;

				chMtxUnlock();
			}
		}

		if (_action == SPIN) {
			spinStart = millis();

			while (_angle > 0.0f) {
				aimAngle = _computeAimAngle(_rotation, _originAngle, fmod(_angle, 2 * M_PI));
				lastAngle = 0.0f;

				while (!_rotationEnded(_rotation, aimAngle, &lastAngle)) {
					DriveSystem::spin(_rotation, _speed);
					waitMs(delay);

					if (abs(millis() - spinStart) > 2500) /* Security, prevent infinite spinning */
						break;
				}

				chMtxLock(&_dataMutex);
				_angle -= 2 * M_PI;
				chMtxUnlock();
			}

			if (_action == SPIN) {
				chMtxLock(&_dataMutex);

				_oldAction = SPIN;
				_action = STOP;
				_duration = 0;

				chMtxUnlock();
			}
		}

		if (_action == TURN) {
			/* TODO */
		}

		if (_action == STOP) {
			if (_oldAction == GO) {
				count = 0;
				nSteps = _duration / delay;

				while ((count++) * delay < _duration) {
					_speed = _speed - _speed / nSteps;
					DriveSystem::go(_direction, _speed);
					waitMs(delay);
				}
			}

			DriveSystem::stop();

			chMtxLock(&_dataMutex);

			_direction = FORWARD;
			_rotation = LEFT;
			_speed = 0;

			chMtxUnlock();
		}

		chMtxLock(&_dataMutex);

		_action = NONE;
		chMtxUnlock();
	}

	return (msg_t)0;
}

}
