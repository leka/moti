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

namespace Environment {

bool _isStarted = false;
bool _isRunning = false;
bool _isStuck = false;
uint32_t _startStuckTime = 0;

msg_t thread(void* arg);

static WORKING_AREA(environmentThreadArea, 128);


/**
 * @brief Tells the Environment thread to run and check for events
 */
void run(void) {
	_isRunning = true;
}

/**
 * @brief Tells the Environment thread to stop checking for event
 */
void stop(void) {
	_isRunning = false;
	_isStuck = false;
}

/**
 * @brief Returns whether the device is stuck or not
 * @return true if it is stuck, false otherwise
 */
bool isStuck() {
	if (!_isStarted)
		start();

	return _isStuck && (abs(millis() - _startStuckTime) > ENVIRONMENT_STUCK_TIME);
}


void start(void* arg, tprio_t priority) {
	if (!_isStarted) {
		_isStarted = true;

		(void)chThdCreateStatic(environmentThreadArea, sizeof(environmentThreadArea),
				priority, thread, arg);

	}
}

msg_t thread(void* arg) {
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

}
