#include <Arduino.h>
#include <Wire.h>

#include "ChibiOS_AVR.h"
#include "Sensors.h"
#include "DriveSystem.h"
#include "Led.h"
Led LedRight = Led(8,9,10);
Led LedLeft = Led(11,12,13);

bool isBlinking=FALSE;

		void Sick(uint16_t timeBehavior, uint16_t wellBeingTime, uint8_t nbSick){
		timeBehavior=timeBehavior/nbSick;
		wellBeingTime=wellBeingTime/nbSick;
		for (uint16_t i = 0; i<nbSick; ++i)
		{
			DriveSystem::spin(LEFT, 100);
			LedRight.shine(255,0,0);
			LedLeft.shine(255,0,0);
			waitMs((timeBehavior*3/4) - wellBeingTime);
			LedRight.shine(0,255,0);
			LedLeft.shine(0,255,0);
			waitMs(wellBeingTime);
			LedRight.shine(255,0,0);
			LedLeft.shine(255,0,0);
			waitMs(timeBehavior/4);
		}	
		LedRight.shine(255,0,0);
		LedLeft.shine(255,0,0);
		DriveSystem::stop();
	}

	void Better(uint16_t timeBehavior, uint16_t wellBeingTime, uint8_t nbSick){
		timeBehavior=timeBehavior/nbSick;
		wellBeingTime=wellBeingTime/nbSick;
		for (uint16_t i = 0; i<nbSick; ++i)
		{
			DriveSystem::spin(LEFT, 100);
			LedRight.shine(0,255,0);
			LedLeft.shine(0,255,0);
			waitMs((timeBehavior*3/4) - wellBeingTime);
			LedRight.shine(255,0,0);
			LedLeft.shine(255,0,0);
			waitMs(wellBeingTime);
			LedRight.shine(255,0,0);
			LedLeft.shine(255,0,0);
			waitMs(timeBehavior/4);
		}	
		LedRight.shine(255,0,0);
		LedLeft.shine(255,0,0);
		DriveSystem::stop();
	}

	void BlinkGreen(uint16_t time){
		for (uint16_t i = 0; i < time/600; ++i)
		{
			LedLeft.shine(0,255,0);
			LedRight.shine(0,255,0);
			waitMs(500);
			LedLeft.shine(0,0,0);
			LedRight.shine(0,0,0);
			waitMs(100);
		}
	}


void mainThread() {

	//INITIALIZATION
	Sensors::init();
	Sensors::start();

	bool isTouched=FALSE;
	bool isTouchedStory=FALSE;
	bool StoryOver=FALSE;

	int Threshold = 80;
	int ThresholdStory = 200;

	int Touche = -1;

	int accXold = 0;
	int deltaX = 0;

	int accYold = 0;
	int deltaY = 0;

	uint16_t timeBehavior = 0;
	uint16_t wellBeingTime = 0;
	waitMs(60000);
	while (TRUE) {

		//shake and blink 2s
		deltaX = accXold - Sensors::getAccX();
		deltaY = accYold - Sensors::getAccY();
		accXold = Sensors::getAccX();
		accYold = Sensors::getAccY();


		if (deltaX < 0) deltaX = - deltaX;
		if (deltaY < 0) deltaY = - deltaY;

		if ((deltaX > ThresholdStory || deltaY > ThresholdStory) && StoryOver==FALSE) {
			isTouchedStory = TRUE;
			Serial.println("touchedStory" );
			Serial.println("BlinkGreen" );
			isBlinking=TRUE;

			BlinkGreen(2000);
			//then move forward 20s
			Serial.println("DriveSystem go" );
			DriveSystem::go(BACKWARD, 50);
			BlinkGreen(25000);
			//waitMs(20000);
			//storm
			Serial.println("DriveSystem turn" );
			DriveSystem::spin(LEFT, 255);
			BlinkGreen(6000);
			//waitMs(6000);
			DriveSystem::stop();
			isBlinking=FALSE;
			Serial.println("fade" );
			for (int i = 0; i < 255; ++i)
			{
			LedLeft.shine(i,0,0);
			LedRight.shine(i,0,0);
			waitMs(20);
			}
			waitMs(6000);
			StoryOver=TRUE;
		}


		//storyover
		
		if (StoryOver){
			isTouched=FALSE;

		if (deltaX > Threshold || deltaY > Threshold) {
			isTouched = TRUE;
			Touche++; 
			Serial.println("touched" );
			Serial.println(Touche);
		}

		if (isTouched && Touche==0)
		{
			accXold = Sensors::getAccX();
			accYold = Sensors::getAccY();
		}

		if (isTouched && Touche==1){
			timeBehavior=4000;
			wellBeingTime=200;
			waitMs(7000); // A uncomment soon
			Serial.println("1 very sick");
			Sick(timeBehavior, wellBeingTime, Touche);
			 //obligatoire
			accXold = Sensors::getAccX();
			accYold = Sensors::getAccY();
		}

	if (isTouched && Touche==2){
			timeBehavior=5000;
			wellBeingTime=500;
			waitMs(7000); // A uncommunt soon
			Serial.println("2 quite sick");
			Sick(timeBehavior, wellBeingTime, Touche);
			 //obligatoire
			accXold = Sensors::getAccX();
			accYold = Sensors::getAccY();
		}

		if (isTouched && Touche==3){
			timeBehavior=5000;
			wellBeingTime=2000;
			waitMs(7000); // A uncommunt soon
			Serial.println("3 sick");
			Sick(timeBehavior, wellBeingTime, Touche);
			 //obligatoire
			accXold = Sensors::getAccX();
			accYold = Sensors::getAccY();
		}
		
		if (isTouched && Touche==4){
			timeBehavior=6000;
			wellBeingTime=4000;
			waitMs(7000); // A uncommunt soon
			Serial.println("4 sick enough");
			Sick(timeBehavior, wellBeingTime, Touche);
			 //obligatoire
			accXold = Sensors::getAccX();
			accYold = Sensors::getAccY();
		}

		if (isTouched && Touche==5){
			timeBehavior=5000;
			wellBeingTime=500;
			waitMs(7000); // A uncommunt soon
			Serial.println("5 amlmost not sick anymore");
			Better(timeBehavior, wellBeingTime, Touche);
			 //obligatoire
			accXold = Sensors::getAccX();
			accYold = Sensors::getAccY();
		}

		if (isTouched && Touche==6){
			timeBehavior=6000;
			wellBeingTime=500;
			waitMs(7000); // A uncommunt soon
			Serial.println("6 feeling better");
			Better(timeBehavior, wellBeingTime, Touche);
			 //obligatoire
			accXold = Sensors::getAccX();
			accYold = Sensors::getAccY();
		}

		if (isTouched && Touche==7){
			timeBehavior=2000;
			wellBeingTime=400;
			waitMs(7000); // A uncommunt soon
			Serial.println("7 feeling good");
			Sick(timeBehavior, wellBeingTime, (Touche-4));
			for (int i = 0; i < 255; ++i)
			{
			LedLeft.shine(0,i,0);
			LedRight.shine(0,i,0);
			waitMs(20);
			}
			waitMs(120000);
			LedRight.shine(0,0,0);
			LedLeft.shine(0,0,0);

			 //obligatoire
			accXold = Sensors::getAccX();
			accYold = Sensors::getAccY();
		}

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