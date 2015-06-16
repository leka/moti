#include <Arduino.h>
#include <Wire.h>

#include "ChibiOS_AVR.h"
#include "Moti.h"
#include "Sensors.h"
#include "Motion.h"
#include "DriveSystem.h"
#include "Led.h"

void mainThread() {
	int Threshold=70;
	int i=0;
	int accXold=0;
	int deltaX=0;

	int accYold=0;
	int deltaY=0;

	int nbtouch=0;
	bool isTouched;

	Led myLed = Led(11,12,13);

	//INITIALIZATION
	Moti::init();
	Moti::start();
	Sensors::init();
	Sensors::start();

	Serial.println("Hello world!");
	while (TRUE) {
		deltaX=accXold-Sensors::getAccX();
		deltaY=accYold-Sensors::getAccY();
		accXold=Sensors::getAccX();
		accYold=Sensors::getAccY();

		if (deltaX<0) deltaX =-deltaX;
		if (deltaY<0) deltaY=-deltaY;
		
			//if ((Sensors::getAccX()>Threshold) | (Sensors::getAccX()< (-Threshold)) | (Sensors::getAccY()>Threshold) | (Sensors::getAccY()< (-Threshold))) {
		if (deltaX > Threshold | deltaY > Threshold){
			nbtouch++;
			Serial.println(nbtouch);
			isTouched=1;
		}

		if (nbtouch==1 &&  isTouched){
			Serial.println("bleu");
			myLed.shine(0,0,255);
			isTouched=0;
			waitMs(1000);
			myLed.shine(0,0,0);
			waitMs(1000);
			//accXold=-Sensors::getAccX();
		//accYold=-Sensors::getAccY();

		}

		if (nbtouch==2 && isTouched){
			Serial.println("vert");
			myLed.shine(0,255, 0);
			isTouched=0;
			waitMs(2000);
			myLed.shine(0,0,0);
			waitMs(1000);
			//accXold=-Sensors::getAccX();
		//accYold=-Sensors::getAccY();

		}

		if (nbtouch==3 && isTouched){
			Serial.println("Rouge et  spin");
			myLed.shine(255,0,0);
			isTouched=0;
			waitMs(50);
			DriveSystem::spin(LEFT, 255);
			waitMs(3000);
			DriveSystem::stop();
			myLed.shine(0,0,0);
			nbtouch=0;
			waitMs(2000);
			//accXold=-Sensors::getAccX();
		//accYold=-Sensors::getAccY();

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
	delay(5000);

	chBegin(mainThread);

	while(1);

	return 0;
}