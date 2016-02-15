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

#ifndef LEKA_MOTI_CLASS_COLOR_H_
#define LEKA_MOTI_CLASS_COLOR_H_

#include <Arduino.h>

/**
 * @file Color.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

class Color {
	public:
		Color();
		Color(uint8_t r, uint8_t g, uint8_t b);

		void getRGB(uint8_t* r, uint8_t* g, uint8_t* b);
		uint8_t getR(void);
		uint8_t getG(void);
		uint8_t getB(void);

		void getHSV(uint16_t* hue, float* saturation, float* value);
		uint16_t getHue(void);
		float getSaturation(void);
		float getValue(void);

		void setRGB(uint8_t r, uint8_t g, uint8_t b);
		void setHSV(uint16_t hue, float value, float saturation);

		bool isEgal(Color const& colora) const;
		// bool EgalEgal(Color const& a, Color const& b);

		static Color randomColor(void);

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
		uint8_t _r, _g, _b;

		uint16_t _hue;
		float _saturation, _value;
};

#endif
