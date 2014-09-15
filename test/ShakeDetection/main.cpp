#define serio Serial

#include <Arduino.h>
#include <Wire.h>

#include "Moti.h"
#include "Color.h"
#include "Led.h"

Led heart = Led(11, 12, 13);

void mainThread() {
	serio.begin(115200);
	Sensors::init();
	Moti::startThread();

	Moti::start();

	while (TRUE) {

		if (Moti::isShakenX())
			heart.shine(Color::RedPure);

		else if (Moti::isShakenY())
			heart.shine(Color::BluePure);

		else if (Moti::isShakenZ())
			heart.shine(Color::GreenPure);

		else
			heart.turnOff();

		waitMs(50);
	}
}

void loop() { }

int main(void) {
	init();

	serio.begin(115200);

	Wire.begin();
	delay(500);

	chBegin(mainThread);

	while(1);

	return 0;
}
