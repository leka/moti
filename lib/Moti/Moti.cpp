#include "Moti.h"

#include "Arduino.h"

#include "FreeSixIMU.h"
#include "RGBLED.h"


//##############//
// CONSTRUCTORS //
//##############//

Moti & Moti::getInstance() {
	static Moti singleton;
	return singleton;
}

Moti::Moti(){
	delay(50);

	Wire.begin();

	RGBLED rgbled = RGBLED(RED_PIN, GREEN_PIN, BLUE_PIN);
	FreeSixIMU AccelGyro = FreeSixIMU();

	delay(50);
}

void Moti::init(){
	initializeConstants();
	delay(50);
	AccelGyro.init();
	delay(50);
	initializeMotors();
	delay(50);
	initializeLed();
	delay(50);
	Serial.begin(115200);
}

//#########//
// SENSORS //
//#########//

void Moti::checkSensors(){
	checkAccelerometer();
	checkGyroscope();
}

void Moti::checkAccelerometer(){
	AccelGyro.getRawValues(XYZ);
}

void Moti::checkGyroscope(){
	AccelGyro.getYawPitchRoll(YPR);
}

void Moti::computeSensorValues	(){
	deltaXYZ[0] = XYZ[0] - lastXYZ[0];
	deltaXYZ[1] = XYZ[1] - lastXYZ[1];
	deltaXYZ[2] = XYZ[2] - lastXYZ[2];

	deltaYPR[0] = YPR[0] - lastYPR[0];
	deltaYPR[1] = YPR[1] - lastYPR[1];
	deltaYPR[2] = YPR[2] - lastYPR[2];
}

void Moti::updateLastSensorValues(){
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

void Moti::setAllToLow(){
	digitalWrite(leftMotorSpeedPin, 0);
	digitalWrite(rightMotorSpeedPin, 0);
	digitalWrite(leftMotorDirectionPin, 0);
	digitalWrite(rightMotorDirectionPin, 0);
	digitalWrite(RED_PIN, 0);
	digitalWrite(GREEN_PIN, 0);
	digitalWrite(BLUE_PIN, 0);
}

void Moti::softwareReset() {
	//	this function reset the program so that it can restart before the void setup().
	//	it is used because we don't know how much time has passed since the last awaken state.
	//	the environment may have change, so going through the void setup() again is required.

	asm volatile ("  jmp 0");
}

