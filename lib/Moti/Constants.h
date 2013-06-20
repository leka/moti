#ifndef __ROBOT_LEKA_ARDUINO_CONSTANTS_H_
#define __ROBOT_LEKA_ARDUINO_CONSTANTS_H_

#include "Arduino.h"

	//	CONSTANTS
	const int DEFAULT_GLOBAL_DELAY            = 75;
	const int DEFAULT_SLEEP_DELAY             = 600;
	const int DEFAULT_AWAKE_THRESHOLD         = 300;
	const int DEFAULT_DELTA_ACCEL_THRESHOLD   = 200;
	const int DEFAULT_HIGH_ACTIVITY_THRESHOLD = 80;

	const uint8_t DEFAULT_LED_MAX_BRIGHTNESS   = 255;
	const uint8_t DEFAULT_RED_MAX_BRIGHTNESS   = 255;
	const uint8_t DEFAULT_GREEN_MAX_BRIGHTNESS = 255;
	const uint8_t DEFAULT_BLUE_MAX_BRIGHTNESS  = 255;

	//	MOTOR PINS
	const uint8_t leftMotorSpeedPin      = 5;
	const uint8_t leftMotorDirectionPin  = 4;
	const uint8_t rightMotorSpeedPin     = 6;
	const uint8_t rightMotorDirectionPin = 7;

	//	LED PINS
	const uint8_t RED_PIN   = 9;
	const uint8_t GREEN_PIN = 10;
	const uint8_t BLUE_PIN  = 11;

#endif
