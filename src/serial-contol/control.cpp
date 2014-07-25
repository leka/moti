#define serial Serial1

#include <Arduino.h>
#include <Wire.h>

#include "Moti.h"
#include "ChibiOS_AVR.h"
#include "Configuration.h"
#include "Color.h"
#include "Drive.h"
#include "DriveSystem.h"
#include "Environment.h"
#include "FreeIMU.h"
#include "Led.h"
#include "Light.h"
#include "Motor.h"
#include "Queue.h"
#include "Sensors.h"
#include "Serial.h"

#include "Stabilization/Stabilization.h"

/* #include "Vector.h" */


void chSetup() {
	Serial.println(F("Starting..."));

	ReadCommand readCmd;
	COMMAND cmd;

	Drive::start();
	DriveSystem::start();
	Environment::start();
	Light::start();
	Stabilization::start();

	while (TRUE) {
		Serial.println(F("Reading..."));

		if (readCmd.getHeader() == 42) {
			readCmd.readControlCommand();
			cmd = readCmd.getCommand();

			switch (readCmd.getType()) {
			case COMMAND_GO:
				Stabilization::stop();
				DriveSystem::go(cmd.go.direction, cmd.go.speed, cmd.go.duration);
				break;

			case COMMAND_SPIN:
				Stabilization::stop();
				DriveSystem::spinDeg(cmd.spin.rotation, cmd.spin.speed, cmd.spin.angle);
				break;

			case COMMAND_STOP:
				Stabilization::run();
				/* DriveSystem::stop(250); */
				break;

			case COMMAND_FADE:
				Light::fade(cmd.fade.indicator,
							Color(cmd.fade.startR, cmd.fade.startG, cmd.fade.startB),
							Color(cmd.fade.endR, cmd.fade.endG, cmd.fade.endB),
							cmd.fade.duration);
				break;
			
			default:
				break;
			}
		}
	}
}


void setup() {
	Serial.begin(115200);
	while (!Serial);

	serial.begin(115200);
	while (!serial);

	Wire.begin();
	delay(500);

	randomSeed(analogRead(0));

	chBegin(chSetup);

	while(1);
}

void loop() { }

/*
void command(const char* cmd, int num_bytes_response) {
 delay(1000);
 Serial1.print(cmd);
 delay(1500);
 for (int i=0;i<num_bytes_response;i++)
 Serial.write(Serial1.read());
}

void setup() { 
 Serial.begin(115200);
 Serial1.begin(9600);//use 9600 if first set up
}

void loop() {
 Serial.println("Starting");
 command("AT",2);// response: OK
 command("AT+VERSION",12);// response: OKlinvorV1.5
 command("AT+NAMEmoti2",9);//response: OKsetname
 command("AT+BAUD8",8);//response: OK115200
 while(1);//stop execution
}
*/

