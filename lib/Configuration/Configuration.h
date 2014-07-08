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

#ifndef LEKA_MOTI_ARDUINO_CONFIGURATION_H_
#define LEKA_MOTI_ARDUINO_CONFIGURATION_H_

#include <Arduino.h>

/**
 * @file Configuration.h
 * @author Ladislas de Toldi & Flavien Raynaud
 * @version 1.0
 */


static const uint8_t LEFT_MOTOR_DIRECTION_PIN = 4;
static const uint8_t LEFT_MOTOR_SPEED_PIN = 5;
static const uint8_t RIGHT_MOTOR_DIRECTION_PIN = 7;
static const uint8_t RIGHT_MOTOR_SPEED_PIN = 6;

static const uint8_t MOTOR_MAX_SPEED = 255;


static const uint8_t DRIVESYSTEM_THREAD_DELAY = 50;


static const uint8_t N_LEDS = 1;

static const uint8_t HEART_LED_RED_PIN = 11;
static const uint8_t HEART_LED_GREEN_PIN = 12;
static const uint8_t HEART_LED_BLUE_PIN = 13;


static const uint8_t LIGHT_THREAD_DELAY = 30;


static const uint8_t SENSORS_INACTIVITY_THRESHOLD = 75;
static const uint8_t SENSORS_INACTIVITY_TIME = 10;
static const uint8_t SENSORS_INACTIVITY_X = 1; /* 1 for activated, 0 else */
static const uint8_t SENSORS_INACTIVITY_Y = 1; /* 1 for activated, 0 else */
static const uint8_t SENSORS_INACTIVITY_Z = 1; /* 1 for activated, 0 else */

static const uint8_t SENSORS_REFRESH_DELAY = 50;

#endif
