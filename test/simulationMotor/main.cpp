#include <Arduino.h>
#include <Wire.h>

#include "ChibiOS_AVR.h"
#include "Moti.h"
#include "Sensors.h"
#include "Motion.h"
#include "DriveSystem.h"
#include "Communication.h"


void mainThread() {
	 int Threshold=30;
	 int i=0;
	 int accXold=0;
	 int deltaX=0;

	 int accYold=0;
	int deltaY=0;

	 int nbtouch=0;



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

		if (deltaX<0) deltaX=-deltaX;
		if (deltaY<0) deltaY=-deltaY;
		
			//if ((Sensors::getAccX()>Threshold) | (Sensors::getAccX()< (-Threshold)) | (Sensors::getAccY()>Threshold) | (Sensors::getAccY()< (-Threshold))) {
			if (deltaX>Threshold | deltaX>Threshold){

				Serial.println("je m'allume");
				Serial.println("je tourne");
				Serial.println(i);
				i++;
				Serial.println(" ");
				DriveSystem::go(FORWARD, 255);
				waitMs(1000);
				DriveSystem::stop();
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