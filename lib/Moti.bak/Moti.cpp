#include "Arduino.h"
#include "Moti.h"



//##############//
// CONSTRUCTORS //
//##############//

Moti::Moti(){

}

Moti::Moti(int red_led_pin, int green_led_pin, int blue_led_pin, int left_motor_speed_pin, int left_motor_direction_pin, int right_motor_speed_pin, int right_motor_direction_pin){

}

//###############//
// SET CONSTANTS //
//###############//

int Moti::setGlobalDelay(){

}

int Moti::setSleepDelay(){

}

int Moti::setAwakeThreshold(){

}

int Moti::setDeltaAccelThreshold(){

}

int Moti::setCrazyActivityThreshold(){

}

int Moti::setLedMaxBrightness(){

}

int Moti::setRedMaxBrightness(){

}

int Moti::setGreenMaxBrightness(){

}

int Moti::setBlueMaxBrightness(){

}


//###############//
// GET CONSTANTS //
//###############//

int Moti::getGlobalDelay(){

}

int Moti::getSleepDelay(){

}

int Moti::getAwakeThreshold(){

}

int Moti::getDeltaAccelThreshold(){

}

int Moti::getHighActivityThreshold(){

}

int Moti::getLedMaxBrightness(){

}

int Moti::getRedMaxBrightness(){

}

int Moti::getGreenMaxBrightness(){

}

int Moti::getBlueMaxBrightness(){

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

