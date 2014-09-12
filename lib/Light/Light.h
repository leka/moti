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
#include "Configuration.h"
#include "Color.h"
#include "Led.h"
#include "Moti.h"
#include "Queue.h"

typedef struct {
	Color startColor, endColor, diff, current;
	int16_t totalSteps, steps;
	LedState state;
} LedData;

/**
 * @class Led
 * @brief Led library gathers all the LED functions for Moti.
 */

#define N_LEDS 1

namespace Light {
	void start(void* arg=NULL, tprio_t priority=NORMALPRIO+1);

	void fade(LedIndicator led, Color startColor, Color endColor, int16_t duration);
	void turnOff(LedIndicator led);
	LedState getState(LedIndicator led);
	Color getColor(LedIndicator led);

   /* Easy use function */
   void fadeHeart(Color startColor, Color endColor, int16_t duration);
   void turnHeartOff();
   LedState getHeartState(void);
   Color getHeartColor(void);
}

#endif
