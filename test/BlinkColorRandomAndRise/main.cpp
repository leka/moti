#include <Arduino.h>
#include <Wire.h>

#include "ChibiOS_AVR.h"
//#include "Moti.h"
#include "Sensors.h"
#include "DriveSystem.h"
#include "Led.h"
#include "Color.h"

Led LedRight = Led(8,9,10);
Led LedLeft = Led(11,12,13);

Color Color1 = Color(0,0,255); // bleu
Color Color2 = Color(0,255,0); // vert
Color Color3 = Color(255,0,0); // rouge
Color Color4 = Color(255,127,0); // orange
Color randColor = Color(0,0,0);

bool isLoto=TRUE;


void setup(){
	Serial.begin(9600);
	randomSeed(analogRead(0));
}

void blinkInterval(uint16_t t, uint16_t intervalBlink){
	DriveSystem::spin(LEFT, 150);
	// Serial.println(F("blinkInterval 0"));
	for(uint16_t i = 0; i < (t/(2*intervalBlink)) ; ++i){
		LedRight.shine(0,0,255);
		LedLeft.shine(0,0,0);
		waitMs(intervalBlink);
// Serial.println(F("blinkInterval 1"));
		LedRight.shine(0,0,0);
		LedLeft.shine(0,255,0);
		waitMs(intervalBlink);
// Serial.println(F("blinkInterval 2"));
		LedRight.shine(255,0,0);
		LedLeft.shine(0,0,0);
		waitMs(intervalBlink);
// Serial.println(F("blinkInterval 3"));
		LedRight.shine(0,0,0);
		LedLeft.shine(255,127,0);
		waitMs(intervalBlink);
		// Serial.println(F("blinkInterval 4"));
		
	}
	// Serial.println(F("blinkInterval 5"));
	DriveSystem::stop();
}

void blinkJackpot(void) {
	// Serial.println(F("blinkJackpot 01"));	
	blinkInterval(1000,100);
	// Serial.println(F("blinkJackpot 02"));
	blinkInterval(1000,200);
	// Serial.println(F("blinkJackpot 03"));
	blinkInterval(1000,300);
	// Serial.println(F("blinkJackpot 04"));
	blinkInterval(1000,400);
	// Serial.println(F("blinkJackpot 05"));
	blinkInterval(1000,500);

	for (uint8_t i = 0 ; i < 4 ; ++i) {

		// Serial.println(F("blinkJackpot 1"));
		LedLeft.shine(0,0,0);
		LedRight.shine(0,0,0);

		waitMs(250);

		LedRight.shine(randColor);
		LedLeft.shine(randColor);

		waitMs(250);
		// Serial.println(F("blinkJackpot 2"));
	}
	// Serial.println(F("blinkJackpot 3"));
	
	LedRight.shine(randColor);
	LedLeft.shine(randColor);

	waitMs(3000);

	LedLeft.shine(0,0,0);
	LedRight.shine(0,0,0);
	// Serial.println(F("blinkJackpot 4"));
}

void setColorRandom( uint8_t randNumber, bool isTouched){

			if (isTouched && randNumber > 1 && randNumber <= 10){
				// Serial.println(F("randNumber 1"));
				randColor=Color1;
				blinkJackpot();
				waitMs(5000);
			}

			else if (isTouched && randNumber > 10 && randNumber <= 20){
				// Serial.println(F("randNumber 2"));
				randColor=Color2;
				blinkJackpot();
				waitMs(5000);
			}

			else if (isTouched && randNumber > 20 && randNumber <= 30){
				// Serial.println(F("randNumber 3"));
				randColor=Color3;
				blinkJackpot();
				waitMs(5000);
			}

			else if (isTouched && randNumber > 10 && randNumber <= 40){
				// Serial.println(F("randNumber 4"));
				randColor=Color4;
				blinkJackpot();
				waitMs(5000);
			}

}

void setColorChanges(bool isTouched){

	if (isTouched && randColor.isEgal(Color1)){
				// Serial.println(F("isEqual 1 1"));
		Color1=Color2;
		Color2=Color3;
		Color3=Color4;
				// Serial.println(F("isEqual 1 2"));
	}

	else if (isTouched && randColor.isEgal(Color2)){
				// Serial.println(F("isEqual 2 1"));
		Color2=Color3;
		Color3=Color4;
				// Serial.println(F("isEqual 2 2"));
	}

	else if (isTouched && randColor.isEgal(Color3)){
				// Serial.println(F("isEqual 3 1"));
		Color3=Color4;
				// Serial.println(F("isEqual 3 2"));
	}
}

void initColors(){
				Color1=Color(0,0,255); // bleu
			Color2=Color(0,255,0); // vert
			Color3=Color(255,0,0); // rouge
			Color4=Color(255,127,0); // orange
}

int LiftAndSpin(int deltaZ, int accZold){
	int Threshold = 100;
	bool isDetecting = TRUE;
// FAIRE LE COP/COLL POUR TESTER SI LA FONCTION MARCHE PAREIL, RÉGLER LE THRESHOLD, METTRE DANS BLINKCOLORRANDOMRISE ET GÉRER RANDOM
		if (deltaZ > Threshold && isDetecting) {
			Serial.println("rised");
			accZold = Sensors::getAccZ();
			isDetecting=FALSE;
		}

		if (isDetecting==FALSE){
		Serial.println("shine");
		LedRight.shine(255,255,255);
		LedLeft.shine(255,255,255);
		Serial.println("spin");
		DriveSystem::spin(LEFT, 255);
		waitMs(3000);
		Serial.println("stop spin");
		DriveSystem::stop();
		waitMs(1000);
		Serial.println("stop led");
		LedRight.shine(0,0,0);
		LedLeft.shine(0,0,0);
		// Serial.println("isDetecting TRUE");
		// isDetecting=TRUE;
		Serial.println("isLoto before TRUE");
		Serial.println(isLoto);
		isLoto = TRUE;
		Serial.println("isLoto TRUE");
		Serial.println(isLoto);
		}

		return accZold;
}

void mainThread() {

	//Variables
	int Threshold = 200;

	int accXold = 0;
	int deltaX = 0;

	int accYold = 0;
	int deltaY = 0;

	int accZold = 0;
	int deltaZ = 0;

	bool isTouched = FALSE;

	uint8_t randNumber;
	uint8_t i = 4;

	//INITIALIZATION
	Sensors::init();
	Sensors::start();

	Serial.println("Hello world!");

	while (TRUE) {

		//Detect shake and lift
		deltaX = accXold - Sensors::getAccX();
		if (deltaX < 0) deltaX = - deltaX;
		accXold = Sensors::getAccX();

		deltaY = accYold - Sensors::getAccY();
		if (deltaY < 0) deltaY = - deltaY;
		accYold = Sensors::getAccY();
		
		deltaZ = accZold - Sensors::getAccZ();
		accZold = Sensors::getAccZ();

		//Shaked 
		if ((deltaX > Threshold || deltaY > Threshold)) {
			Serial.println("touched");
			
			isTouched = TRUE;
			waitMs(1000);
			accXold = Sensors::getAccX();
			accYold = Sensors::getAccY();
			randNumber = random(1,((i*10)+1));
			
			Serial.print("random number :");
			Serial.println(randNumber);
			
			i--;
			Serial.println("set color random");
			setColorRandom(randNumber, isTouched);
			Serial.println("isLoto FALSE");
			isLoto=FALSE;
			Serial.println(isLoto);

		}

		//Incremente colors
		setColorChanges(isTouched);

		// Reset i
		if (i == 0) {
			// Serial.println(F("i equal 0 1"));
			i = 4;
			initColors();

			// Serial.println(F("i equal 0 2"));
		}

		isTouched = FALSE;

		//Lift

		if (isLoto == FALSE){
			accZold = LiftAndSpin(deltaZ, accZold);
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