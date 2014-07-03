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

#include "Color.h"


/**
 * @file Color.cpp
 * @author Ladislas de Toldi
 * @version 1.0
 */

Color::Color() {
    _r = _g = _b = 0;
}

Color::Color(uint8_t r, uint8_t g, uint8_t b) {
    _r = r;
    _g = g;
    _b = b;
}

void Color::getRGB(uint8_t* r, uint8_t* g, uint8_t* b) {
    *r = _r;
    *g = _g;
    *b = _b;
}

uint8_t Color::getR(void) {
    return _r;
}

uint8_t Color::getG(void) {
    return _g;
}

uint8_t Color::getB(void) {
    return _b;
}

void Color::setRGB(uint8_t r, uint8_t g, uint8_t b) {
    _r = r;
    _g = g;
    _b = b;
}
