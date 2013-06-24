#include "Moti.h"
#include "Arduino.h"

//###############//
// SET CONSTANTS //
//###############//

void Moti::setGlobalDelay(int value){
	_globalDelay = value;
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


//###############//
// GET CONSTANTS //
//###############//

int Moti::getGlobalDelay(){
	return _globalDelay;
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


//#################//
// RESET CONSTANTS //
//#################//

void Moti::resetGlobalDelay(int value){
	_globalDelay = DEFAULT_GLOBAL_DELAY;
}

void Moti::resetSleepDelay(int value){
	_sleepDelay = DEFAULT_SLEEP_DELAY;
}

void Moti::resetAwakeThreshold(int value){
	_awakeThreshold = DEFAULT_AWAKE_THRESHOLD;
}

void Moti::resetDeltaAccelThreshold(int value){
	_deltaAccelThreshold = DEFAULT_DELTA_ACCEL_THRESHOLD;
}

void Moti::resetHighActivityThreshold(int value){
	_highActivityThreshold = DEFAULT_HIGH_ACTIVITY_THRESHOLD;
}

void Moti::resetLedMaxBrightness(int value){
	_ledMaxBrightness = DEFAULT_LED_MAX_BRIGHTNESS;
}

void Moti::resetRedMaxBrightness(int value){
	_redMaxBrightness = DEFAULT_RED_MAX_BRIGHTNESS;
}

void Moti::resetGreenMaxBrightness(int value){
	_greenMaxBrightness = DEFAULT_GREEN_MAX_BRIGHTNESS;
}

void Moti::resetBlueMaxBrightness(int value){
	_blueMaxBrightness = DEFAULT_BLUE_MAX_BRIGHTNESS;
}
