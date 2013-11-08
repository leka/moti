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
class Motors {

	public:

		Motors();

		void init();

		//	SET CONSTANTS
		void setMotorMinSpeed(uint8_t value);
		void setMotorMaxSpeed(uint8_t value);


		//	GET CONSTANTS
		int getMotorMinSpeed();
		int getMotorMaxSpeed();


    	//	RESET CONSTANTS
		void resetMotorMinSpeed();
		void resetMotorMaxSpeed();


		//	MOTORS
		void spinRightWheel(uint8_t speed, bool direction);
		void spinLeftWheel(uint8_t speed, bool direction);

		void goForward();
		void goForward(int speed);

		void goBackward();
		void goBackward(int speed);

		void goLeft();
		void goLeft(int speed);
		void goRight();
		void goRight(int speed);

		void spinLeft();
		void spinLeft(int speed);
		void spinRight();
		void spinRight(int speed);

		void stop();

	private:

		//	VARIABLES

		uint8_t rightMotorSpeedPin;
		uint8_t rightMotorDirectionPin;
		uint8_t leftMotorSpeedPin;
		uint8_t leftMotorDirectionPin;

		uint16_t rightMotorSpeed, rightMotorSpeedBuffer;
		uint16_t leftMotorSpeed, leftMotorSpeedBuffer;

		uint8_t _motorMinSpeed;
		uint8_t _motorMaxSpeed;


		//	CONSTANTS
		static const uint8_t DEFAULT_MIN_MOTOR_SPEED = 90;
		static const uint8_t DEFAULT_MAX_MOTOR_SPEED = 255;

		static const uint8_t turnCoefficientTime = 80;
		static const uint8_t turnCoefficientDiv = 100;

		//	MOTOR PINS
		static const uint8_t DEFAULT_LEFT_MOTOR_SPEED_PIN      = 5;
		static const uint8_t DEFAULT_LEFT_MOTOR_DIRECTION_PIN  = 4;
		static const uint8_t DEFAULT_RIGHT_MOTOR_SPEED_PIN     = 6;
		static const uint8_t DEFAULT_RIGHT_MOTOR_DIRECTION_PIN = 7;
};

#endif