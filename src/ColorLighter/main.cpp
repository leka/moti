#include <Arduino.h>
#include <Wire.h>

#include "Moti.h"
#include "ColorLighter.h"
#include "Led.h"

uint8_t i = 0;
void mainThread() {

Moti::init();
ColorLighter::init(); 

	Moti::start();

	Serial.println(F("Starting..."));
	
	while (TRUE) {
		i++;
		//Serial.print("hello ");
		//Serial.println(i);

		if (i==5) {
			i=0;
			ColorLighter::start();
		}
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