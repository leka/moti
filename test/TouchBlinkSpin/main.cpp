#include <Arduino.h>
#include <Wire.h>

#include "ChibiOS_AVR.h"
#include "Moti.h"
#include "Sensors.h"
#include "Motion.h"
#include "DriveSystem.h"
#include "Led.h"

void BlinkRightLEft(int RedValue, int GreenValue, int BlueValue, int timeTotal, Led Led1, Led Led2){
	int i;
	for (i=0; i<timeTotal/500; ++i){
		Led1.shine(RedValue, GreenValue, BlueValue);
		Led2.shine(0,0,0);
		waitMs(250);
		Led2.shine(RedValue, GreenValue, BlueValue);
		Led1.shine(0,0,0);
		waitMs(250);
	}

}

void mainThread() {
	int Threshold=70;
	
	int accXold=0;
	int deltaX=0;

	int accYold=0;
	int deltaY=0;

	int nbtouch=0;
	bool isTouched;

	Led LedRight = Led(8,9,10);
	Led LedLeft = Led(11,12,13);

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
			//LedLeft.shine(0,0,255);
			BlinkRightLEft(0,0,255, 1000, LedLeft, LedRight);
			isTouched=0;
			waitMs(1000);
			LedLeft.shine(0,0,0);
			LedRight.shine(0,0,0);
			waitMs(1000);
			//accXold=-Sensors::getAccX();
		//accYold=-Sensors::getAccY();

		}

		if (nbtouch==2 && isTouched){
			Serial.println("vert");
			BlinkRightLEft(0,255,0, 2000, LedLeft, LedRight);
			//LedLeft.shine(0,255, 0);
			isTouched=0;
			waitMs(2000);
			LedLeft.shine(0,0,0);
			LedRight.shine(0,0,0);
			waitMs(1000);
			//accXold=-Sensors::getAccX();
		//accYold=-Sensors::getAccY();

		}

		if (nbtouch==3 && isTouched){
			Serial.println("Rouge et  spin");
			BlinkRightLEft(255,0,0, 3000, LedLeft, LedRight);
			//LedLeft.shine(255,0,0);
			isTouched=0;
			//waitMs(50);
			DriveSystem::spin(LEFT, 255);
			waitMs(3000);
			DriveSystem::stop();
			LedLeft.shine(0,0,0);
			LedRight.shine(0,0,0);
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