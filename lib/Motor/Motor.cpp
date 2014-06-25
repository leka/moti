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

/**
 * @brief Motor Class Constructor
 *
 * @param directionPin for Moti in its most up-to-date configuration, the pins are as follow: Left Dir = 4 / Left Speed = 5 // Right Dir = 7 / Right Speed = 6
 * @param speedPin
 */
Motor::Motor(uint8_t directionPin, uint8_t speedPin) : _directionPin(directionPin), _speedPin(speedPin) {
	// nothing to do here
}

/*
 * @brief Motor Spin Method
 *
 * @param direction should take 0 for backward, 1 for frontward
 * @param speed the speed the motor should have
 */
void Motor::spin(bool direction, uint8_t speed) const {
	digitalWrite(_directionPin, direction);
	analogWrite(_speedPin, speed);
}

/*
 * @brief Motor stop Method
 */
void Motor::stop() const{
	digitalWrite(_directionPin, 0);
	digitalWrite(_speedPin, 0);
}

