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

#ifndef LEKA_MOTI_ARDUINO_DRIVE_H_
#define LEKA_MOTI_ARDUINO_DRIVE_H_

/**
 * @file Drive.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Motor.h"


/**
 * @class DriveSystem
 * @brief DriveSystem gathers all the driving related functions such as going forward, backward, turning and spinning.
 */
class Drive {
public:
	static void __start__(void* arg=NULL, tprio_t priority=NORMALPRIO+2);

	static void go(Direction direction, uint8_t speed);
	static void spin(Rotation rotation, uint8_t speed);
	static void turn(Direction direction, uint8_t speedR, uint8_t speedL);
	static void stop(void);

	static Direction getRDirection(void);
	static Direction getLDirection(void);

	static uint8_t getRSpeed(void);
	static uint8_t getLSpeed(void);

private:
	static uint8_t _r_speed, _l_speed;
	static Direction _r_direction, _l_direction;
	static Motor _r_motor, _l_motor;

	static bool _is_started;

	static Semaphore _sem;
	static msg_t thread(void* arg);
};

#endif
