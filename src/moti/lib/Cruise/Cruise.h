#ifndef LEKA_MOTI_ARDUINO_CRUISE_H_
#define LEKA_MOTI_ARDUINO_CRUISE_H_

#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "DriveSystem.h"

class Cruise {
    public:
        static void launch(void);
        static void stop(void);

        static bool isCruising(void);

    private:
        static void start(void* arg=NULL, tprio_t priority=NORMALPRIO+1);

        static bool _isStarted, _isCruising;

        static Semaphore _sem;
        static msg_t thread(void* arg);
};

bool Cruise::_isStarted = false;
bool Cruise::_isCruising = false;
Semaphore Cruise::_sem = _SEMAPHORE_DATA(Cruise::_sem, 0);


static WORKING_AREA(cruiseThreadArea, 256);


void Cruise::launch(void) {
    if (!_isStarted)
        Cruise::start();

    if (!_isCruising) {
        _isCruising = true;
        chSemSignal(&_sem);
    }
}

void Cruise::stop(void) {
    if (!_isStarted)
        Cruise::start();

    Serial.println(_isCruising);

    if (_isCruising) {
        _isCruising = false;
        chSemSignal(&_sem);
    }
}

bool Cruise::isCruising(void) {
    return _isCruising;
}


void Cruise::start(void* arg, tprio_t priority) {
    if (!_isStarted) {
        _isStarted = true;

        (void)chThdCreateStatic(cruiseThreadArea, sizeof(cruiseThreadArea),
                priority, thread, arg);
    }
}

msg_t Cruise::thread(void* arg) {
    while (!chThdShouldTerminate()) {
        chSemWait(&_sem);

        if (_isCruising)
            DriveSystem::go(FORWARD, 255, 0);
        else
            DriveSystem::stop();
    }

    return (msg_t)0;
}

#endif
