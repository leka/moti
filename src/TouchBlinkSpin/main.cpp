#include <Arduino.h>
#include <Wire.h>

#include "ChibiOS_AVR.h"
#include "Moti.h"
#include "Sensors.h"
#include "DriveSystem.h"
#include "Led.h"
#include "Stabilization.h"

Led LedRight = Led(8,9,10);
Led LedLeft = Led(11,12,13);

void blinkRightLeft(uint8_t RedValue, uint8_t GreenValue, uint8_t BlueValue, uint16_t timeTotal) {

	for (uint16_t i = 0 ; i < timeTotal/500 ; ++i) {

		LedRight.shine(RedValue, GreenValue, BlueValue);
		LedLeft.shine(0, 0, 0);

		waitMs(250);

		LedLeft.shine(RedValue, GreenValue, BlueValue);
		LedRight.shine(0, 0, 0);

		waitMs(250);

	}

	LedLeft.shine(0, 0, 0);
	LedRight.shine(0, 0, 0);

}

void mainThread() {

	int Threshold = 150;

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
	// Stabilization::init();
	// Stabilization::start();

	Serial.println("Hello world!");

	while (TRUE) {

		deltaX = accXold - Sensors::getAccX();
		deltaY = accYold - Sensors::getAccY();
		accXold = Sensors::getAccX();
		accYold = Sensors::getAccY();

		if (deltaX < 0) deltaX = - deltaX;
		if (deltaY < 0) deltaY = - deltaY;

		Serial.println(deltaX);
		Serial.println(deltaY);
		Serial.println(accXold);
		Serial.println(accYold);

		if (deltaX > Threshold || deltaY > Threshold) {
			Stabilization::stop();
			nbtouch++;
			Serial.println(nbtouch);
			isTouched = TRUE;
		}

		if (nbtouch == 1 && isTouched) {
			Serial.println("bleu");
			blinkRightLeft(0, 0, 255, 1000);
			waitMs(2000);

			accXold = Sensors::getAccX();
			accYold = Sensors::getAccY();
			isTouched = FALSE;
			Stabilization::start();
		}

		if (nbtouch == 2 && isTouched) {
			Serial.println("vert");
			blinkRightLeft(0, 255, 0, 2000);
			waitMs(2000);

			accXold = Sensors::getAccX();
			accYold = Sensors::getAccY();
			isTouched = FALSE;
			Stabilization::start();
		}

		if (nbtouch == 3 && isTouched) {
			Serial.println("Rouge et  spin");
			blinkRightLeft(255, 0, 0, 3000);
			LedRight.shine(255, 0, 0);
			LedLeft.shine(255, 0, 0);

			DriveSystem::spin(LEFT, 255);

			waitMs(3000);

			DriveSystem::stop();

			LedRight.shine(0, 0, 0);
			LedLeft.shine(0, 0, 0);

			waitMs(2000);

			accXold = Sensors::getAccX();
			accYold = Sensors::getAccY();
			nbtouch = 0;
			isTouched = FALSE;
			Stabilization::start();
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
