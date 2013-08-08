#include <Arduino.h>
#include <Motors.h>

/**
 * @file Motors.cpp
 * @author Ladislas de Toldi
 * @version 1.0
 */


// CONSTRUCTORS //
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Motors Class Constructor
 */
Motors::Motors(){
}

void Motors::init(){
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
bool Motors::getMovingState(){
	return _stateMoving;
}

/**
 * @brief Setter method for the moving state
 *
 * @param state can be true or false
 */
void Motors::setMovingState(bool state){
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
void Motors::spinRightWheel(uint8_t speed, bool direction){
	analogWrite(DEFAULT_RIGHT_MOTOR_SPEED_PIN, speed);
	digitalWrite(DEFAULT_RIGHT_MOTOR_DIRECTION_PIN, direction);
}

/**
 * @ brief Method used to spin the left wheel of the robot.
 *
 * @param speed the speed of the wheel, between 0-255
 * @param direction the direction of the wheel, 1 for to go forward,  0 to go backwar
 */
void Motors::spinLeftWheel(uint8_t speed, bool direction){
	analogWrite(DEFAULT_LEFT_MOTOR_SPEED_PIN, speed);
	digitalWrite(DEFAULT_LEFT_MOTOR_DIRECTION_PIN, direction);
}

/**
 * @brief Method used to go forward at full speed.
 */
void Motors::goForward(){
	spinLeftWheel(255, 1);
	spinRightWheel(255, 1);

	setMovingState(true);
}

/**
 * @brief Method used to go forward
 *
 * @param speed the speed wanted, should be between 0-255
 */
void Motors::goForward(int speed){
	int _speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel(_speed, 1);
	spinRightWheel(_speed, 1);

	setMovingState(true);
}

/**
 * @brief Method used to go backward at full speed.
 */
void Motors::goBackward(){
	spinLeftWheel(255, 0);
	spinRightWheel(255, 0);

	setMovingState(true);
}

/**
 * @brief Method used to go backward
 *
 * @param speed the speed wanted, should be between 0-255
 */
void Motors::goBackward(int speed){
	int _speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel(_speed, 0);
	spinRightWheel(_speed, 0);

	setMovingState(true);
}

/**
 * @brief Method used to go left at full speed.
 */
void Motors::goLeft(){
	spinLeftWheel(175, 0);
	spinRightWheel(255, 0);

	setMovingState(true);
}

/**
 * @brief Method used to go left
 *
 * @param speed the speed wanted, should be between 0-255
 */
void Motors::goLeft(int speed){
	speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel((uint8_t) speed * turnCoefficientTime / turnCoefficientDiv, 0);
	spinRightWheel(speed, 0);

	setMovingState(true);
}

/**
 * @brief Method used to go right at full speed.
 */
void Motors::goRight(){
	spinLeftWheel(255, 0);
	spinRightWheel(175, 0);

	setMovingState(true);
}

/**
 * @brief Method used to go right
 *
 * @param speed the speed wanted, should be between 0-255
 */
void Motors::goRight(int speed){
	speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel(speed, 0);
	spinRightWheel((uint8_t) speed * turnCoefficientTime / turnCoefficientDiv, 0);

	setMovingState(true);
}

/**
 * @brief Method used to spin left at full speed.
 */
void Motors::spinLeft(){
	spinLeftWheel(255, 0);
	spinRightWheel(255, 1);

	setMovingState(true);
}

/**
 * @brief Method used to spin left
 *
 * @param speed the speed wanted, should be between 0-255
 */
void Motors::spinLeft(int speed){
	speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel(speed, 0);
	spinRightWheel(speed, 1);

	setMovingState(true);
}

/**
 * @brief Method used to spin right at full speed.
 */
void Motors::spinRight(){
	spinLeftWheel(255, 1);
	spinRightWheel(255, 0);

	setMovingState(true);
}

/**
 * @brief Method used to spin right
 *
 * @param speed the speed wanted, should be between 0-255
 */
void Motors::spinRight(int speed){
	speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel(speed, 1);
	spinRightWheel(speed, 0);

	setMovingState(true);
}

/**
 * @brief Method used to stop all motors.
 */
void Motors::stop(){
	digitalWrite(DEFAULT_LEFT_MOTOR_DIRECTION_PIN, 0);
	digitalWrite(DEFAULT_LEFT_MOTOR_SPEED_PIN, 0);
	digitalWrite(DEFAULT_RIGHT_MOTOR_DIRECTION_PIN, 0);
	digitalWrite(DEFAULT_RIGHT_MOTOR_SPEED_PIN, 0);

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
void Motors::setMotorMinSpeed(int value){
	_motorMinSpeed = value;
}

/**
 * @brief Setter method for _motorMaxSpeed
 *
 * Once set, the _sleepDelay can be accessed by calling getMotorMaxSpeed()
 * @param value the value you want to assign to _motorMaxSpeed.
 */
void Motors::setMotorMaxSpeed(int value){
	_motorMaxSpeed = value;
}

/**
 * @brief Getter method for _motorMinSpeed
 *
 * It is used to get the minimum speed needed to get the wheels spinning.
 * @return the value of _motorMinSpeed
 */
int Motors::getMotorMinSpeed(){
	return _motorMinSpeed;
}

/**
 * @brief Getter method for _motorMaxSpeed
 *
 * It is used to get the maximum speed at which the wheels should be spinning.
 * @return the value of _motorMaxSpeed
 */
int Motors::getMotorMaxSpeed(){
	return _motorMaxSpeed;
}

/**
 * @brief Reset method for _motorMinSpeed to initial value
 */
void Motors::resetMotorMinSpeed(){
	_motorMinSpeed = DEFAULT_MIN_MOTOR_SPEED;
}

/**
 * @brief Reset method for _motorMaxSpeed to initial value
 */
void Motors::resetMotorMaxSpeed(){
	_motorMaxSpeed = DEFAULT_MAX_MOTOR_SPEED;
}