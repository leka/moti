#include "Moti.h"
#include "Arduino.h"

//########//
// MOTORS //
//########//

void Moti::initializeMotors(){
	pinMode(leftMotorSpeedPin, OUTPUT);
	pinMode(leftMotorDirectionPin, OUTPUT);
	pinMode(rightMotorSpeedPin, OUTPUT);
	pinMode(rightMotorDirectionPin, OUTPUT);

	stop();
}

void Moti::spinRightWheel(uint8_t speed, bool direction){
	digitalWrite(rightMotorSpeedPin, speed);
	digitalWrite(rightMotorDirectionPin, direction);
}

void Moti::spinLeftWheel(uint8_t speed, bool direction){
	digitalWrite(leftMotorSpeedPin, speed);
	digitalWrite(leftMotorDirectionPin, direction);
}

void Moti::goForward(){
	spinLeftWheel(255, 1);
	spinRightWheel(255, 1);

	setMovingState(true);
}

void Moti::goForward(int speed){
	speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel(speed, 1);
	spinRightWheel(speed, 1);

	setMovingState(true);
}

void Moti::goBackward(){
	spinLeftWheel(255, 0);
	spinRightWheel(255, 0);

	setMovingState(true);
}

void Moti::goBackward(int speed){
	speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel(speed, 0);
	spinRightWheel(speed, 0);

	setMovingState(true);
}

void Moti::goLeft(){
	spinLeftWheel(175, 0);
	spinRightWheel(255, 0);

	setMovingState(true);
}

void Moti::goLeft(int speed){
	speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel(speed * turnCoefficient, 0);
	spinRightWheel(speed, 0);

	setMovingState(true);
}

void Moti::goRight(){
	spinLeftWheel(255, 0);
	spinRightWheel(175, 0);

	setMovingState(true);
}

void Moti::goRight(int speed){
	speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel(speed, 0);
	spinRightWheel(speed * turnCoefficient, 0);

	setMovingState(true);
}

void Moti::spinLeft(){
	spinLeftWheel(255, 0);
	spinRightWheel(255, 1);

	setMovingState(true);
}

void Moti::spinLeft(int speed){
	speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel(speed, 0);
	spinRightWheel(speed, 1);

	setMovingState(true);
}

void Moti::spinRight(){
	spinLeftWheel(255, 1);
	spinRightWheel(255, 0);

	setMovingState(true);
}

void Moti::spinRight(int speed){
	speed = constrain(speed, getMotorMinSpeed(), getMotorMaxSpeed());
	spinLeftWheel(speed, 1);
	spinRightWheel(speed, 0);

	setMovingState(true);
}

void Moti::stop(){
	digitalWrite(leftMotorDirectionPin, 0);
	digitalWrite(leftMotorSpeedPin, 0);
	digitalWrite(rightMotorDirectionPin, 0);
	digitalWrite(rightMotorSpeedPin, 0);

	setMovingState(false);
}