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

#include "Environment.h"

/**
 * @file Environment.cpp
 * @author Ladislas de Toldi & Flavien Raynaud
 * @version 1.0
 */


bool Environment::_isStarted = false;
bool Environment::_isRunning = false;
bool Environment::_isStuck = false;
uint32_t Environment::_startStuckTime = 0;

static WORKING_AREA(environmentThreadArea, 128);


void Environment::run(void) {
	_isRunning = true;
}

void Environment::stop(void) {
	_isRunning = false;
	_isStuck = false;
}

bool Environment::isStuck() {
	if (!_isStarted)
		Environment::start();

	return _isStuck && (abs(millis() - _startStuckTime) > ENVIRONMENT_STUCK_TIME);
}


void Environment::start(void* arg, tprio_t priority) {
	if (!_isStarted) {
		_isStarted = true;

		(void)chThdCreateStatic(environmentThreadArea, sizeof(environmentThreadArea),
				priority, thread, arg);

	}
}

msg_t Environment::thread(void* arg) {
	while (!chThdShouldTerminate()) {
		if (_isRunning) {
			if (abs(Sensors::getAccX()) > ENVIRONMENT_STUCK_THRESHOLD) {
				if (!_isStuck) {
					_isStuck = true;
					_startStuckTime = millis();
				}
			}
			else
				_isStuck = false;

		}

		waitMs(ENVIRONMENT_THREAD_DELAY);
	}

	return (msg_t)0;
}
