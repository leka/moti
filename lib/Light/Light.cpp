/*
Copyright (C) 2013-2014 Ladislas de Toldi <ladislas at weareleka dot com> and Leka <http://weareleka.com>

This file is part of Moti, a spherical robotic smart toy for autistic children.

Moti is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Moti is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Moti. If not, see <http://www.gnu.org/licenses/>.
*/

#include <Arduino.h>
#include "Light.h"


/**
 * @file Light.cpp
 * @author Ladislas de Toldi
 * @version 1.0
 */

Semaphore Light::_sem = _SEMAPHORE_DATA(_sem, 0);
bool Light::_isInit = false;
bool Light::_isStarted = false;
Led Light::leds[N_LEDS] = { Led(11, 12, 13) };
LedData Light::data[N_LEDS] = { {Color(0,0,0), Color(0,0,0), Color(0,0,0), Color(0,0,0), 0, 0, INACTIVE} };

static WORKING_AREA(lightThreadArea, 64);


void Light::fade(LedIndicator led, Color startColor, Color endColor, int16_t duration) {
	if (!_isStarted)
		start();

	uint8_t i = (uint8_t)led;

	data[i].startColor = startColor;
	data[i].endColor = endColor;
	data[i].totalSteps = duration / 30;
	data[i].steps = 0;
	data[i].state = FADE;

	data[i].diff = Color(endColor.getR() - startColor.getR(),
						 endColor.getG() - startColor.getG(),
						 endColor.getB() - startColor.getB());

	data[i].current = startColor;

	chSemSignal(&_sem);
}

void Light::turnOff(LedIndicator led) {
	if (!_isStarted)
		start();

	uint8_t i = (uint8_t)led;

	leds[i].turnOff();
	Serial.println("OFF");
}

LedState Light::getState(LedIndicator led) {
	uint8_t i = (uint8_t)led;

	return data[i].state;
}


void Light::init(void) {
	if (!_isInit) {
		_isInit = true;

		leds[0] = Led(11, 12, 13);
	}
}

void Light::start(void* arg, tprio_t priority) {
	if (!_isInit)
		init();

	if (!_isStarted) {
		_isStarted = true;

		(void)chThdCreateStatic(lightThreadArea,
								sizeof(lightThreadArea),
								priority, thread, arg);
	}
}

msg_t Light::thread(void* arg) {
	bool noRecall = true;

	while (!chThdShouldTerminate()) {
		chSemWait(&_sem);

		while (TRUE) {
			noRecall = true;

			for (uint8_t i = 0; i < N_LEDS; ++i) {
				switch (data[i].state) {
				case FADE:
					data[i].current.setRGB(data[i].startColor.getR() + data[i].diff.getR() * data[i].steps / data[i].totalSteps,
										   data[i].startColor.getG() + data[i].diff.getG() * data[i].steps / data[i].totalSteps,
										   data[i].startColor.getB() + data[i].diff.getB() * data[i].steps / data[i].totalSteps);
					leds[i].shine(data[i].current);
					
					++data[i].steps;

					if (data[i].steps == data[i].totalSteps) {
						data[i].state = INACTIVE;
						leds[i].shine(data[i].endColor);
					}
					else
						noRecall = false;

					break;

				case SHINE:
					break;

				case INACTIVE:
					break;			
				}
			}

			waitMs(30);

			if (noRecall)
				break;
		}
	}

	return (msg_t)0;
}
