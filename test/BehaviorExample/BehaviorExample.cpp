#include <Arduino.h>
#include <Wire.h>

#include "Motion.h"
#include "Moti.h"
#include "Light.h"
#include "Communication.h"
#include "Serial.h"

#include "ChibiOS_AVR.h"
#include "Configuration.h"
#include "Color.h"
#include "DriveSystem.h"
#include "Motion.h"
#include "FreeIMU.h"
#include "Led.h"
#include "Light.h"
#include "Communication.h"
#include "Motor.h"
#include "Queue.h"
#include "Sensors.h"
#include "Serial.h"

#include "lib/Stabilization/Stabilization.h"

void mainThread() {

    // Init part
    Wire.begin();
    delay(500);

    Sensors::init();
    DriveSystem::start();
    Motion::start();
    Moti::start();
    Light::start();

    // Init our new behavior
    Stabilization::start();

    // Set variables
    bool stabilize = false;

    while (TRUE) {
        if (Moti::isShaken()) {
            if (!stabilize)
                Stabilization::run();
            else
                Stabilization::stop();

            stabilize = !stabilize;
        }

        waitMs(50);
    }
}

void setup() {

    chBegin(mainThread);

    while(1);
}

void loop() {
    // nothing to do here
}
