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
#include "Led.h"


/**
 * @file Led.cpp
 * @author Ladislas de Toldi
 * @version 1.0
 */


Led::Led() { }

Led::Led(uint8_t red_pin, uint8_t green_pin, uint8_t blue_pin) {
	_red_pin = red_pin;
	_green_pin = green_pin;
	_blue_pin = blue_pin;

	_color = Color(0, 0, 0);
}

Led::Led(uint8_t red_pin, uint8_t green_pin, uint8_t blue_pin, Color color) {
	Led(red_pin, green_pin, blue_pin);
	_color = color;
}

void Led::shine(void) {
	Serial.println(_color.getB());
	
	analogWrite(_red_pin, _color.getR());
	analogWrite(_green_pin, _color.getG());
	analogWrite(_blue_pin, _color.getB());
}

void Led::shine(Color color) {
	setColor(color);
	shine();
}

void Led::turnOff(void) {
	setColor(Color(0, 0, 0));
	shine();
}

Color Led::getColor(void) {
	return _color;
}

void Led::setColor(Color color) {
	_color = color;
}
