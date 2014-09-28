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

#include "DriveSystem.h"

/**
 * @file DriveSystem.cpp
 * @author Ladislas de Toldi
 * @version 1.0
 */

namespace DriveSystem {

	// VARIABLES

	// Thread
	// no thread here

	// Motor objects
	uint8_t LEFT_MOTOR_DIRECTION_PIN = 4;
	uint8_t LEFT_MOTOR_SPEED_PIN = 5;
	uint8_t RIGHT_MOTOR_DIRECTION_PIN = 7;
	uint8_t RIGHT_MOTOR_SPEED_PIN = 6;

	Motor _rightMotor = Motor(RIGHT_MOTOR_DIRECTION_PIN, RIGHT_MOTOR_SPEED_PIN);
	Motor _leftMotor  = Motor(LEFT_MOTOR_DIRECTION_PIN, LEFT_MOTOR_SPEED_PIN);

	// Motors variables
	uint8_t _rightSpeed = 0;
	uint8_t _leftSpeed  = 0;
	Direction _rightMotorDirection = FORWARD;
	Direction _leftMotorDirection  = FORWARD;

	uint8_t _returnRightSpeed = 0;
	uint8_t _returnLeftSpeed  = 0;
	Direction _returnRightMotorDirection = FORWARD;
	Direction _returnLeftMotorDirection  = FORWARD;

	// ChibiOS
	MUTEX_DECL(_DriveSystemDataMutex);

}

void DriveSystem::setRightMotorDirection(Direction dir) {

	chMtxLock(&_DriveSystemDataMutex);
	_rightMotorDirection = dir;
	chMtxUnlock();

}

void DriveSystem::setLeftMotorDirection(Direction dir) {

	chMtxLock(&_DriveSystemDataMutex);
	_leftMotorDirection = dir;
	chMtxUnlock();

}

void DriveSystem::setRightMotorSpeed(uint8_t speed) {

	chMtxLock(&_DriveSystemDataMutex);
	_rightSpeed = speed;
	chMtxUnlock();

}

void DriveSystem::setLeftMotorSpeed(uint8_t speed) {

	chMtxLock(&_DriveSystemDataMutex);
	_leftSpeed = speed;
	chMtxUnlock();

}

/**
 * @brief Tells the motors to spin in a given direction, at a given speed
 * @param direction the direction (FORWARD | BACKWARD)
 * @param speed the speed (0 - MOTOR_MAX_SPEED)
 */
void DriveSystem::go(Direction direction, uint8_t speed) {

	setRightMotorDirection(direction);
	setLeftMotorDirection(direction);

	setRightMotorSpeed(speed);
	setLeftMotorSpeed(speed);

	_rightMotor.spin(getRightMotorDirection(), getRightMotorSpeed());
	_leftMotor.spin(getLeftMotorDirection(), getLeftMotorSpeed());

}

/**
 * @brief Tells the motors to spin in a given direction, at a given speed, with different speed for right and left motors
 * @param direction the direction (FORWARD | BACKWARD)
 * @param rightSpeed the speed of the right motor (0 - MOTOR_MAX_SPEED)
 * @param leftSpeed the speed of the left motor (0 - MOTOR_MAX_SPEED)
 */
void DriveSystem::turn(Direction direction, uint8_t rightSpeed, uint8_t leftSpeed) {

	setRightMotorDirection(direction);
	setLeftMotorDirection(direction);

	setRightMotorSpeed(rightSpeed);
	setLeftMotorSpeed(leftSpeed);

	_rightMotor.spin(getRightMotorDirection(), getRightMotorSpeed());
	_leftMotor.spin(getLeftMotorDirection(), getLeftMotorSpeed());

}

/**
 * @brief Tells the motors to spin in the opposite direction (rotation), at a given speed
 * @param rotation the rotation side (RIGHT | LEFT)
 * @param speed the speed (0 - MOTOR_MAX_SPEED)
 */
void DriveSystem::spin(Rotation rotation, uint8_t speed) {

	switch (rotation) {
		case LEFT:
			setRightMotorDirection(FORWARD);
			setLeftMotorDirection(BACKWARD);
			break;

		case RIGHT:
			setRightMotorDirection(BACKWARD);
			setLeftMotorDirection(FORWARD);
			break;
	}

	setRightMotorSpeed(speed);
	setLeftMotorSpeed(speed);

	_rightMotor.spin(getRightMotorDirection(), getRightMotorSpeed());
	_leftMotor.spin(getLeftMotorDirection(), getLeftMotorSpeed());

}

/**
 * @brief Tells the motors to immediately stop spinning
 */
void DriveSystem::stop(void) {

	setRightMotorDirection(FORWARD);
	setLeftMotorDirection(FORWARD);

	setRightMotorSpeed(0);
	setLeftMotorSpeed(0);

	_rightMotor.stop();
	_leftMotor.stop();

}

Direction DriveSystem::getRightMotorDirection(void) {

	chMtxLock(&_DriveSystemDataMutex);
	_returnRightMotorDirection = _rightMotorDirection;
	chMtxUnlock();

	return _returnRightMotorDirection;

}

Direction DriveSystem::getLeftMotorDirection(void) {

	chMtxLock(&_DriveSystemDataMutex);
	_returnLeftMotorDirection = _leftMotorDirection;
	chMtxUnlock();

	return _returnLeftMotorDirection;

}

uint8_t DriveSystem::getRightMotorSpeed(void) {

	chMtxLock(&_DriveSystemDataMutex);
	_returnRightSpeed = _rightSpeed;
	chMtxUnlock();

	return _returnRightSpeed;

}

uint8_t DriveSystem::getLeftMotorSpeed(void) {

	chMtxLock(&_DriveSystemDataMutex);
	_returnLeftSpeed = _leftSpeed;
	chMtxUnlock();

	return _returnLeftSpeed;

}


