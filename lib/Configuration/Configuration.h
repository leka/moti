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

/*
 * @brief The direction pin of the left motor
 */
static const uint8_t LEFT_MOTOR_DIRECTION_PIN = 4;

/*
 * @brief The speed pin of the left motor
 */
static const uint8_t LEFT_MOTOR_SPEED_PIN = 5;

/*
 * @brief The direction pin of the right motor
 */
static const uint8_t RIGHT_MOTOR_DIRECTION_PIN = 7;

/*
 * @brief The speed pin of the right motor
 */
static const uint8_t RIGHT_MOTOR_SPEED_PIN = 6;


/*
 * @brief The maximum speed that a motor can spin
 */
static const uint8_t MOTOR_MAX_SPEED = 255;


/*
 * @brief The delay between two operations in the DriveSystem
 */
static const uint8_t DRIVESYSTEM_THREAD_DELAY = 50;



/*
 * @brief The number of leds on the device
 */
static const uint8_t N_LEDS = 1;


/*
 * @brief The heart led red pin
 */
static const uint8_t HEART_LED_RED_PIN = 11;

/*
 * @brief The heart led green pin
 */
static const uint8_t HEART_LED_GREEN_PIN = 12;

/*
 * @brief The heart led blue pin
 */
static const uint8_t HEART_LED_BLUE_PIN = 13;


/*
 * @brief The delay between two operations in the Light system
 */
static const uint8_t LIGHT_THREAD_DELAY = 30;



/*
 * @brief The threshold that detects whether the device is active or not
 */
static const uint8_t SENSORS_INACTIVITY_THRESHOLD = 75;

/*
 * @brief The time after which the device is said to be inactive
 */
static const uint8_t SENSORS_INACTIVITY_TIME = 10;

/*
 * @brief Activate or not the inactivity checking on the X-axis of the accelerometer (1 to active, 0 otherwise)
 */
static const uint8_t SENSORS_INACTIVITY_X = 1;

/*
 * @brief Activate or not the inactivity checking on the Y-axis of the accelerometer (1 to active, 0 otherwise)
 */
static const uint8_t SENSORS_INACTIVITY_Y = 1;

/*
 * @brief Activate or not the inactivity checking on the Z-axis of the accelerometer (1 to active, 0 otherwise)
 */
static const uint8_t SENSORS_INACTIVITY_Z = 1;

/*
 * @brief The minimum delay between two sensors refresh
 */
static const uint8_t SENSORS_REFRESH_DELAY = 50;

#endif
