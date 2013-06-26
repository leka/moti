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
	blinkLed(4);
	delay(500);
	initializeConstants();
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
	Serial.println("Serial communication has begun.");
	delay(500);
	Serial.println("Starting Moti.init();");
	blinkLed(4);
	delay(500);
	Serial.print("Initializing Constants");
	initializeConstants();
	Serial.println(" ---> Constants OK");
	delay(500);
	Serial.print("Initializing States");
	initializeStates();
	Serial.println(" ---> States OK");
	delay(500);
	Serial.print("Initializing Wire communication");
	Wire.begin();
	Serial.println(" ---> Wire OK");
	delay(500);
	Serial.print("Initializing Accelerometer and Gyroscope");
	AccelGyro.init();
	Serial.println(" ---> AccelGyro OK");
	delay(500);
	Serial.print("Initializing Motors");
	initializeMotors();
	Serial.println(" ---> Motors OK");
	delay(500);
	Serial.println(" Moti has been initialized correctly, void loop(); is starting......");
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

