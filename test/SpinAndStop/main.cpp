#include <Arduino.h>
#include <Wire.h>

#include "ChibiOS_AVR.h"
#include "Moti.h"
#include "Sensors.h"
#include "DriveSystem.h"
#include "Led.h"

#define SpeedMoti 150

void mainThread() {

	int Threshold = 220;

	int accXold = 0;
	int deltaX = 0;

	int accYold = 0;
	int deltaY = 0;

	uint8_t nbtouch = 0;
	bool isTouched = FALSE;

	//INITIALIZATION
	Moti::init();
	Moti::start();
	Sensors::init();
	Sensors::start();

	Serial.println("Hello world!");

	while (TRUE) {

		deltaX = accXold - Sensors::getAccX();
		deltaY = accYold - Sensors::getAccY();
		accXold = Sensors::getAccX();
		accYold = Sensors::getAccY();

		if (deltaX < 0) deltaX = - deltaX;
		if (deltaY < 0) deltaY = - deltaY;

		// Serial.println(deltaX);
		// Serial.println(deltaY);
		// Serial.println(accXold);
		// Serial.println(accYold);

		if (deltaX > Threshold || deltaY > Threshold) {
			Serial.println(nbtouch);
			isTouched = TRUE;
			nbtouch++;
		}

		if (nbtouch == 1 && isTouched) {
			DriveSystem::spin(LEFT, SpeedMoti);
			waitMs(1000);
			accXold = Sensors::getAccX();
			accYold = Sensors::getAccY();
			isTouched = FALSE;
		}

		if (nbtouch == 2 && isTouched) {
			DriveSystem::stop();
			waitMs(1000);
			accXold = Sensors::getAccX();
			accYold = Sensors::getAccY();
			isTouched = FALSE;
			nbtouch=0;
		}

		waitMs(50);
	}
}

void loop() { }

int main(void) {
	init();

	Serial.begin(115200);
	while (!Serial);

	// Serial1.begin(115200);
	// while (!Serial1);

	Wire.begin();
	delay(2000);

	chBegin(mainThread);

	while(1);

	return 0;
}