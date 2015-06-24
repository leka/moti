 #ifndef LEKA_MOTI_BEHAVIOR_COLORCHANGER_H_
#define LEKA_MOTI_BEHAVIOR_COLORCHANGER_H_

#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Moti.h"
#include "Led.h"
#include "Color.h"

namespace ColorChanger {

	// Thread methods
	static WORKING_AREA(behaviorThreadArea, 256);
	static msg_t thread(void * arg);
	
	//Thread
	void init(void* arg = NULL, tprio_t priority = NORMALPRIO);
	void start(void);
	void stop(void);
	uint16_t _threadDelay = 50;

	//Methods
	void FadeFromBlack(uint8_t r, uint8_t g, uint8_t b);
	void FadeToBlack(uint8_t r, uint8_t g, uint8_t b);
	void FadeFromWhite(uint8_t r, uint8_t g, uint8_t b);
	void FadeToWhite(uint8_t r, uint8_t g, uint8_t b);
   
	// Variables
	bool _isInitialized = false;
	bool _isStarted = false;

	//Object
	Led myLed = Led(11,12,13);
	
	// Misc
	MUTEX_DECL(_behaviorMutex);
}



void ColorChanger::init(void* arg, tprio_t priority) {
	if (!_isInitialized) {
		_isInitialized = true;
		_isStarted = false;

		(void)chThdCreateStatic(behaviorThreadArea,
				sizeof(behaviorThreadArea),
				priority, thread, arg);
	}
}

void ColorChanger::start(void) {
	chMtxLock(&_behaviorMutex);
	_isStarted = true;
	chMtxUnlock();
}

void ColorChanger::stop(void) {
	chMtxLock(&_behaviorMutex);

	_isStarted = false;
	myLed.turnOff();    
	chMtxUnlock();
}


void ColorChanger::FadeFromBlack(uint8_t r, uint8_t g, uint8_t b){
	uint8_t myShadeRed, myShadeBlue, myShadeGreen;
	Serial.println("Fade from Black");
	for (int i=0; i<101; i++){
		myShadeRed= r *i*0.01;
		myShadeGreen= g *i*0.01;
		myShadeBlue=b *i*0.01;
		myLed.shine((myShadeRed), (myShadeGreen), (myShadeBlue));
		waitMs(50);
	}
}

void ColorChanger::FadeToBlack(uint8_t r, uint8_t g, uint8_t b){
	uint8_t myShadeRed, myShadeBlue, myShadeGreen;
	Serial.println("Fade to Black");
	for (int i=0; i<101; i++){
		myShadeRed=r *(100-i)*0.01;
		myShadeGreen=g *(100-i)*0.01;
		myShadeBlue=b *(100-i)*0.01;
		myLed.shine((myShadeRed), (myShadeGreen), (myShadeBlue));
		waitMs(50);
	}
}

void ColorChanger::FadeFromWhite(uint8_t r, uint8_t g, uint8_t b){
	uint8_t myShadeRed, myShadeBlue, myShadeGreen;
	Serial.println("Fade from white");
	for (int i=0; i<101; i++){
		myShadeRed = r + ((255- r)* (100-i) *0.01);
		myShadeGreen=g+((255- g)* (100-i) *0.01);
		myShadeBlue=b+((255- b)* (100-i) *0.01);
		myLed.shine((myShadeRed), (myShadeGreen), (myShadeBlue));
		waitMs(50);
	}
}

void ColorChanger::FadeToWhite(uint8_t r, uint8_t g, uint8_t b){
	uint8_t myShadeRed, myShadeBlue, myShadeGreen;
		Serial.println("Fade to White");
	for (int i=0; i<101; i++){
		myShadeRed = r + ((255- r )* i *0.01);
		myShadeGreen= g +((255- g )* i *0.01);
		myShadeBlue= b +((255- b )* i *0.01);
		myLed.shine((myShadeRed), (myShadeGreen), (myShadeBlue));
		waitMs(50);
	}
}

msg_t ColorChanger::thread(void* arg) {

	(void) arg;
 	// mettre fonction ici
	while (!chThdShouldTerminate()) {

		if (_isStarted) {
		FadeToWhite(176,202,18);
		FadeFromWhite(231,15,96);
		FadeToBlack(240,42,0);
		FadeFromBlack(97,174,214);
		}

		waitMs(_threadDelay);
	}

	return (msg_t)0;
}

#endif
