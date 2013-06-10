#include "Arduino.h"
#include "Moti.h"



//##############//
// CONSTRUCTORS //
//##############//

Moti & Moti::getInstance() {
	static Moti singleton;
	return singleton;
}

Moti::Moti(){

}


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

}

void Moti::resetSleepDelay(int value){

}

void Moti::resetAwakeThreshold(int value){

}

void Moti::resetDeltaAccelThreshold(int value){

}

void Moti::resetHighActivityThreshold(int value){

}


void Moti::resetLedMaxBrightness(int value){

}

void Moti::resetRedMaxBrightness(int value){

}

void Moti::resetGreenMaxBrightness(int value){

}

void Moti::resetBlueMaxBrightness(int value){

}



//###########################//
// DATA TRANSFER TO COMPUTER //
//###########################//

void Moti::sendDataToProcessing(){

}

void Moti::sendDataToDebug(){

}

void Moti::sendDataToNode(){

}


//#####//
// LED //
//#####//

void Moti::setRgbValue(){

}

void Moti::setRgbValue(int value){

}

void Moti::printRgbColor(){

}

void Moti::printRgbColor(int red, int green, int blue){

}

void Moti::turnLedOff(){

}


//########//
// MOTORS //
//########//

void Moti::goForward(){

}

void Moti::goForward(int time){

}

void Moti::goBackward(){

}

void Moti::goBackward(int time){

}

void Moti::turnAround(){

}

void Moti::turnAround(int time){

}

void Moti::goLeft(){

}

void Moti::goRight(){

}


//#########//
// SENSORS //
//#########//

void Moti::checkSensors(){

}

void Moti::checkAccelerometer(){

}

void Moti::checkGyroscope(){

}


//#########//
// GENERAL //
//#########//

void Moti::setAllToLow(){

}

void Moti::shutDown(){

}

