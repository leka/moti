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
#include "Monitor.h"
#include "Motor.h"
#include "Queue.h"
#include "Sensors.h"
#include "Serial.h"

#include "lib/Arbitrer/Arbitrer.h"
#include "lib/Stabilization/Stabilization.h"


void chSetup() {
	Serial.println(F("Starting..."));

    Sensors::init();
    Drive::start();
    DriveSystem::start();
    // Environment::start();
    // Light::start();

    uint8_t state = 1;
    Stabilization::start();

    ReadCommand readCmd;
    COMMAND cmd;

    while (TRUE) {
        if (readCmd.getHeader() == 1) {
            if (state == 0) {
                Arbitrer::stop();
                DriveSystem::stop(0);
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
                    DriveSystem::go(cmd.go.direction, cmd.go.speed, cmd.go.duration, 500);
                    break;

                case COMMAND_SPIN:
                    Stabilization::stop();
                    DriveSystem::spinDeg(cmd.spin.rotation, cmd.spin.speed, cmd.spin.angle);
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

        Monitor::sendAllData();
        waitMs(50);
    }
}


void setup() {
	Serial.begin(115200);
	while (!Serial);

    Serial1.begin(115200);
    while (!Serial1);

	Wire.begin();
	delay(500);

	chBegin(chSetup);

	while(1);
}

void loop() { }
