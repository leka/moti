#ifndef LEKA_MOTI_ARDUINO_DRIVE_SYSTEM_H_
#define LEKA_MOTI_ARDUINO_DRIVE_SYSTEM_H_

/**
 * @file DriveSystem.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include <Arduino.h>
#include "Motor.h"

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

		void go(bool direction = FORTH, uint8_t speed = DEFAULT_MAX_SPEED) const;

		void spin(bool spinDirection = RIGHT, uint8_t speed = DEFAULT_MAX_SPEED) const;

		// TODO : is it really useful? shouldn't it be part of a dynamic behavior?
		void turn(bool turnDirection = RIGHT, uint8_t speed = DEFAULT_MAX_SPEED) const;

		// void turn(int16_t angle = 45, bool direction = FORTH, uint8_t speed = DEFAULT_MAX_SPEED) const;

		void stop() const;

	private:

		//	VARIABLES
		uint8_t _rightMotorSpeed;
		uint8_t _leftMotorSpeed;

		uint8_t _motorMinSpeed;
		uint8_t _motorMaxSpeed;

		//	CONSTANTS
		static const uint8_t DEFAULT_MIN_SPEED = 0;
		static const uint8_t DEFAULT_MAX_SPEED = 110;

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