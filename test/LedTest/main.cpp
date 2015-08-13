#include <Arduino.h>
#include <Wire.h>
#include "Motor.h"
#include "Led.h"

Motor motor1 = Motor(1,2);
Led led1 = Led(1,2,3);

void setup() {

	Serial.begin(1190);
	led1.shine();

}

void loop() {
	Serial.println("Hello, Wolrd");
}
