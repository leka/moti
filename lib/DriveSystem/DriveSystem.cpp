#include <Arduino.h>
#include "DriveSystem.h"

/**
 * @file DriveSystem.cpp
 * @author Ladislas de Toldi
 * @version 1.0
 */

/**
 * @brief DriveSystem Class Constructor
 *
 * @param directionPin for Moti in its most up-to-date configuration, the pins are as follow: Left Dir = 4 / Left Speed = 5 // Right Dir = 7 / Right Speed = 6
 * @param speedPin
 */
DriveSystem::DriveSystem() {
	_rightMotorSpeed = 0;
	_leftMotorSpeed = 0;

	_rightMotorDirection = FORTH;
	_leftMotorDirection = FORTH;
}

/*
 * @brief DriveSystem go Method
 *
 * @param direction should take 0 for backward, 1 for forward
 * @param speed the speed the motors should have
 */
void DriveSystem::go(Direction direction, uint8_t speed, uint32_t launchTime) {
	uint32_t startTime = chTimeNow();
	uint32_t currentTime = 0;

	_rightMotorDirection = direction;
	_leftMotorDirection = direction;

	while (currentTime < launchTime) {
		currentTime = chTimeNow() - startTime;

		_rightMotorSpeed = currentTime * speed / launchTime;
		_leftMotorSpeed = _rightMotorSpeed;

		activate();
	}	

	_rightMotorSpeed = speed;
	_leftMotorSpeed = speed;
	activate();
}

/*
 * @brief DriveSystem spin Method
 *
 * @param direction should take 0 for backward, 1 for forward
 * @param speed the speed the motors should have
 */
void DriveSystem::spin(SpinDirection spinDirection, uint8_t speed) {
	if(spinDirection == RIGHT) {
		_rightMotorDirection = BACK;
		_leftMotorDirection = FORTH;
	}
	else if(spinDirection == LEFT) {
		_rightMotorDirection = FORTH;
		_leftMotorDirection = BACK;
	}

	_rightMotorSpeed = speed;
	_leftMotorSpeed = speed;

	activate();
}

/*
 * @brief DriveSystem stop Method
 */
void DriveSystem::stop(uint32_t stopTime) {
	uint32_t startTime = chTimeNow();
	uint32_t leftTime = stopTime;

	uint8_t rightInitSpeed = _rightMotorSpeed;
	uint8_t leftInitSpeed = _leftMotorSpeed;

	while (leftTime > 0) {
		leftTime = stopTime - (chTimeNow() - startTime);

		_rightMotorSpeed = leftTime * rightInitSpeed / stopTime;
		_leftMotorSpeed = leftTime * leftInitSpeed / stopTime;
		activate();
	}

	rightMotor.stop();
	leftMotor.stop();
}

/*
 * @brief DriveSystem turn function
 */
void DriveSystem::turn(SpinDirection turnDirection, uint8_t speed) {
	if(turnDirection == RIGHT) {
		_rightMotorSpeed = speed;
		_leftMotorSpeed = speed - 30;
	}
	else if(turnDirection == LEFT) {
		_rightMotorSpeed = speed - 30;
		_leftMotorSpeed = speed;
	}

	_rightMotorDirection = FORTH;
	_leftMotorDirection = FORTH;

	activate();
}

/*
 * @brief DriveSystem activate method
 */
void DriveSystem::activate(void) {
	rightMotor.spin((bool)_rightMotorDirection, _rightMotorSpeed);
	leftMotor.spin((bool)_leftMotorDirection, _leftMotorSpeed);
}

/*
 * @brief DriveSystem turn function
 */
// void DriveSystem::turn(int16_t angle, bool direction, uint8_t speed) const {
// 	// nothing to do here until we check is usefulness of this method...
// }