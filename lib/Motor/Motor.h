#ifndef LEKA_MOTI_ARDUINO_MOTORS_H_
#define LEKA_MOTI_ARDUINO_MOTORS_H_

/**
 * @file Motors.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include <Arduino.h>


/**
 * @class Motors
 * @brief Motors class gathers all the Motors functions for Moti.
 */
class Motor {

	public:

		Motor(uint8_t directionPin, uint8_t speedPin);

		Motor(uint8_t directionPin, uint8_t speedPin, uint8_t minSpeed, uint8_t maxSpeed);

		void spin(bool direction, uint8_t speed = DEFAULT_MAX_SPEED);

	private:

		//	VARIABLES
		uint8_t _speedPin;
		uint8_t _directionPin;

		uint8_t _speed, _speedBuffer;


		uint8_t _minSpeed;
		uint8_t _maxSpeed;


		//	CONSTANTS
		static const uint8_t DEFAULT_MIN_SPEED = 0;
		static const uint8_t DEFAULT_MAX_SPEED = 255;
};

#endif