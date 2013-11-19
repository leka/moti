#include <Arduino.h>
#include "Motor.h"

/**
 * @file Motors.cpp
 * @author Ladislas de Toldi
 * @version 1.0
 */

/**
 * @brief Motors Class Constructor
 *
 * @param directionPin for Moti in its most up-to-date configuration, the pins are as follow: Left Dir = 4 / Left Speed = 5 // Right Dir = 7 / Right Speed = 6
 * @param speedPin
 */
Motor::Motor(uint8_t directionPin, uint8_t speedPin) : _directionPin(directionPin), _speedPin(speedPin), _minSpeed(DEFAULT_MIN_SPEED), _maxSpeed(DEFAULT_MAX_SPEED) {
	// nothing to do here
}

/**
 * @brief Motors Class Constructor
 *
 * @param directionPin
 * @param speedPin
 * @param minSpeed
 * @param maxSpeed
 */
Motor::Motor(uint8_t directionPin, uint8_t speedPin, uint8_t minSpeed, uint8_t maxSpeed) : _directionPin(directionPin), _speedPin(speedPin), _minSpeed(minSpeed), _maxSpeed(maxSpeed){
	// nothing to do here
}

/*
 * @brief Motor Spin Method
 *
 * @param direction should take 0 for backward, 1 for frontward
 * @param speed the speed the motor should have
 */
void Motor::spin(bool direction, uint8_t speed) const {
	digitalWrite(_directionPin, direction);
	analogWrite(_speedPin, speed);
}

/*
 * @brief Motor stop Method
 *
 * @param direction should take 0 for backward, 1 for frontward
 * @param speed the speed the motor should have
 */
void Motor::stop() const{
	digitalWrite(_directionPin, 0);
	digitalWrite(_speedPin, 0);
}

