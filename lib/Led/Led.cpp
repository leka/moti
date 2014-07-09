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


/**
 * @brief Default constructor
 */
Led::Led() { }

/**
 * @brief Instantiates a new led, given its red, green and blue pins
 * @param redPin the red pin
 * @param greenPin the green pin
 * @param bluePin the blue pin
 */
Led::Led(uint8_t redPin, uint8_t greenPin, uint8_t bluePin) {
	_redPin = redPin;
	_greenPin = greenPin;
	_bluePin = bluePin;

	_color = Color(0, 0, 0);
}

/**
 * @brief Instantiates a new led, given its red, green and blue pins and a starting color
 * @param redPin the red pin
 * @param greenPin the green pin
 * @param bluePin the blue pin
 * @param color the start color
 */
Led::Led(uint8_t redPin, uint8_t greenPin, uint8_t bluePin, Color color) {
	Led(redPin, greenPin, bluePin);
	_color = color;
}

/**
 * @brief Tells the led to shine with its color
 */
void Led::shine(void) {
	Serial.println(_color.getB());
	
	analogWrite(_redPin, _color.getR());
	analogWrite(_greenPin, _color.getG());
	analogWrite(_bluePin, _color.getB());
}

/**
 * @brief Tells the led to shine with a given color
 * @param color the color the led will shine
 */
void Led::shine(Color color) {
	setColor(color);
	shine();
}

/**
 * @brief Tells the led to stop shining
 */
void Led::turnOff(void) {
	setColor(Color(0, 0, 0));
	shine();
}

/**
 * @brief Getter method to get the color of the led
 */
Color Led::getColor(void) {
	return _color;
}

/**
 * @brief Setter method to set the color of the led
 * @param color the new color of the led
 */
void Led::setColor(Color color) {
	_color = color;
}
