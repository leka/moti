#include <Arduino.h>
#include <Wire.h>

#include "ChibiOS_AVR.h"
#include "Moti.h"
#include "Sensors.h"
#include "DriveSystem.h"
#include "Led.h"

#define SpeedMoti 150
#define SpeedTurnMoti 50

Led LedRight = Led(8,9,10);
Led LedLeft = Led(11,12,13);

void setup(){
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

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

void zigzag(uint16_t timeTotal){
for (uint16_t i = 0 ; i < timeTotal/1000 ; ++i) {

		DriveSystem::turn(BACKWARD, SpeedMoti, 0);
		waitMs(500);

		DriveSystem::turn(BACKWARD, 0, SpeedMoti);
		waitMs(500);

	}

}

void mainThread() {
	uint8_t randNumber;

	int Threshold = 120;

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

		// 

		if (deltaX > Threshold || deltaY > Threshold) {
			nbtouch++;
			//Serial.println(nbtouch);
			isTouched = TRUE;
		}

		if (nbtouch == 1 && isTouched) {
			Serial.println("bleu");
			blinkRightLeft(0, 0, 255, 1000);
			waitMs(2000);

			accXold = Sensors::getAccX();
			accYold = Sensors::getAccY();
			isTouched = FALSE;
		}

		if (nbtouch == 2 && isTouched) {
			Serial.println("vert");
			blinkRightLeft(0, 255, 0, 2000);
			waitMs(2000);

			accXold = Sensors::getAccX();
			accYold = Sensors::getAccY();
			isTouched = FALSE;
		}

		if (nbtouch == 3 && isTouched) {
			Serial.println("Rouge et  spin");
			blinkRightLeft(255, 0, 0, 3000);
			LedRight.shine(255, 0, 0);
			LedLeft.shine(255, 0, 0);

			randNumber = random(1,4);
			Serial.println(randNumber);

			if (randNumber ==1){
			DriveSystem::spin(LEFT, SpeedMoti);
			waitMs(3000);
			}

			if (randNumber ==2){
			zigzag(3000);
			}

			if (randNumber ==3){
			DriveSystem::go(BACKWARD, SpeedMoti);
			waitMs(1000);
			DriveSystem::turn(FORWARD, SpeedMoti, SpeedTurnMoti);
			waitMs(1000);
			DriveSystem::go(BACKWARD, SpeedMoti);
			waitMs(1000);
			}

			DriveSystem::stop();

			LedRight.shine(0, 0, 0);
			LedLeft.shine(0, 0, 0);

			waitMs(2000);

			accXold = Sensors::getAccX();
			accYold = Sensors::getAccY();
			nbtouch = 0;
			isTouched = FALSE;
		}

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