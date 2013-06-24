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

	Serial.begin(115200);

	delay(50);

	RGBLED rgbled = RGBLED(RED_PIN, GREEN_PIN, BLUE_PIN);
	FreeSixIMU AccelGyro = FreeSixIMU();

	delay(50);
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


//#########//
// GENERAL //
//#########//

void Moti::setAllToLow(){

}

void Moti::shutDown(){

}

void Moti::softwareReset() {
	//	this function reset the program so that it can restart before the void setup().
	//	it is used because we don't know how much time has passed since the last awaken state.
	//	the environment may have change, so going through the void setup() again is required.

	asm volatile ("  jmp 0");
}

