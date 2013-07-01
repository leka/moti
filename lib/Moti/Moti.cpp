#include "Moti.h"

#include "Moti_Constants.cpp"
#include "Moti_Data.cpp"
#include "Moti_Led.cpp"
#include "Moti_Motors.cpp"
#include "Moti_State.cpp"

#include "Arduino.h"


//##############//
// CONSTRUCTORS //
//##############//

// MOTI & MOTI::getInstance() {
// 	static MOTI singleton;
// 	return singleton;
// }

MOTI::MOTI(){

}

void MOTI::init(){
	delay(500);
	Serial.begin(115200);
	delay(500);
	blinkLed("rand", 4, 50);
	delay(500);
	initializeConstants();
	delay(500);
	initializeLed();
	delay(500);
	initializeStates();
	delay(500);
	Wire.begin();
	delay(500);
	AccelGyro.init();
	delay(500);
	initializeMotors();
	delay(500);
}

void MOTI::initVerbose(){
	delay(500);
	Serial.begin(115200);
	delay(500);
	Serial.println(F("Serial communication has begun."));
	delay(500);
	Serial.println(F("Starting Moti.init();"));
	blinkLed("rand", 4, 50);
	delay(500);
	Serial.print(F("Initializing Constants"));
	initializeConstants();
	Serial.println(F(" ---> Constants OK"));
	delay(500);
	Serial.print(F("Initializing LED"));
	initializeLed();
	Serial.println(F(" ---> LED OK"));
	delay(500);
	Serial.print(F("Initializing States"));
	initializeStates();
	Serial.println(F(" ---> States OK"));
	delay(500);
	Serial.print(F("Initializing Wire communication"));
	Wire.begin();
	Serial.println(F(" ---> Wire OK"));
	delay(500);
	Serial.print(F("Initializing Accelerometer and Gyroscope"));
	AccelGyro.init();
	Serial.println(F(" ---> AccelGyro OK"));
	delay(500);
	Serial.print(F("Initializing Motors"));
	initializeMotors();
	Serial.println(F(" ---> Motors OK"));
	delay(500);
	Serial.println(F(" Moti has been initialized correctly, void loop(); is starting......"));
}


//#########//
// GENERAL //
//#########//

void MOTI::setAllToLow(){
	digitalWrite(leftMotorSpeedPin, 0);
	digitalWrite(rightMotorSpeedPin, 0);
	digitalWrite(leftMotorDirectionPin, 0);
	digitalWrite(rightMotorDirectionPin, 0);
	digitalWrite(RED_PIN, 0);
	digitalWrite(GREEN_PIN, 0);
	digitalWrite(BLUE_PIN, 0);
}

void MOTI::softwareReset() {
	//	this function reset the program so that it can restart before the void setup().
	//	it is used because we don't know how much time has passed since the last awaken state.
	//	the environment may have change, so going through the void setup() again is required.

	asm volatile ("  jmp 0");
}

