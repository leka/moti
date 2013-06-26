#include "Moti.h"
#include "Arduino.h"

void MOTI::initializeConstants(){
	resetLoopDelay();
	resetSleepDelay();
	resetAwakeThreshold();
	resetDeltaAccelThreshold();
	resetHighActivityThreshold();

	resetLedMaxBrightness();
	resetRedMaxBrightness();
	resetGreenMaxBrightness();
	resetBlueMaxBrightness();

	resetMotorMinSpeed();
	resetMotorMaxSpeed();
}

//###############//
// SET CONSTANTS //
//###############//

void MOTI::setLoopDelay(int value){
	_loopDelay = value;
}

void MOTI::setSleepDelay(int value){
	_sleepDelay = value;
}

void MOTI::setAwakeThreshold(int value){
	_awakeThreshold = value;
}

void MOTI::setDeltaAccelThreshold(int value){
	_deltaAccelThreshold = value;
}

void MOTI::setHighActivityThreshold(int value){
	_highActivityThreshold = value;
}

void MOTI::setLedMaxBrightness(int value){
	_ledMaxBrightness = value;
}

void MOTI::setRedMaxBrightness(int value){
	_redMaxBrightness = value;
}

void MOTI::setGreenMaxBrightness(int value){
	_greenMaxBrightness = value;
}

void MOTI::setBlueMaxBrightness(int value){
	_blueMaxBrightness = value;
}

void MOTI::setMotorMinSpeed(int value){
	_motorMinSpeed = value;
}

void MOTI::setMotorMaxSpeed(int value){
	_motorMaxSpeed = value;
}


//###############//
// GET CONSTANTS //
//###############//

int MOTI::getLoopDelay(){
	return _loopDelay;
}

int MOTI::getSleepDelay(){
	return _sleepDelay;
}

int MOTI::getAwakeThreshold(){
	return _awakeThreshold;
}

int MOTI::getDeltaAccelThreshold(){
	return _deltaAccelThreshold;
}

int MOTI::getHighActivityThreshold(){
	return _highActivityThreshold;
}

int MOTI::getLedMaxBrightness(){
	return _ledMaxBrightness;
}

int MOTI::getRedMaxBrightness(){
	return _redMaxBrightness;
}

int MOTI::getGreenMaxBrightness(){
	return _greenMaxBrightness;
}

int MOTI::getBlueMaxBrightness(){
	return _blueMaxBrightness;
}

int MOTI::getMotorMinSpeed(){
	return _motorMinSpeed;
}

int MOTI::getMotorMaxSpeed(){
	return _motorMaxSpeed;
}


//#################//
// RESET CONSTANTS //
//#################//

void MOTI::resetLoopDelay(){
	_loopDelay = DEFAULT_LOOP_DELAY;
}

void MOTI::resetSleepDelay(){
	_sleepDelay = DEFAULT_SLEEP_DELAY;
}

void MOTI::resetAwakeThreshold(){
	_awakeThreshold = DEFAULT_AWAKE_THRESHOLD;
}

void MOTI::resetDeltaAccelThreshold(){
	_deltaAccelThreshold = DEFAULT_DELTA_ACCEL_THRESHOLD;
}

void MOTI::resetHighActivityThreshold(){
	_highActivityThreshold = DEFAULT_HIGH_ACTIVITY_THRESHOLD;
}

void MOTI::resetLedMaxBrightness(){
	_ledMaxBrightness = DEFAULT_LED_MAX_BRIGHTNESS;
}

void MOTI::resetRedMaxBrightness(){
	_redMaxBrightness = DEFAULT_RED_MAX_BRIGHTNESS;
}

void MOTI::resetGreenMaxBrightness(){
	_greenMaxBrightness = DEFAULT_GREEN_MAX_BRIGHTNESS;
}

void MOTI::resetBlueMaxBrightness(){
	_blueMaxBrightness = DEFAULT_BLUE_MAX_BRIGHTNESS;
}

void MOTI::resetMotorMinSpeed(){
	_motorMinSpeed = DEFAULT_MIN_MOTOR_SPEED;
}

void MOTI::resetMotorMaxSpeed(){
	_motorMaxSpeed = DEFAULT_MAX_MOTOR_SPEED;
}

