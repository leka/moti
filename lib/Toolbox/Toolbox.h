/*
   Copyright (C) 2013-2014 Ladislas de Toldi <ladislas at weareleka dot com>
   and Leka <http://weareleka.com>

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

#ifndef LEKA_MOTI_MODULE_TOOLBOX_H_
#define LEKA_MOTI_MODULE_TOOLBOX_H_

/**
 * @file Toolbox.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include <Arduino.h>
#include <math.h>

namespace Toolbox {

	float mod(float a, float b);
	float diffAngle(float a, float b);
	float arrayDeltaSum(float* array, uint8_t size);

}

#endif
