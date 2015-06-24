#include <Arduino.h>
#include <Wire.h>

#include "Moti.h"
#include "ColorChanger.h"
#include "Led.h"

void mainThread() {

Moti::init();
ColorChanger::init(); 

	Moti::start();

	Serial.println(F("Starting..."));
	
	while (TRUE) {
			ColorChanger::start();
		waitMs(100);
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
	// delay(5000);

	chBegin(mainThread);

	while(1);

	return 0;
}