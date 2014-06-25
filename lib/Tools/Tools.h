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

#ifndef TOOLS_H_
#define TOOLS_H_

/**
 * @file Tools.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include <stdio.h>

//	Methods
int8_t sabs8(int8_t i);
int16_t sabs16(int16_t i);
int32_t sabs32(int32_t i);

//	Constants
static const int8_t INT8_MIN = -128;
static const int8_t INT8_MAX = 127;
static const int16_t INT16_MIN = -32768;
static const int16_t INT16_MAX = 32767;
static const int32_t INT32_MIN = -2147483647;
static const int32_t INT32_MAX = 2147483647;



#endif