#ifndef LEKA_ARDUINO_ROBOT_MOTI_Motors_H_
#define LEKA_ARDUINO_ROBOT_MOTI_Motors_H_

/**
 * @file MotiMotors.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include "Arduino.h"


/**
 * @class MotiMotors
 * @brief MotiMotors class gathers all the Motors functions for Moti.
 */
class MotiMotors {

	public:

		MotiMotors();

		//	SET CONSTANTS
		void setMotorMinSpeed(int value);
		void setMotorMaxSpeed(int value);


		//	GET CONSTANTS
		int getMotorMinSpeed();
		int getMotorMaxSpeed();


    	//	RESET CONSTANTS
		void resetMotorMinSpeed();
		void resetMotorMaxSpeed();


		//	MOVING STATE
		bool getMovingState();
		void setMovingState(bool state);


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

		bool _stateMoving;

		//	CONSTANTS
		static const uint8_t DEFAULT_MIN_MOTOR_SPEED = 0;
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