#include "Moti.h"

#include "Moti_Constants.cpp"
#include "Moti_Data.cpp"
#include "Moti_Led.cpp"
#include "Moti_Motors.cpp"
#include "Moti_State.cpp"

#include "Arduino.h"

#include "FreeSixIMU.h"
#include "RGBLED.h"


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
	Serial.println("Initialize Constants");
	initializeConstants();
	Serial.println("Initialize Constants - OK");
	delay(500);
	Serial.println("Initialize States");
	initializeStates();
	Serial.println("Initialize States - OK");
	delay(500);
	Serial.println("Initialize Wire");
	Wire.begin();
	Serial.println("Initialize Wire - OK");
	delay(500);
	Serial.println("Initialize AccelGyro");
	AccelGyro.init();
	Serial.println("Initialize AccelGyro - OK");
	delay(500);
	Serial.println("Initialize Motors");
	initializeMotors();
	Serial.println("Initialize Motors - OK");
	delay(500);
}

//#########//
// SENSORS //
//#########//

void MOTI::checkSensors(){
	checkAccelerometer();
	checkGyroscope();
}

void MOTI::checkAccelerometer(){
	AccelGyro.getRawValues(XYZ);
}

void MOTI::checkGyroscope(){
	AccelGyro.getYawPitchRoll(YPR);
}

void MOTI::computeSensorValues	(){
	deltaXYZ[0] = XYZ[0] - lastXYZ[0];
	deltaXYZ[1] = XYZ[1] - lastXYZ[1];
	deltaXYZ[2] = XYZ[2] - lastXYZ[2];

	deltaYPR[0] = YPR[0] - lastYPR[0];
	deltaYPR[1] = YPR[1] - lastYPR[1];
	deltaYPR[2] = YPR[2] - lastYPR[2];
}

void MOTI::updateLastSensorValues(){
	lastXYZ[0] = XYZ[0];
	lastXYZ[1] = XYZ[1];
	lastXYZ[2] = XYZ[2];

	lastYPR[0] = YPR[0];
	lastYPR[1] = YPR[1];
	lastYPR[2] = YPR[2];
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

