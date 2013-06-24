#include "Moti.h"
#include "Arduino.h"

//########//
// MOTORS //
//########//

void MOTI::initializeMotors(){
	pinMode(leftMotorSpeedPin, OUTPUT);
	pinMode(leftMotorDirectionPin, OUTPUT);
	pinMode(rightMotorSpeedPin, OUTPUT);
	pinMode(rightMotorDirectionPin, OUTPUT);

	stop();
}

void MOTI::spinRightWheel(uint8_t speed, bool direction){
	analogWrite(rightMotorSpeedPin, speed);
	digitalWrite(rightMotorDirectionPin, direction);
}

void MOTI::spinLeftWheel(uint8_t speed, bool direction){
	analogWrite(leftMotorSpeedPin, speed);
	digitalWrite(leftMotorDirectionPin, direction);
}

void MOTI::goForward(){
	spinLeftWheel(255, 1);
	spinRightWheel(255, 1);

	setMovingState(true);
}

void MOTI::goForward(int speed){
	speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel(speed, 1);
	spinRightWheel(speed, 1);

	setMovingState(true);
}

void MOTI::goBackward(){
	spinLeftWheel(255, 0);
	spinRightWheel(255, 0);

	setMovingState(true);
}

void MOTI::goBackward(int speed){
	speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel(speed, 0);
	spinRightWheel(speed, 0);

	setMovingState(true);
}

void MOTI::goLeft(){
	spinLeftWheel(175, 0);
	spinRightWheel(255, 0);

	setMovingState(true);
}

void MOTI::goLeft(int speed){
	speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel(speed * turnCoefficient, 0);
	spinRightWheel(speed, 0);

	setMovingState(true);
}

void MOTI::goRight(){
	spinLeftWheel(255, 0);
	spinRightWheel(175, 0);

	setMovingState(true);
}

void MOTI::goRight(int speed){
	speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel(speed, 0);
	spinRightWheel(speed * turnCoefficient, 0);

	setMovingState(true);
}

void MOTI::spinLeft(){
	spinLeftWheel(255, 0);
	spinRightWheel(255, 1);

	setMovingState(true);
}

void MOTI::spinLeft(int speed){
	speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel(speed, 0);
	spinRightWheel(speed, 1);

	setMovingState(true);
}

void MOTI::spinRight(){
	spinLeftWheel(255, 1);
	spinRightWheel(255, 0);

	setMovingState(true);
}

void MOTI::spinRight(int speed){
	speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel(speed, 1);
	spinRightWheel(speed, 0);

	setMovingState(true);
}

void MOTI::stop(){
	digitalWrite(leftMotorDirectionPin, 0);
	digitalWrite(leftMotorSpeedPin, 0);
	digitalWrite(rightMotorDirectionPin, 0);
	digitalWrite(rightMotorSpeedPin, 0);

	setMovingState(false);
}