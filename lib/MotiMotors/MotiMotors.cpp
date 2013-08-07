#include "Arduino.h"
#include "MotiMotors.h"

/**
 * @file MotiMotors.cpp
 * @author Ladislas de Toldi
 * @version 1.0
 */


// CONSTRUCTORS //
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief MotiMotors Class Constructor
 */
MotiMotors::MotiMotors(){
	pinMode(DEFAULT_LEFT_MOTOR_SPEED_PIN     , OUTPUT);
	pinMode(DEFAULT_LEFT_MOTOR_DIRECTION_PIN , OUTPUT);

	pinMode(DEFAULT_RIGHT_MOTOR_SPEED_PIN    , OUTPUT);
	pinMode(DEFAULT_RIGHT_MOTOR_DIRECTION_PIN, OUTPUT);

	stop();
}


// MOVING STATE //
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Is Moti moving method
 *
 * @return true if motors are ON, false if motors are OFF.
 */
bool MotiMotors::getMovingState(){
	return _stateMoving;
}

/**
 * @brief Setter method for the moving state
 *
 * @param state can be true or false
 */
void MotiMotors::setMovingState(bool state){
	_stateMoving = state;
}


// GENERAL METHODS //
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 * @ brief Method used to spin the right wheel of the robot.
 *
 * @param speed the speed of the wheel, between 0-255
 * @param direction the direction of the wheel, 1 for to go forward,  0 to go backwar
 */
void MotiMotors::spinRightWheel(uint8_t speed, bool direction){
	analogWrite(rightMotorSpeedPin, speed);
	digitalWrite(rightMotorDirectionPin, direction);
}

/**
 * @ brief Method used to spin the left wheel of the robot.
 *
 * @param speed the speed of the wheel, between 0-255
 * @param direction the direction of the wheel, 1 for to go forward,  0 to go backwar
 */
void MotiMotors::spinLeftWheel(uint8_t speed, bool direction){
	analogWrite(leftMotorSpeedPin, speed);
	digitalWrite(leftMotorDirectionPin, direction);
}

/**
 * @brief Method used to go forward at full speed.
 */
void MotiMotors::goForward(){
	spinLeftWheel(255, 1);
	spinRightWheel(255, 1);

	setMovingState(true);
}

/**
 * @brief Method used to go forward
 *
 * @param speed the speed wanted, should be between 0-255
 */
void MotiMotors::goForward(int speed){
	int _speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel(_speed, 1);
	spinRightWheel(_speed, 1);

	setMovingState(true);
}

/**
 * @brief Method used to go backward at full speed.
 */
void MotiMotors::goBackward(){
	spinLeftWheel(255, 0);
	spinRightWheel(255, 0);

	setMovingState(true);
}

/**
 * @brief Method used to go backward
 *
 * @param speed the speed wanted, should be between 0-255
 */
void MotiMotors::goBackward(int speed){
	int _speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel(_speed, 0);
	spinRightWheel(_speed, 0);

	setMovingState(true);
}

/**
 * @brief Method used to go left at full speed.
 */
void MotiMotors::goLeft(){
	spinLeftWheel(175, 0);
	spinRightWheel(255, 0);

	setMovingState(true);
}

/**
 * @brief Method used to go left
 *
 * @param speed the speed wanted, should be between 0-255
 */
void MotiMotors::goLeft(int speed){
	speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel((uint8_t) speed * turnCoefficientTime / turnCoefficientDiv, 0);
	spinRightWheel(speed, 0);

	setMovingState(true);
}

/**
 * @brief Method used to go right at full speed.
 */
void MotiMotors::goRight(){
	spinLeftWheel(255, 0);
	spinRightWheel(175, 0);

	setMovingState(true);
}

/**
 * @brief Method used to go right
 *
 * @param speed the speed wanted, should be between 0-255
 */
void MotiMotors::goRight(int speed){
	speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel(speed, 0);
	spinRightWheel((uint8_t) speed * turnCoefficientTime / turnCoefficientDiv, 0);

	setMovingState(true);
}

/**
 * @brief Method used to spin left at full speed.
 */
void MotiMotors::spinLeft(){
	spinLeftWheel(255, 0);
	spinRightWheel(255, 1);

	setMovingState(true);
}

/**
 * @brief Method used to spin left
 *
 * @param speed the speed wanted, should be between 0-255
 */
void MotiMotors::spinLeft(int speed){
	speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel(speed, 0);
	spinRightWheel(speed, 1);

	setMovingState(true);
}

/**
 * @brief Method used to spin right at full speed.
 */
void MotiMotors::spinRight(){
	spinLeftWheel(255, 1);
	spinRightWheel(255, 0);

	setMovingState(true);
}

/**
 * @brief Method used to spin right
 *
 * @param speed the speed wanted, should be between 0-255
 */
void MotiMotors::spinRight(int speed){
	speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel(speed, 1);
	spinRightWheel(speed, 0);

	setMovingState(true);
}

/**
 * @brief Method used to stop all motors.
 */
void MotiMotors::stop(){
	digitalWrite(leftMotorDirectionPin, 0);
	digitalWrite(leftMotorSpeedPin, 0);
	digitalWrite(rightMotorDirectionPin, 0);
	digitalWrite(rightMotorSpeedPin, 0);

	setMovingState(false);
}


// CONSTANTS //
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Setter method for _motorMinSpeed
 *
 * Once set, the _sleepDelay can be accessed by calling getMotorMinSpeed()
 * @param value the value you want to assign to _motorMinSpeed.
 */
void MotiMotors::setMotorMinSpeed(int value){
	_motorMinSpeed = value;
}

/**
 * @brief Setter method for _motorMaxSpeed
 *
 * Once set, the _sleepDelay can be accessed by calling getMotorMaxSpeed()
 * @param value the value you want to assign to _motorMaxSpeed.
 */
void MotiMotors::setMotorMaxSpeed(int value){
	_motorMaxSpeed = value;
}

/**
 * @brief Getter method for _motorMinSpeed
 *
 * It is used to get the minimum speed needed to get the wheels spinning.
 * @return the value of _motorMinSpeed
 */
int MotiMotors::getMotorMinSpeed(){
	return _motorMinSpeed;
}

/**
 * @brief Getter method for _motorMaxSpeed
 *
 * It is used to get the maximum speed at which the wheels should be spinning.
 * @return the value of _motorMaxSpeed
 */
int MotiMotors::getMotorMaxSpeed(){
	return _motorMaxSpeed;
}

/**
 * @brief Reset method for _motorMinSpeed to initial value
 */
void MotiMotors::resetMotorMinSpeed(){
	_motorMinSpeed = DEFAULT_MIN_MOTOR_SPEED;
}

/**
 * @brief Reset method for _motorMaxSpeed to initial value
 */
void MotiMotors::resetMotorMaxSpeed(){
	_motorMaxSpeed = DEFAULT_MAX_MOTOR_SPEED;
}