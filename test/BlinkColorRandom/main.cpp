#include <Arduino.h>
#include <Wire.h>

#include "ChibiOS_AVR.h"
#include "Moti.h"
#include "Sensors.h"
#include "DriveSystem.h"
#include "Led.h"
#include "Color.h"

Led LedRight = Led(8,9,10);
Led LedLeft = Led(11,12,13);

Color Color1=Color(0,0,255); // bleu
Color Color2=Color(0,255,0); // vert
Color Color3=Color(255,0,0); // rouge
Color Color4=Color(255,127,0); // orange
Color randColor=Color(0,0,0);


void setup(){
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void blinkInterval(uint16_t t, uint16_t intervalBlink){
	for(uint16_t i=0; i < (t/(2*intervalBlink)) ; i++){

		LedRight.shine(0,0,255);
		LedLeft.shine(0,0,0);
		waitMs(intervalBlink);

		LedRight.shine(0,0,0);
		LedLeft.shine(0,255,0);
		waitMs(intervalBlink);

		LedRight.shine(255,0,0);
		LedLeft.shine(0,0,0);
		waitMs(intervalBlink);
	
		LedRight.shine(0,0,0);
		LedLeft.shine(255,127,0);
		waitMs(intervalBlink);
	}
}

void blinkJackpot(void) {
	
	blinkInterval(1000,100);
	blinkInterval(1000,200);
	blinkInterval(1000,300);
	blinkInterval(1000,400);
	blinkInterval(1000,500);
	for (uint8_t i = 0 ; i < 4 ; ++i) {

		LedLeft.shine(0,0,0);
	 	LedRight.shine(0,0,0);

	 	waitMs(250);

	 	LedRight.shine(randColor);
	 	LedLeft.shine(randColor);

	 	waitMs(250);
	 }

	 	LedRight.shine(randColor);
	 	LedLeft.shine(randColor);

	 	waitMs(3000);

		LedLeft.shine(0,0,0);
	 	LedRight.shine(0,0,0);
	}


void mainThread() {

	int Threshold = 200;

	int accXold = 0;
	int deltaX = 0;

	int accYold = 0;
	int deltaY = 0;

	bool isTouched = FALSE;

	uint8_t randNumber;
	uint8_t i=4;

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


 		//for (uint16_t i = 4 ; i > 0; --i)
		if (deltaX > Threshold || deltaY > Threshold) {
			Serial.println("touched");
			isTouched = TRUE;
			waitMs(1000);
			accXold = Sensors::getAccX();
			accYold = Sensors::getAccY();
			randNumber = random(1,(i+1));
			Serial.print("random number :");
			Serial.println(randNumber);
			i--;
		

			if (isTouched && randNumber ==1){
				randColor=Color1;
				blinkJackpot();
			}

			if (isTouched && randNumber ==2){
				randColor=Color2;
				blinkJackpot();
			}

			if (isTouched && randNumber ==3){
				randColor=Color3;
				blinkJackpot();
			}

			if (isTouched && randNumber ==4){
				randColor=Color4;
				blinkJackpot();
			}

			
			

		}

			if (isTouched && randColor.isEgal(Color1)){
				Color1=Color2;
				Color2=Color3;
				Color3=Color4;
			}
			
			if (isTouched && randColor.isEgal(Color2)){
				Color2=Color3;
				Color3=Color4;
			}
			
			if (isTouched && randColor.isEgal(Color3)){
				Color3=Color4;
			}

			if (i==0){
				i=4;
				Color1=Color(0,0,255); // bleu
				Color2=Color(0,255,0); // vert
				Color3=Color(255,0,0); // rouge
				Color4=Color(255,127,0); // orange
			}

			isTouched = FALSE;
		

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