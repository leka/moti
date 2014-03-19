#ifndef LEKA_MOTI_ARDUINO_DRIVE_SYSTEM_H_
#define LEKA_MOTI_ARDUINO_DRIVE_SYSTEM_H_

/**
 * @file DriveSystem.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include <Arduino.h>
#include "Motor.h"
#include "ChibiOS_AVR.h"

	enum Direction {
		BACK,
		FORTH
	};

	enum SpinDirection {
		RIGHT,
		LEFT
	};

/**
 * @class DriveSystem
 * @brief DriveSystem gathers all the driving related functions such as going forward, backward, turning and spinning.
 */
class DriveSystem {

	public:

		DriveSystem();

		void go(Direction direction = FORTH, uint8_t speed = DEFAULT_MAX_SPEED, uint32_t launchTime = 250);

		void spin(SpinDirection spinDirection = RIGHT, uint8_t speed = DEFAULT_MAX_SPEED);

		// TODO : is it really useful? shouldn't it be part of a dynamic behavior?
		void turn(SpinDirection turnDirection = RIGHT, uint8_t speed = DEFAULT_MAX_SPEED);

		// void turn(int16_t angle = 45, bool direction = FORTH, uint8_t speed = DEFAULT_MAX_SPEED) const;

		void stop(uint32_t stopTime = 250);

	private:

		//	VARIABLES
		uint8_t _rightMotorSpeed;
		uint8_t _leftMotorSpeed;

		Direction _rightMotorDirection;
		Direction _leftMotorDirection;

		uint8_t _motorMinSpeed;
		uint8_t _motorMaxSpeed;

		void activate();

		//	CONSTANTS
		static const uint8_t DEFAULT_MIN_SPEED = 0;
		static const uint8_t DEFAULT_MAX_SPEED = 220;

		//	MOTOR PINS
		static const uint8_t DEFAULT_LEFT_MOTOR_SPEED_PIN      = 5;
		static const uint8_t DEFAULT_LEFT_MOTOR_DIRECTION_PIN  = 4;
		static const uint8_t DEFAULT_RIGHT_MOTOR_SPEED_PIN     = 6;
		static const uint8_t DEFAULT_RIGHT_MOTOR_DIRECTION_PIN = 7;

		//	RIGHT & LEFT MOTOR INSTANCES
		Motor rightMotor = Motor(DEFAULT_RIGHT_MOTOR_DIRECTION_PIN, DEFAULT_RIGHT_MOTOR_SPEED_PIN);
		Motor leftMotor = Motor(DEFAULT_LEFT_MOTOR_DIRECTION_PIN, DEFAULT_LEFT_MOTOR_SPEED_PIN);

};

#endif