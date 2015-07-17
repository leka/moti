#include <Arduino.h>
#include <Wire.h>

#include "ChibiOS_AVR.h"
#include "Sensors.h"
#include "DriveSystem.h"
#include "Led.h"

Led LedRight = Led(8,9,10);
Led LedLeft = Led(11,12,13);

bool isStarted = FALSE;
 
void Round() {
	while(isStarted){
		DriveSystem::go(FORWARD, 255);
		waitMs(10000);
		DriveSystem::spin(LEFT,200);
		waitMs(3000);
		DriveSystem::go(FORWARD, 255);
		waitMs(8000);
		DriveSystem::spin(RIGHT,200);
		waitMs(4000);
		DriveSystem::go(FORWARD, 255);
		waitMs(15000);
		DriveSystem::spin(LEFT,200);
		waitMs(3000);
		DriveSystem::go(FORWARD, 255);
		waitMs(8000);
		DriveSystem::spin(RIGHT,200);
		waitMs(3000);
	}
}

void BlinkColors(uint16_t timeBlinking) {

		for (uint16_t i = 0; i < timeBlinking/1000; ++i)
		{
 
		LedRight.shine(0,0,255); //Bleu
		LedLeft.shine(0,0,0);
		waitMs(100);

		LedRight.shine(0,0,0); //Vert
		LedLeft.shine(0,255,0);
		waitMs(100);

		LedRight.shine(255,0,0); //Rouge
		LedLeft.shine(0,0,0);
		waitMs(100);

		LedRight.shine(0,0,0);
		LedLeft.shine(255,127,0); //Orange
		waitMs(100);

		LedRight.shine(0,255,255); //Cyan
		LedLeft.shine(0,0,0);
		waitMs(100);

		LedRight.shine(0,0,0); //Jaune
		LedLeft.shine(255,255,0);
		waitMs(100);

		LedRight.shine(255,0,128); //Rose
		LedLeft.shine(0,0,0);
		waitMs(100);

		LedRight.shine(0,0,0);
		LedLeft.shine(128,0, 255); //Violet
		waitMs(100);


		LedRight.shine(0, 255, 128); //Turquoise
		LedLeft.shine(0,0,0);
		waitMs(100);

		LedRight.shine(0,0,0);
		LedLeft.shine(255, 255, 255); //Blanc
		waitMs(100);
	}
}

void mainThread() {

	//INITIALIZATION
	Sensors::init();
	Sensors::start();

	while (TRUE) {
		Serial.println(isStarted);
		waitMs(1000);
		isStarted=TRUE;
		if (isStarted)
		{
			Serial.println("forward 10s");
			DriveSystem::go(BACKWARD, 200);
			BlinkColors(10000);

			Serial.println("spin 3s");
			DriveSystem::spin(LEFT,150);
			BlinkColors(3000);

			Serial.println("BACKWARD 8s");
			DriveSystem::go(BACKWARD, 200);
			BlinkColors(8000);

			Serial.println("spin 4s");
			DriveSystem::spin(RIGHT,150);
			BlinkColors(4000);

			Serial.println("BACKWARD 15s");
			DriveSystem::go(BACKWARD, 200);
			BlinkColors(15000);

			Serial.println("spin 3s");
			DriveSystem::spin(LEFT,150);
			BlinkColors(3000);

			Serial.println("BACKWARD 8s");
			DriveSystem::go(BACKWARD, 200);
			BlinkColors(8000);

			Serial.println("spin 3s");
			DriveSystem::spin(RIGHT,150);
			BlinkColors(3000);
		}
		
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