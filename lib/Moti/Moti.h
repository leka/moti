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

#ifndef LEKA_MOTI_ARDUINO_MOTI_H_
#define LEKA_MOTI_ARDUINO_MOTI_H_

/**
 * @file Moti.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include "ChibiOS_AVR.h"
#include "Color.h"


/*! Direction enumeration, for the DriveSystem */
typedef enum {
	BACKWARD,
	FORWARD
} Direction;

/*! Rotation enumeration, for the DriveSystem spin */
typedef enum {
	LEFT,
	RIGHT
} Rotation;

/*! All the DriveStates the DriveSystem can be */
typedef enum {
	GO,
	SPIN,
	TURN,
	STOP,
	NONE
} DriveState;


/*! Indicators for the leds in the device */
typedef enum {
	HEART
} LedIndicator;

/*! All the LedStates a led can be */
typedef enum {
	FADE,
	SHINE,
	INACTIVE
} LedState;

typedef struct {
	Color startColor, endColor, diff, current;
	int16_t totalSteps, steps;
	LedState state;
} LedData;

void waitMs(uint16_t ms);

#endif
