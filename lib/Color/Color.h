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

#ifndef LEKA_MOTI_ARDUINO_COLOR_H_
#define LEKA_MOTI_ARDUINO_COLOR_H_

#include <Arduino.h>

/**
 * @file Color.h
 * @author Ladislas de Toldi
 * @version 1.0
 */


class Color {
	public:
		Color();
		Color(int16_t r, int16_t g, int16_t b);

		void getRGB(int16_t *r, int16_t* g, int16_t* b);
		int16_t getR(void);
		int16_t getG(void);
		int16_t getB(void);

		void setRGB(int16_t r, int16_t g, int16_t b);

		static const Color Black;
		static const Color White;
		static const Color RedPure;
		static const Color GreenPure;
		static const Color BluePure;
		static const Color DarkRed;
		static const Color LightRed;
		static const Color Purple;
		static const Color LightBlue;
		static const Color LightPink;
		static const Color Yellow;
		static const Color DarkYellow;
		static const Color Orange;
		static const Color DarkOrange;
		static const Color LightGreen;	

	private:
		int16_t _r, _g, _b;
};

#endif
