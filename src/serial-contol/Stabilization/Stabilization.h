
#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Configuration.h"

class Stabilization {
    public:
        static void start(void* arg=NULL, tprio_t priority=NORMALPRIO);

        static void run(void);
        static void stop(void);

    private:
        static bool _isStarted, _isRunning;
        static msg_t thread(void* arg);
};

bool Stabilization::_isStarted = false;
bool Stabilization::_isRunning = false;

static WORKING_AREA(stabilizationThreadArea, 256);

void Stabilization::start(void* arg, tprio_t priority) {
    if (!_isStarted) {
        _isStarted = true;
        _isRunning = true;

        (void)chThdCreateStatic(stabilizationThreadArea,
                sizeof(stabilizationThreadArea),
                priority, thread, arg);
    }
}

void Stabilization::run(void) {
    _isRunning = true;
}

void Stabilization::stop(void) {
    _isRunning = false;
}

msg_t Stabilization::thread(void* arg) {
    float currentAngle = 0.0;
    float input = 0.0;
    int16_t output = 0.0;

    while (!chThdShouldTerminate()) {
        /*
        if (Light::getState(HEART) == INACTIVE) {
            Light::fade(HEART, Color::randomColor(), Color::randomColor(), 1500);
        }
        */

        /* currentAngle = Sensors::getEulerPhi(); */

        if (_isRunning) {
            input = Sensors::getAccX();
            output = (int16_t)(-0.75 * input);
            
            if (abs(output) > 100.0f) {
                DriveSystem::go(output < 0 ? BACKWARD : FORWARD, (uint8_t)abs(output), 100);
            }
            else if (Sensors::getAccY() > 80) {
                Serial.println(F("SPIN RIGHT"));
                DriveSystem::spin(RIGHT, 200, 1.57f);
            }
            else if (Sensors::getAccY() < -80) {
                Serial.println(F("SPIN LEFT"));
                DriveSystem::spin(LEFT, 200, 1.57f);
            }
            /* else if (abs(currentAngle) > 0.45f) {
                Serial.println(F("FACING"));
                DriveSystem::spin(currentAngle > 0.0f ? LEFT : RIGHT, 150, abs(currentAngle));
            } */
            else if (DriveSystem::getState() != NONE) {
                DriveSystem::stop(0);
            }
        }

        waitMs(STABILIZATION_THREAD_DELAY);
    }

    return (msg_t)0;
}