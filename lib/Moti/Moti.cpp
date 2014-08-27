#include "Moti.h"
#include "ChibiOS_AVR.h"

void waitMs(uint16_t ms) {
	chThdSleepMilliseconds(ms);
}

namespace Moti {

bool _isStarted = false;
bool _isRunning = false;
bool _isStuck = false;
uint32_t _startStuckTime = 0;

msg_t thread(void* arg);

static WORKING_AREA(environmentThreadArea, 128);


/**
 * @brief Tells the Environment thread to run and check for events
 */
void run(void) {
        _isRunning = true;
}

/**
 * @brief Tells the Environment thread to stop checking for event
 */
void stop(void) {
        _isRunning = false;
        _isStuck = false;
}

/**
 * @brief Returns whether the device is stuck or not
 * @return true if it is stuck, false otherwise
 */
bool isStuck() {
        if (!_isStarted)
                start();

        return _isStuck && (abs(millis() - _startStuckTime) > ENVIRONMENT_STUCK_TIME);
}


void start(void* arg, tprio_t priority) {
        if (!_isStarted) {
                _isStarted = true;

                (void)chThdCreateStatic(environmentThreadArea, sizeof(environmentThreadArea),
                                priority, thread, arg);

        }
}

msg_t thread(void* arg) {
        while (!chThdShouldTerminate()) {
                if (_isRunning) {
                        if (abs(Sensors::getAccX()) > ENVIRONMENT_STUCK_THRESHOLD) {
                                if (!_isStuck) {
                                        _isStuck = true;
                                        _startStuckTime = millis();
                                }
                        }
                        else
                                _isStuck = false;

                }

                waitMs(ENVIRONMENT_THREAD_DELAY);
        }

        return (msg_t)0;
}
}
