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
#include "Moti.h"


/**
 * @class Led
 * @brief Led library gathers all the LED functions for Moti.
 */

#define N_LEDS 1

class Light {
	public:
		static void fade(LedIndicator led, Color startColor, Color endColor, int16_t duration);
		static void turnOff(LedIndicator led);
		static LedState getState(LedIndicator led);

	private:
		static void init(void);
		static void start(void* arg=NULL, tprio_t priority=NORMALPRIO+1);

		static Led leds[N_LEDS];
		static LedData data[N_LEDS];

		static Semaphore _sem;
		static msg_t thread(void* arg);
		static bool _isInit, _isStarted;
};

#endif
