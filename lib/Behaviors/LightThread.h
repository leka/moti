#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Behaviors.h"

static msg_t LightThreadFunction(void *arg) {

	(void)arg;

	while (TRUE) {

		chSemWait(&LightSem);

		// serial.println("Drive");
		// driveSystem.stop();
		// light.turnOff();

		if (getBehavior() == WAKE_UP) {
			light.fade(400, BLUE, ORANGE);
			light.fade(200, ORANGE, PURPLE);
			light.fade(400, PURPLE, GREEN);
			light.fade(200, GREEN, LIGHT_PINK);

			chThdSleepMilliseconds(1000);

			light.shine(RAND);
			chThdSleepMilliseconds(150);
			light.shine(RAND);
			chThdSleepMilliseconds(150);
			light.shine(RAND);
			chThdSleepMilliseconds(150);
			light.shine(RAND);

			chThdSleepMilliseconds(400);

			light.turnOff();

			chThdSleepMilliseconds(400);

			setBehavior(EXPLORE);
		}

		else if (getBehavior() == EXPLORE) {
			light.fade(500, PURPLE, BLACK);
			light.fade(500, BLACK, PURPLE);
		}

		else if (getBehavior() == WAITING) {
			light.fade(500, RED_PURE, GREEN_PURE);
			light.fade(500, GREEN_PURE, BLUE_PURE);
			light.fade(500, BLUE_PURE, RED_PURE);
		}

		else if (getBehavior() == WANT_INTERACTION) {

			light.fade(300, BLACK, ORANGE);
			light.turnOff();
			light.fade(300, BLACK, ORANGE);
			light.turnOff();
			light.fade(300, BLACK, ORANGE);
			light.turnOff();
			light.fade(300, BLACK, ORANGE);
			light.turnOff();

			_numberOfCallsForInteraction++;
			setBehavior(WAITING);
		}

		else if (getBehavior() == SLEEP) {
			// serial.println("Sleep light start");

			volatile uint8_t basePwm = 0; // divided by ten to have a wait delay higher than 1ms
			volatile uint8_t bpm = 35;     // must multiply by ten in heart.shine();
			volatile uint8_t R = 250;

			light.fade(1300, 0, 0, 0, 0, basePwm, R);
			light.fade(650, 0, 0, 0, 0, R, basePwm);

			chThdSleepMilliseconds(30000/ bpm);

			// serial.println("Sleep light end");
		}
	}
	return 0;
}


