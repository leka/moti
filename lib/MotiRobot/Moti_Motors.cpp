#include "Moti.h"
#include "Arduino.h"

//########//
// MOTORS //
//########//

/**
 * @brief Method used to initialize all motor pins as OUTPUT.
 */
void MOTI::initializeMotors(){
	pinMode(leftMotorSpeedPin, OUTPUT);
	pinMode(leftMotorDirectionPin, OUTPUT);
	pinMode(rightMotorSpeedPin, OUTPUT);
	pinMode(rightMotorDirectionPin, OUTPUT);

	stop();
}
/**
 * @ brief Method used to spin the right wheel of the robot.
 *
 * @param speed the speed of the wheel, between 0-255
 * @param direction the direction of the wheel, 1 for to go forward,  0 to go backwar
 */
void MOTI::spinRightWheel(uint8_t speed, bool direction){
	analogWrite(rightMotorSpeedPin, speed);
	digitalWrite(rightMotorDirectionPin, direction);
}

/**
 * @ brief Method used to spin the left wheel of the robot.
 *
 * @param speed the speed of the wheel, between 0-255
 * @param direction the direction of the wheel, 1 for to go forward,  0 to go backwar
 */
void MOTI::spinLeftWheel(uint8_t speed, bool direction){
	analogWrite(leftMotorSpeedPin, speed);
	digitalWrite(leftMotorDirectionPin, direction);
}

/**
 * @brief Method used to go forward at full speed.
 */
void MOTI::goForward(){
	spinLeftWheel(255, 1);
	spinRightWheel(255, 1);

	setMovingState(true);
}

/**
 * @brief Method used to go forward
 *
 * @param speed the speed wanted, should be between 0-255
 */
void MOTI::goForward(int speed){
	int _speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel(_speed, 1);
	spinRightWheel(_speed, 1);

	setMovingState(true);
}

/**
 * @brief Method used to go backward at full speed.
 */
void MOTI::goBackward(){
	spinLeftWheel(255, 0);
	spinRightWheel(255, 0);

	setMovingState(true);
}

/**
 * @brief Method used to go backward
 *
 * @param speed the speed wanted, should be between 0-255
 */
void MOTI::goBackward(int speed){
	int _speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel(_speed, 0);
	spinRightWheel(_speed, 0);

	setMovingState(true);
}

/**
 * @brief Method used to go left at full speed.
 */
void MOTI::goLeft(){
	spinLeftWheel(175, 0);
	spinRightWheel(255, 0);

	setMovingState(true);
}

/**
 * @brief Method used to go left
 *
 * @param speed the speed wanted, should be between 0-255
 */
void MOTI::goLeft(int speed){
	speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel((uint8_t) speed * turnCoefficientTime / turnCoefficientDiv, 0);
	spinRightWheel(speed, 0);

	setMovingState(true);
}

/**
 * @brief Method used to go right at full speed.
 */
void MOTI::goRight(){
	spinLeftWheel(255, 0);
	spinRightWheel(175, 0);

	setMovingState(true);
}

/**
 * @brief Method used to go right
 *
 * @param speed the speed wanted, should be between 0-255
 */
void MOTI::goRight(int speed){
	speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel(speed, 0);
	spinRightWheel((uint8_t) speed * turnCoefficientTime / turnCoefficientDiv, 0);

	setMovingState(true);
}

/**
 * @brief Method used to spin left at full speed.
 */
void MOTI::spinLeft(){
	spinLeftWheel(255, 0);
	spinRightWheel(255, 1);

	setMovingState(true);
}

/**
 * @brief Method used to spin left
 *
 * @param speed the speed wanted, should be between 0-255
 */
void MOTI::spinLeft(int speed){
	speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel(speed, 0);
	spinRightWheel(speed, 1);

	setMovingState(true);
}

/**
 * @brief Method used to spin right at full speed.
 */
void MOTI::spinRight(){
	spinLeftWheel(255, 1);
	spinRightWheel(255, 0);

	setMovingState(true);
}

/**
 * @brief Method used to spin right
 *
 * @param speed the speed wanted, should be between 0-255
 */
void MOTI::spinRight(int speed){
	speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel(speed, 1);
	spinRightWheel(speed, 0);

	setMovingState(true);
}

/**
 * @brief Method used to stop all motors.
 */
void MOTI::stop(){
	digitalWrite(leftMotorDirectionPin, 0);
	digitalWrite(leftMotorSpeedPin, 0);
	digitalWrite(rightMotorDirectionPin, 0);
	digitalWrite(rightMotorSpeedPin, 0);

	setMovingState(false);
}