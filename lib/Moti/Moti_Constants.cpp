#include "Moti.h"
#include "Arduino.h"

void Moti::initializeConstants(){
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

void Moti::setLoopDelay(int value){
	_loopDelay = value;
}

void Moti::setSleepDelay(int value){
	_sleepDelay = value;
}

void Moti::setAwakeThreshold(int value){
	_awakeThreshold = value;
}

void Moti::setDeltaAccelThreshold(int value){
	_deltaAccelThreshold = value;
}

void Moti::setHighActivityThreshold(int value){
	_highActivityThreshold = value;
}

void Moti::setLedMaxBrightness(int value){
	_ledMaxBrightness = value;
}

void Moti::setRedMaxBrightness(int value){
	_redMaxBrightness = value;
}

void Moti::setGreenMaxBrightness(int value){
	_greenMaxBrightness = value;
}

void Moti::setBlueMaxBrightness(int value){
	_blueMaxBrightness = value;
}

void Moti::setMotorMinSpeed(int value){
	_motorMinSpeed = value;
}

void Moti::setMotorMaxSpeed(int value){
	_motorMaxSpeed = value;
}


//###############//
// GET CONSTANTS //
//###############//

int Moti::getLoopDelay(){
	return _loopDelay;
}

int Moti::getSleepDelay(){
	return _sleepDelay;
}

int Moti::getAwakeThreshold(){
	return _awakeThreshold;
}

int Moti::getDeltaAccelThreshold(){
	return _deltaAccelThreshold;
}

int Moti::getHighActivityThreshold(){
	return _highActivityThreshold;
}

int Moti::getLedMaxBrightness(){
	return _ledMaxBrightness;
}

int Moti::getRedMaxBrightness(){
	return _redMaxBrightness;
}

int Moti::getGreenMaxBrightness(){
	return _greenMaxBrightness;
}

int Moti::getBlueMaxBrightness(){
	return _blueMaxBrightness;
}

int Moti::getMotorMinSpeed(){
	return _motorMinSpeed;
}

int Moti::getMotorMaxSpeed(){
	return _motorMaxSpeed;
}


//#################//
// RESET CONSTANTS //
//#################//

void Moti::resetLoopDelay(){
	_loopDelay = DEFAULT_LOOP_DELAY;
}

void Moti::resetSleepDelay(){
	_sleepDelay = DEFAULT_SLEEP_DELAY;
}

void Moti::resetAwakeThreshold(){
	_awakeThreshold = DEFAULT_AWAKE_THRESHOLD;
}

void Moti::resetDeltaAccelThreshold(){
	_deltaAccelThreshold = DEFAULT_DELTA_ACCEL_THRESHOLD;
}

void Moti::resetHighActivityThreshold(){
	_highActivityThreshold = DEFAULT_HIGH_ACTIVITY_THRESHOLD;
}

void Moti::resetLedMaxBrightness(){
	_ledMaxBrightness = DEFAULT_LED_MAX_BRIGHTNESS;
}

void Moti::resetRedMaxBrightness(){
	_redMaxBrightness = DEFAULT_RED_MAX_BRIGHTNESS;
}

void Moti::resetGreenMaxBrightness(){
	_greenMaxBrightness = DEFAULT_GREEN_MAX_BRIGHTNESS;
}

void Moti::resetBlueMaxBrightness(){
	_blueMaxBrightness = DEFAULT_BLUE_MAX_BRIGHTNESS;
}
