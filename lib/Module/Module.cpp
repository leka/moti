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

#include "Module.h"

/**
 * @file Module.cpp
 * @author Ladislas de Toldi
 * @version 1.0
 */

namespace ModuleName {

	// VARIABLES

	// Thread
	static WORKING_AREA(threadArea, 128);
	bool _isInitialized = false;
	bool _isStarted = false;
	uint16_t _threadDelay = 50;

	// Objects

	// Variables

	// Misc

}

/**
 * @brief Start DriveSystem's chThread
 */
void ModuleName::init(void* arg, tprio_t priority) {
	if (!_isInitialized) {
		_isInitialized = true;

		(void)chThdCreateStatic(threadArea, sizeof(threadArea),
				priority, moduleThread, arg);
	}
}

/**
 * @brief Starts the module
 */
void ModuleName::start(void) {
	_isStarted = true;
}

/**
 * @brief Stops the module
 */
void ModuleName::stop(void) {
	_isStarted = false;
}

/**
 * @brief A method the Module should execute
 */
void ModuleName::aModuleMethod(void) {
	// do stuff you want here
}

/**
 * @brief Main module thread
 */
msg_t ModuleName::moduleThread(void* arg) {
	(void) arg;

	while (!chThdShouldTerminate()) {

		if(_isStarted) {
			aModuleMethod();
			// and everything else you want
		}

		waitMs(_threadDelay);
	}

	return (msg_t)0;
}


