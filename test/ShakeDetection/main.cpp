#define serio Serial

#include <Arduino.h>
#include <Wire.h>

#include "Motion.h"
#include "Moti.h"
#include "Color.h"
// #include "Light.h"
#include "Led.h"
#include "Communication.h"
#include "Serial.h"

int16_t pastX = 0, currentX = 0, deltaX = 0, threshold = 150;
double sqDeltaX = 0, sqrtDeltaX = 0, newX = 0, computedX1 = 0, computedX2 = 0, computedX3 = 0;
double alpha1 = 0.1, alpha2 = 0.5, alpha3 = 0.9;
uint32_t count = 0;
Led heart = Led(11, 12, 13);

void mainThread() {
	serio.println(F("Starting..."));

	Sensors::init();
	// DriveSystem::start();
	// Motion::start();
	Moti::start();


	Moti::run();

	while (TRUE) {

		// else if (Moti::isShaken())
		// 	serio.println(2);
		//
		// else
		// 	serio.println(0);


		currentX = Sensors::getAccX();
		deltaX = pastX - currentX;
		pastX = currentX;

		newX = sqrt(sq((double)deltaX));
		computedX1 = (alpha1 * newX) + (1.0 - alpha1) * computedX1;
		computedX2 = (alpha2 * newX) + (1.0 - alpha2) * computedX2;
		computedX3 = (alpha3 * newX) + (1.0 - alpha3) * computedX3;


		serio.print(count);
		serio.print (F("\t"));
		serio.print(currentX);
		serio.print (F("\t"));
		serio.print(deltaX);
		serio.print (F("\t"));
		serio.print(newX);
		serio.print (F("\t"));
		serio.print(computedX1);
		serio.print (F("\t"));
		serio.print(computedX2);
		serio.print (F("\t"));
		serio.println(computedX3);

		count++;

		if (Moti::isSpinning())
			heart.shine(Color::BluePure);

		if (computedX1 > threshold)
			heart.shine(Color::RedPure);

		if (!Moti::isSpinning() && computedX1 < threshold)
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
