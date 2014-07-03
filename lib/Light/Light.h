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

#ifndef LEKA_MOTI_ARDUINO_LIGHT_H_
#define LEKA_MOTI_ARDUINO_LIGHT_H_

/**
 * @file Light.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include <Arduino.h>

#include "ChibiOS_AVR.h"
#include "Color.h"
#include "Led.h"


/**
 * @class Led
 * @brief Led library gathers all the LED functions for Moti.
 */

class Light: public Led {
public:
    Light();
    Light(uint8_t red_pin, uint8_t green_pin, uint8_t blue_pin);

    void fade(Color start_color, Color end_color, uint16_t duration);
};

#endif
