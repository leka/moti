#include <Arduino.h>
#include <Wire.h>

#include "Motion.h"
#include "Moti.h"
#include "Light.h"
#include "Communication.h"
#include "Serial.h"

#include "Arbitrer.h"
#include "Stabilization.h"

void mainThread() {
	Serial1.println(F("Starting..."));

	Sensors::init();
	DriveSystem::init();
	Motion::init();
	Moti::init();
	// Light::start();

	uint8_t state = 1;
	Stabilization::start();

	ReadCommand readCmd;
	COMMAND cmd;

	Stabilization::run();

	Moti::start();

	while (TRUE) {
		if (Moti::isSpinning())
			Serial1.println(Moti::getLapsZ());

		if (readCmd.getHeader() == 1) {
			if (state == 0) {
				Arbitrer::stop();
				Motion::stop(0);
				Stabilization::run();
			}
			else {
				Stabilization::stop();
				Arbitrer::launch();
			}

			state ^= 1;
			readCmd.resetHeader();
		}

		if (state == 0) { }

		else if (state == 1) {
			if (readCmd.getHeader() == 42) {
				readCmd.readControlCommand();
				cmd = readCmd.getCommand();

				switch (readCmd.getType()) {
					case COMMAND_GO:
						Stabilization::stop();
						Motion::go(cmd.go.direction, cmd.go.speed, cmd.go.duration, 500);
						break;

					case COMMAND_SPIN:
						Stabilization::stop();
						Motion::spinDeg(cmd.spin.rotation, cmd.spin.speed, cmd.spin.angle);
						break;

					case COMMAND_STOP:
						Stabilization::run();
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

		Communication::sendAllData();
		waitMs(50);
	}
}

void loop() { }

int main(void) {
	init();

	Serial.begin(115200);
	while (!Serial);

	Serial1.begin(115200);
	while (!Serial1);

	Wire.begin();
	delay(500);

	chBegin(mainThread);

	while(1);

	return 0;
}
