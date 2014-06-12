#ifndef LEKA_MOTI_ARDUINO_DRIVE_SYSTEM_H_
#define LEKA_MOTI_ARDUINO_DRIVE_SYSTEM_H_

/**
 * @file DriveSystem.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Motor.h"

#include "Sensors.h"

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

		void go(Direction direction = FORTH, uint8_t speed = DEFAULT_MAX_SPEED, uint32_t time = 0, uint16_t launchTime = 250);

		void launch(Direction direction = FORTH, uint8_t speed = DEFAULT_MAX_SPEED, uint16_t launchTime = 250);

		void spin(Sensors &sensors, SpinDirection spinDirection = RIGHT, uint8_t speed = DEFAULT_MAX_SPEED, uint16_t angle = 90);

		// TODO : is it really useful? shouldn't it be part of a dynamic behavior?
		void turn(SpinDirection turnDirection = RIGHT, uint8_t speed = DEFAULT_MAX_SPEED);

		// void turn(int16_t angle = 45, bool direction = FORTH, uint8_t speed = DEFAULT_MAX_SPEED) const;

		void stop(uint32_t stopTime = 250);

		void activate();

	private:

		// VARIABLES
		uint8_t rSpeed;
		uint8_t lSpeed;

		Direction rDirection;
		Direction lDirection;

		// MOTOR PINS
		static const uint8_t DEFAULT_LEFT_MOTOR_SPEED_PIN      = 5;
		static const uint8_t DEFAULT_LEFT_MOTOR_DIRECTION_PIN  = 4;
		static const uint8_t DEFAULT_RIGHT_MOTOR_SPEED_PIN     = 6;
		static const uint8_t DEFAULT_RIGHT_MOTOR_DIRECTION_PIN = 7;

		// CONSTANTS
		static const uint8_t DEFAULT_MIN_SPEED = 0;
  	static const uint8_t DEFAULT_MAX_SPEED = 220;

		// RIGHT & LEFT MOTOR INSTANCES
		Motor rMotor, lMotor;

		FreeIMU AccelGyro;
};

#endif
