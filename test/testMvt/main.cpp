#include <Arduino.h>
#include <Wire.h>

#include "ChibiOS_AVR.h"
//#include "Moti.h"
#include "Sensors.h"
#include "DriveSystem.h"
#include "Led.h"
Led LedRight = Led(8,9,10);
Led LedLeft = Led(11,12,13);

int LiftAndSpin(int deltaZ, int accZold){
	int Threshold = 150;
	bool isDetecting = TRUE;
// FAIRE LE COP/COLL POUR TESTER SI LA FONCTION MARCHE PAREIL, RÉGLER LE THRESHOLD, METTRE DANS BLINKCOLORRANDOMRISE ET GÉRER RANDOM
		if (deltaZ > Threshold && isDetecting) {
			Serial.println("rised");
			accZold = Sensors::getAccZ();
			isDetecting=FALSE;
		}

		if (!isDetecting){
		Serial.println("spining");
		LedRight.shine(255,255,0);
		LedLeft.shine(255,255,0);
		DriveSystem::spin(LEFT, 255);
		waitMs(1000);
		DriveSystem::stop();
		waitMs(1000);
		LedRight.shine(0,0,0);
		LedLeft.shine(0,0,0);
		isDetecting=TRUE;
		}

		return accZold;
}

void mainThread() {

	//INITIALIZATION
	Sensors::init();
	Sensors::start();

	int accZold = 0;
	int deltaZ = 0;

	while (TRUE) {

		deltaZ = accZold - Sensors::getAccZ();
		accZold = Sensors::getAccZ();
		accZold = LiftAndSpin(deltaZ, accZold);
		waitMs(50);
	}
}

void loop() { }

int main(void) {
	init();

	Serial.begin(115200);
	while (!Serial);

	Wire.begin();
	delay(2000);

	chBegin(mainThread);

	while(1);

	return 0;
}