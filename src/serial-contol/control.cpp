#include <Arduino.h>
#include <Wire.h>

#include "Moti.h"
#include "ChibiOS_AVR.h"
#include "Configuration.h"
#include "Color.h"
#include "Drive.h"
#include "DriveSystem.h"
#include "FreeIMU.h"
#include "Led.h"
#include "Light.h"
#include "Motor.h"
#include "Sensors.h"
#include "Serial.h"

/* #include "Vector.h" */


void chSetup() {
    Serial.println(F("Starting..."));

    while (TRUE) {
        Serial.println(F("Reading..."));

        READ_COMMAND cmd = readCommand();

        switch (cmd.type) {
        case COMMAND_GO:
            DriveSystem::go(cmd.cmd.go.direction, cmd.cmd.go.speed, cmd.cmd.go.duration);
            break;

        case COMMAND_SPIN:
            DriveSystem::spinDeg(cmd.cmd.spin.rotation, cmd.cmd.spin.speed, cmd.cmd.spin.angle);
            break;

        case COMMAND_STOP:
            DriveSystem::stop();
            break;

        case COMMAND_FADE:
            Light::fade(cmd.cmd.fade.indicator,
                        Color(cmd.cmd.fade.startR, cmd.cmd.fade.startG, cmd.cmd.fade.startB),
                        Color(cmd.cmd.fade.endR, cmd.cmd.fade.endG, cmd.cmd.fade.endB),
                        cmd.cmd.fade.duration);
            break;
        }
    }
}


void setup() {
    Serial.begin(115200);
    while (!Serial);

    Wire.begin();
    delay(500);

    chBegin(chSetup);

    while(1);
}

void loop() { }
