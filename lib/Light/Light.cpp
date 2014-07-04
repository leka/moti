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
bool Light::_is_init = false;
bool Light::_is_started = false;
Led Light::leds[N_LEDS] = { Led(9, 10, 11) };
LedData Light::data[N_LEDS] = { {Color(0,0,0), Color(0,0,0), Color(0,0,0), Color(0,0,0), 0, 0, INACTIVE} };

static WORKING_AREA(light_thread_area, 64);

void Light::__init__(void) {
	if (!_is_init) {
		_is_init = true;

		leds[0] = Led(11, 12, 13);
	}
}

void Light::__start__(void* arg, tprio_t priority) {
	if (!_is_init)
		Light::__init__();

	if (!_is_started) {
		_is_started = true;

		(void)chThdCreateStatic(light_thread_area,
								sizeof(light_thread_area),
								priority, thread, arg);
	}
}

void Light::fade(LedIndicator led, Color start_color, Color end_color, int16_t duration) {
	if (!_is_started)
		Light::__start__();

	uint8_t i = (uint8_t)led;

	data[i].start_color = start_color;
	data[i].end_color = end_color;
	data[i].total_steps = duration / 30;
	data[i].steps = 0;
	data[i].state = FADE;

	data[i].diff = Color(end_color.getR() - start_color.getR(),
						 end_color.getG() - start_color.getG(),
						 end_color.getB() - start_color.getB());

	data[i].current = start_color;

	chSemSignal(&_sem);
}

void Light::turnOff(LedIndicator led) {
	if (!_is_started)
		Light::__start__();

	uint8_t i = (uint8_t)led;

	leds[i].turnOff();
	Serial.println("OFF");
}

LedState Light::getState(LedIndicator led) {
	uint8_t i = (uint8_t)led;

	return data[i].state;
}

msg_t Light::thread(void* arg) {
	bool no_recall = true;

	while (!chThdShouldTerminate()) {
		chSemWait(&_sem);

		while (TRUE) {
			no_recall = true;

			for (uint8_t i = 0; i < N_LEDS; ++i) {
				switch (data[i].state) {
				case FADE:
					data[i].current.setRGB(data[i].start_color.getR() + data[i].diff.getR() * data[i].steps / data[i].total_steps,
										   data[i].start_color.getG() + data[i].diff.getG() * data[i].steps / data[i].total_steps,
										   data[i].start_color.getB() + data[i].diff.getB() * data[i].steps / data[i].total_steps);
					leds[i].shine(data[i].current);
					
					++data[i].steps;

					if (data[i].steps == data[i].total_steps) {
						data[i].state = INACTIVE;
						leds[i].shine(data[i].end_color);
					}
					else
						no_recall = false;

					break;

				case SHINE:
					break;

				case INACTIVE:
					break;			
				}
			}

			waitMs(30);

			if (no_recall)
				break;
		}
	}

	return (msg_t)0;
}
