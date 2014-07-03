#include <Arduino.h>
#include <Wire.h>

#include "ChibiOS_AVR.h"
#include "Color.h"
#include "Drive.h"
#include "Led.h"
#include "Light.h"
#include "Moti.h"
#include "Motor.h"


void chSetup() {
    pinMode(13, OUTPUT);

    Serial.println("Starting...");

    while (TRUE);
}


void setup() {
    Serial.begin(115200);

    chBegin(chSetup);

    while(1);
}

void loop() { }
