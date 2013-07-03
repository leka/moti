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

/**
 * @brief MOTI Class Constructor
 */
MOTI::MOTI(){}

/**
 * @brief Initialization method
 *
 * init() initialized everything at the beginning of the program. It must be called inside void setup().
 * The list of all the methods it calls is as follow: Serial.begin(), initializeConstants(), initializeLed(), initializeStates(), Wire.begin(), AccelGyro.init(), initiliazeMotors().
 */
void MOTI::init(){
	delay(500);
	Serial.begin(115200);
	delay(50);
	blinkLed(RED, 2, 200);
	delay(50);
	initializeConstants();
	delay(50);
	Wire.begin();
	delay(50);
	AccelGyro.init();
	delay(50);
	initializeLed();
	delay(50);
	initializeStates();
	delay(50);
	initializeMotors();
	blinkLed(GREEN, 4, 200);
	delay(50);
}

/**
 * @brief Initialization method with verbose output
 *
 * initVerbose() does the same as init() but adds text output for debugging purpose. It should be used ONLY for development and NOT for production.
 * The list of all the methods it calls is as follow: Serial.begin(), initializeConstants(), Wire.begin(), AccelGyro.init(), initializeLed(), initializeStates(), initiliazeMotors().
 * If everything works fine it should output a list with "SC" --> "CST" --> "WIRE" --> "IMU" --> "LED" --> "STATES" --> "MOTORS".
 * If the list is not complete, it means that the initialization of the n+1 failed.
 *
 * For example, if the serial outputs "SC" --> "CST" --> "WIRE", it means that IMU is failing and needs a fix.
 */
void MOTI::initVerbose(){
	delay(500);
	Serial.begin(115200);
	delay(100);
	Serial.println();
	Serial.println(F("SC"));
	delay(100);
	blinkLed(RED, 2, 200);
	delay(100);
	initializeConstants();
	Serial.println(F("CST"));
	delay(100);
	Wire.begin();
	Serial.println(F("WIRE"));
	delay(100);
	AccelGyro.init();
	Serial.println(F("IMU"));
	delay(100);
	initializeLed();
	Serial.println(F("LED"));
	delay(100);
	initializeStates();
	Serial.println(F("STATES"));
	delay(100);
	initializeMotors();
	Serial.println(F("MOTORS"));
	blinkLed(GREEN, 4, 200);
	delay(20);
}


//#########//
// GENERAL //
//#########//

/**
 * @brief Setting all outputs to LOW
 *
 * setAllToLow() is used at in init() to set all output pins to LOW. This makes sure the led are off and the motors are not running.
 */
void MOTI::setAllToLow(){
	digitalWrite(leftMotorSpeedPin, 0);
	digitalWrite(rightMotorSpeedPin, 0);
	digitalWrite(leftMotorDirectionPin, 0);
	digitalWrite(rightMotorDirectionPin, 0);
	digitalWrite(RED_PIN, 0);
	digitalWrite(GREEN_PIN, 0);
	digitalWrite(BLUE_PIN, 0);
}

/**
 * @brief Reseting software
 *
 * softwareReset() resets the program so that it can restart before the void setup().
 * It may be used if you don't know how much time has passed since the last awaken state.
 * The environment may have change, so going through the void setup() again is required to re- init() everything.
 */
void MOTI::softwareReset() {
	asm volatile ("  jmp 0");
}

