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

#ifndef LEKA_MOTI_ARDUINO_MOTOR_H_
#define LEKA_MOTI_ARDUINO_MOTOR_H_

/**
 * @file Motors.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include <Arduino.h>
#include "Moti.h"

/**
 * @class Motor
 * @brief Motor class gathers all the motor functions for Moti.
 */

class Motor {
public:
    Motor(uint8_t direction_pin, uint8_t speed_pin);

    void spin(Direction direction=FORWARD, uint8_t speed=MAX_SPEED);
    void stop(void);

    static const uint8_t MAX_SPEED = 255;

private:
    uint8_t _direction_pin;
    uint8_t _speed_pin;
};

#endif