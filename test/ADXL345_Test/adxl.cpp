#define serial Serial

#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include <Wire.h>

#include "CommunicationUtils.h"
#include "DebugUtils.h"
#include "ADXL345.h"
#include "ITG3200.h"
#include "FreeIMU.h"

#include "Serial.h"
#include "Tools.h"

#include "Sensors.h"

Sensors sensors;

void chSetup() {
    pinMode(13, OUTPUT);

    Serial.println("Starting...");

    ADXL345 ad = sensors.getAccelGyro().acc;

    ad.setFreeFallThreshold(8);
    ad.setFreeFallDuration(3);

    ad.setInterruptMapping(ADXL345_INT_FREE_FALL_BIT, ADXL345_INT1_PIN);
    ad.setInterrupt(ADXL345_INT_FREE_FALL_BIT, 1);

    /*
    ad.setActivityThreshold(75);
    ad.setInactivityThreshold(75);
    ad.setTimeInactivity(5);
    ad.setInactivityX(1);
    ad.setInactivityY(1);
    ad.setInactivityZ(1);
    ad.setActivityX(1);
    ad.setActivityY(1);
    ad.setActivityZ(1);

    ad.setInterruptMapping(ADXL345_INT_ACTIVITY_BIT, ADXL345_INT1_PIN);
    ad.setInterrupt( ADXL345_INT_ACTIVITY_BIT, 1);
    ad.setInterruptMapping(ADXL345_INT_INACTIVITY_BIT, ADXL345_INT1_PIN);
    ad.setInterrupt(ADXL345_INT_INACTIVITY_BIT, 1);


    ad.setTapDetectionOnX(0);
    ad.setTapDetectionOnY(0);
    ad.setTapDetectionOnZ(1);

    ad.setTapThreshold(50);
    ad.setTapDuration(15);
    ad.setDoubleTapLatency(80);
    ad.setDoubleTapWindow(200);
    */

    while (TRUE) { 
        if(ad.getInterruptSource(ADXL345_INT_FREE_FALL_BIT)) {
            Serial.println("WOOOOOOOOOHOUU");
            digitalWrite(13, HIGH);
            delay(350);
        }
        else
            digitalWrite(13, LOW);

        /*
        if(ad.getInterruptSource(ADXL345_INT_INACTIVITY_BIT))
            Serial.println("HMMMM");

        if(ad.getInterruptSource(ADXL345_INT_SINGLE_TAP_BIT))
            Serial.println("SINGLE TAP");
        */

        /* delay(500); */
    }
}


void setup() {
    Serial.begin(115200);
    sensors.init();

    chBegin(chSetup);

    while(1);
}

void loop() { }
