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


const Color Color::Black = Color(0, 0, 0);
const Color Color::White = Color(255, 255, 255);
const Color Color::RedPure = Color(255, 0, 0);
const Color Color::GreenPure = Color(0, 255, 0);
const Color Color::BluePure = Color(0, 0, 255);
const Color Color::DarkRed = Color(186, 48, 42);
const Color Color::LightRed = Color(222, 63, 89);
const Color Color::Purple = Color(165, 67, 188);
const Color Color::LightBlue = Color(95, 184, 224);
const Color Color::LightPink = Color(255, 232, 225);
const Color Color::Yellow = Color(250, 211, 51);
const Color Color::DarkYellow = Color(244, 174, 51);
const Color Color::Orange = Color(240, 143, 51);
const Color Color::DarkOrange = Color(239, 134, 59);
const Color Color::LightGreen = Color(216, 255, 56);	


/*
 * @brief Default constructor, sets R, G, B to be equal to 0
 */
Color::Color() {
	_r = _g = _b = 0;
}

/*
 * @brief R, G, B constructor (0-255)
 * @param r the red intensity of the color
 * @param g the green intensity of the color
 * @param b the blue intensity of the color
 */
Color::Color(int16_t r, int16_t g, int16_t b) {
	_r = r;
	_g = g;
	_b = b;
}


/**
 * @brief Reads the RGB values (0-255)
 * @param r pointer that will receive the content of the red intensity
 * @param g pointer that will receive the content of the green intensity
 * @param b pointer that will receive the content of the blue intensity
 */
void Color::getRGB(int16_t* r, int16_t* g, int16_t* b) {
	*r = _r;
	*g = _g;
	*b = _b;
}

/**
 * @brief Getter method to get the red intensity of the color (0-255)
 * @return the red intensity
 */
int16_t Color::getR(void) {
	return _r;
}

/**
 * @brief Getter method to get the green intensity of the color (0-255)
 * @return the green intensity
 */
int16_t Color::getG(void) {
	return _g;
}

/**
 * @brief Getter method to get the blue intensity of the color (0-255)
 * @return the blue intensity
 */
int16_t Color::getB(void) {
	return _b;
}

/**
 * @brief Setter method to set the red, green and blue intensities of the color (0-255)
 * @param r the new red intensity of the color
 * @param g the new green intensity of the color
 * @param b the new blue intensity of the color
 */
void Color::setRGB(int16_t r, int16_t g, int16_t b) {
	_r = r;
	_g = g;
	_b = b;
}
