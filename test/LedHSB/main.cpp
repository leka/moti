#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Moti.h"
#include "Led.h"
#include "Color.h"


void mainThread() {

//INITIALIZATION
	Moti::init();
	Moti::start();

	(void) arg;
	uint8_t i=0;
	uint8_t j=0;
	uint8_t k=0;
	while (!chThdShouldTerminate()) {

		if (_isStarted) {
			if (k==0){
			Serial.println(F("Je suis le thread Color Changer!"));
			Serial.print(51*i);
			Serial.print(", 0, ");
			Serial.println(51*i);
			myLed.shine(32, 32, 32);
			//myLed.shine((51*i), 0, (51*i));
			waitMs(5000);
			Serial.println(F("Je m'eteint"));
			stop();
			i++;
		}
			if ((51*i)>= 255){
				k=1;
				Serial.println(F("Je suis le thread Color Changer!"));
				Serial.print("255, ");
				Serial.print(51*j);
				Serial.println(", 255");
				myLed.shine(255, (51*j), 255);
				waitMs(5000);
				Serial.println(F("Je m'eteint"));
				stop();
				j++;
				if ((51*j)>= 255 && k==1){
					i=0;
					j=0;
					k=0;
				}
			}
		}

		waitMs(_threadDelay);
	}

	return (msg_t)0;
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