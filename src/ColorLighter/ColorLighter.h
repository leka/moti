#ifndef LEKA_MOTI_BEHAVIOR_COLORLIGHTER_H_
#define LEKA_MOTI_BEHAVIOR_COLORLIGHTER_H_

#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Moti.h"
#include "Led.h"
#include "Color.h"

namespace ColorLighter {

	// Thread methods
	static WORKING_AREA(behaviorThreadArea, 256);
	static msg_t thread(void* arg);

	void init(void* arg = NULL, tprio_t priority = NORMALPRIO);
	void start(void);
	void stop(void);
	uint16_t _threadDelay = 50;

	// Variables
	bool _isInitialized = false;
	bool _isStarted = false;

	//Object
	Led myLed = Led(11,12,13);
	// Misc
	MUTEX_DECL(_behaviorMutex);

}

void ColorLighter::init(void* arg, tprio_t priority) {
	if (!_isInitialized) {
		_isInitialized = true;
		_isStarted = false;

		(void)chThdCreateStatic(behaviorThreadArea,
				sizeof(behaviorThreadArea),
				priority, thread, arg);
	}
}

void ColorLighter::start(void) {
	chMtxLock(&_behaviorMutex);

	_isStarted = true;

	chMtxUnlock();
}

void ColorLighter::stop(void) {
	chMtxLock(&_behaviorMutex);

	_isStarted = false;
	myLed.turnOff();
	chMtxUnlock();
}

msg_t ColorLighter::thread(void* arg) {

	(void) arg;
	// Variables:
	uint8_t myRed, myGreen, myBlue, myShadeRed, myShadeBlue, myShadeGreen;
	uint8_t i=0;

	while (!chThdShouldTerminate()) {

		if (_isStarted) {
			Serial.println(F("Je suis le thread Color Lighter!"));
			myRed=0;
			myGreen=0;
			myBlue=0;
			Serial.println("try 1");
			myShadeRed = myRed + ((255- myRed)* i *0.01);
			Serial.print((myShadeRed));
			Serial.print(", ");
			myShadeGreen=myGreen+((255- myGreen)* i *0.01);
			Serial.print((myShadeGreen));
			Serial.print(", ");
			myShadeBlue=myBlue+((255- myBlue)* i *0.01);
			Serial.println((myShadeBlue));
			Serial.print(", ");


			Serial.println("try 2");
			myShadeRed=floor (myShadeRed);
			Serial.print((myShadeRed));
			Serial.print(", ");
			myShadeGreen=floor (myShadeGreen);
			Serial.print((myShadeGreen));
			Serial.print(", ");
			myShadeBlue=floor (myShadeBlue);
			Serial.println((myShadeBlue));
			Serial.print(", ");
			myLed.shine((myShadeRed), (myShadeGreen), (myShadeBlue));
		
	Serial.print((myShadeRed));
			Serial.print(", ");
			Serial.print((myShadeGreen));
			Serial.print(", ");
			Serial.println((myShadeBlue));
			Serial.print(", ");
			Serial.println(i);

			waitMs(100);
			Serial.println(F("Je m'eteint"));
			i++;


			if (i>100)
			{
				i=0;
				Serial.println(F("Je recommence"));
			}

			
		}

		waitMs(_threadDelay);
	}

	return (msg_t)0;
}

#endif
