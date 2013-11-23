#include <Arduino.h>

#define serial Serial

#include "Motor.hpp"
#include "Serial.hpp"

Motor right_motor = Motor(7,6);
Motor left_motor = Motor(4,5);

void setup(){

	serial.begin(115200);
	delay(500);

	serial.println("Starting...");
	delay(500);

}

void loop() {

	//right motor
	serial.println("Right Motor");
	right_motor.spin(0);
	delay(2000);
	right_motor.spin(0, 100);
	delay(2000);

	right_motor.stop();
	delay(2000);

	right_motor.spin(1);
	delay(2000);
	right_motor.spin(1, 100);
	delay(2000);

	right_motor.stop();
	delay(2000);

	//left motor
	serial.println("Left Motor");
	left_motor.spin(0);
	delay(2000);
	left_motor.spin(0, 100);
	delay(2000);

	left_motor.stop();
	delay(2000);

	left_motor.spin(1);
	delay(2000);
	left_motor.spin(1, 100);
	delay(2000);

	left_motor.stop();
	delay(2000);

	//both
	left_motor.spin();
	right_motor.spin();
	delay(4000);
	left_motor.stop();
	right_motor.stop();
}