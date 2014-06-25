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

#include "Tools.h"

/* Safe 8 bit absolute function */
int8_t sabs8(int8_t i){
    int8_t absValue;

    if (INT8_MIN == i) {
        absValue = INT8_MAX;
    }
    else {
        absValue = i < 0 ? -i : i;
    }

    return absValue;
}

/* Safe 16 bit absolute function */
int16_t sabs16(int16_t i)
{
    int16_t absValue;

    if (INT16_MIN == i) {
        absValue = INT16_MAX;
    }
    else {
        absValue = i < 0 ? -i : i;
    }

    return absValue;
}

/* Safe 32 bit absolute function */
int32_t sabs32(int32_t i)
{
    int32_t absValue;

    if (INT32_MIN == i) {
        absValue = INT32_MAX;
    }
    else {
        absValue = i < 0 ? -i : i;
    }

    return absValue;
}