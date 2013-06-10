#ifndef __COM_LEKA_ARDUINO_CONSTANTS_H_
#define __COM_LEKA_ARDUINO_CONSTANTS_H_

#include "Arduino.h"

class Constants {

	public:

		Constants();

		// //	CONSTANTS
		// const int DEFAULT_GLOBAL_DELAY;
		// const int DEFAULT_SLEEP_DELAY;
		// const int DEFAULT_AWAKE_THRESHOLD;
		// const int DEFAULT_DELTA_ACCEL_THRESHOLD;
		// const int DEFAULT_HIGH_ACTIVITY_THRESHOLD;

		// const int DEFAULT_LED_MAX_BRIGHTNESS;
		// const int DEFAULT_RED_MAX_BRIGHTNESS;
		// const int DEFAULT_GREEN_MAX_BRIGHTNESS;
		// const int DEFAULT_BLUE_MAX_BRIGHTNESS;

		// //	MOTOR PINS
		// const int leftMotorSpeedPin;
		// const int leftMotorDirectionPin;
		// const int rightMotorSpeedPin;
		// const int rightMotorDirectionPin;

		// //	LED PINS
		// const int RED_PIN;
		// const int GREEN_PIN;
		// const int BLUE_PIN;

			//	CONSTANTS
const int DEFAULT_GLOBAL_DELAY = 75;
const int DEFAULT_SLEEP_DELAY = 600;
const int DEFAULT_AWAKE_THRESHOLD = 300;
const int DEFAULT_DELTA_ACCEL_THRESHOLD = 200;
const int DEFAULT_HIGH_ACTIVITY_THRESHOLD = 80;

const int DEFAULT_LED_MAX_BRIGHTNESS = 255;
const int DEFAULT_RED_MAX_BRIGHTNESS = 255;
const int DEFAULT_GREEN_MAX_BRIGHTNESS = 255;
const int DEFAULT_BLUE_MAX_BRIGHTNESS = 255;

//	MOTOR PINS
const int leftMotorSpeedPin = 5;
const int leftMotorDirectionPin = 4;
const int rightMotorSpeedPin = 6;
const int rightMotorDirectionPin = 7;

//	LED PINS
const int RED_PIN = 9;
const int GREEN_PIN = 10; 
const int BLUE_PIN = 11;


};

#endif