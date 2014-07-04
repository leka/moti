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
#include "Motor.h"

/**
 * @file Motor.cpp
 * @author Ladislas de Toldi
 * @version 1.0
 */

Motor::Motor(uint8_t direction_pin, uint8_t speed_pin) {
	_direction_pin = direction_pin;
	_speed_pin = speed_pin;
}

void Motor::spin(Direction direction, uint8_t speed) {
	digitalWrite(_direction_pin, direction);
	analogWrite(_speed_pin, speed);
}

void Motor::stop(void) {
	spin(FORWARD, 0);
}