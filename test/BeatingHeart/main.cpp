#define serio Serial

#include <Arduino.h>
#include <Wire.h>

#include "Moti.h"
#include "Color.h"
#include "Led.h"
#include "Light.h"

// Led heart = Led(11, 12, 13);
//
// void fade(Led led, uint16_t duration, Color startColor, Color endColor) {
//
// 	int16_t redDiff = endColor.getR() - startColor.getR();
// 	int16_t greenDiff = endColor.getG() - startColor.getG();
// 	int16_t blueDiff = endColor.getB() - startColor.getB();
//
// 	int16_t delay = 20;
// 	int16_t steps = duration / delay;
//
// 	int16_t redValue, greenValue, blueValue;
//
// 	for (int16_t i = 0 ; i < steps - 1 ; ++i) {
// 		redValue = (int16_t)startColor.getR() + (redDiff * i / steps);
// 		greenValue = (int16_t)startColor.getG() + (greenDiff * i / steps);
// 		blueValue = (int16_t)startColor.getB() + (blueDiff * i / steps);
//
// 		Serial.print(redValue);
// 		Serial.print("\t");
// 		Serial.print(greenValue);
// 		Serial.print("\t");
// 		Serial.print(blueValue);
// 		Serial.println("\t");
//
// 		led.shine(redValue, greenValue, blueValue);
// 		waitMs(delay);
// 	}
//
// 	led.shine(endColor);
//
// 	// led.shine(endColor.getR(), endColor.getG(), endColor.getB());
//
// }
//

void mainThread() {

	volatile uint8_t basePwm = 10; // divided by ten to have a wait delay higher than 1ms
	volatile uint8_t P = 70;
	volatile uint8_t Q = 0;
	volatile uint8_t R = 230;

	while (TRUE) {

		// fade(heart, 80, Color(basePwm, 0, 0), Color(P, 0, 0));
		// fade(heart, 80, Color(P, 0, 0), Color(basePwm, 0, 0));
        //
		// heart.shine(basePwm, 0, 0);
		// waitMs(160);
		// heart.turnOff();
        //
		// fade(heart, 120, Color(Q, 0, 0), Color(R, 0, 0));
		// fade(heart, 140, Color(R, 0, 0), Color(basePwm, 0, 0));

		Light::fade(HEART, Color(basePwm, 0, 0), Color(P, 0, 0), 100);
		Light::fade(HEART, Color(P, 0, 0), Color(basePwm, 0, 0), 100);

		Light::fade(HEART, Color(basePwm, 0, 0), Color(basePwm, 0, 0), 160);

		Light::fade(HEART, Color(Q, 0, 0), Color(R, 0, 0), 120);
		Light::fade(HEART, Color(R, 0, 0), Color(basePwm, 0, 0), 140);

		waitMs(2000);
	}
}

void loop() { }

int main(void) {
	init();

	Serial.begin(115200);
	Serial.println("Start...");

	delay(500);

	chBegin(mainThread);

	while(1);

	return 0;
}
