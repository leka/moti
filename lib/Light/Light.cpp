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

#include "Light.h"

/**
 * @file Light.cpp
 * @author Ladislas de Toldi
 * @version 1.0
 */

namespace Light {

	// VARIABLES

	// Thread states
	static WORKING_AREA(lightThreadArea, 256);
	bool _isStarted     = false;
	bool _isInitialized = false;
	uint8_t _threadDelay = 20;

	// Led objects
	uint8_t HEART_LED_RED_PIN = 11;
	uint8_t HEART_LED_GREEN_PIN = 12;
	uint8_t HEART_LED_BLUE_PIN = 13;


	Led leds[N_LEDS] = { Led(HEART_LED_RED_PIN, HEART_LED_GREEN_PIN, HEART_LED_BLUE_PIN) };
	Queue<LedData*> data[N_LEDS] = { Queue<LedData*>() };

	// Misc
	Semaphore _sem = _SEMAPHORE_DATA(_sem, 0);

}

/**
 * @brief Tells a led to fade between two given colors, for a given duration
 * @param led the indicator of the led
 * @param startColor the color the led will shine at the beginning
 * @param endColor the color the led will shine at the end
 * @param duration the duration (in ms)
 */
void Light::fade(LedIndicator led, Color startColor, Color endColor, int16_t duration) {
	if (!_isInitialized)
		init();

	uint8_t i = (uint8_t)led;

	LedData* newData = data[i].getTail();

	newData->startColor = startColor;
	newData->endColor = endColor;
	newData->totalSteps = duration / _threadDelay;
	newData->steps = 0;
	newData->state = FADE;

	newData->diff = Color(endColor.getR() - startColor.getR(),
			endColor.getG() - startColor.getG(),
			endColor.getB() - startColor.getB());

	newData->current = startColor;

	data[i].push();

	chSemSignal(&_sem);
}

/**
 * @brief Tells a led to turn off
 * @param led the indicator of the led
 */
void Light::turnOff(LedIndicator led) {
	if (!_isInitialized)
		init();

	uint8_t i = (uint8_t)led;

	leds[i].turnOff();
}

/**
 * @brief Gets the state of a given led
 * @param led the indicator of the led
 * @return one of the available LedStates
 */
LedState Light::getState(LedIndicator led) {
	uint8_t i = (uint8_t)led;

	if (data[i].isEmpty())
		return INACTIVE;

	return data[i].getHead()->state;
}

/**
 * @brief Gets the color of a given led
 * @param led the indicator of the led
 * @return the color  of the led
 */
Color Light::getColor(LedIndicator led) {
	uint8_t i = (uint8_t)led;

	return leds[i].getColor();
}


void Light::fadeHeart(Color startColor, Color endColor, int16_t duration) {
	fade(HEART, startColor, endColor, duration);
}

void Light::turnHeartOff() {
	turnOff(HEART);
}

LedState Light::getHeartState(void) {
	return getState(HEART);
}

Color Light::getHeartColor(void) {
	return getColor(HEART);
}


void Light::start(void) {
	if (!_isStarted) {
		_isStarted = true;

		// leds[0] = Led(HEART_LED_RED_PIN, HEART_LED_GREEN_PIN, HEART_LED_BLUE_PIN);
		//
		// for (uint8_t i = 0; i < N_LEDS; ++i)
		// 	data[i] = Queue<LedData*>();
	}
}

void Light::init(void* arg, tprio_t priority) {

	(void) arg;

	if (!_isStarted) {
		start();


		(void)chThdCreateStatic(lightThreadArea,
				sizeof(lightThreadArea),
				priority, moduleThread, arg);

		for (uint8_t i = 0; i < N_LEDS; ++i)
			for (uint16_t j = 0; j < QUEUE_MAX_SIZE; ++j)
				data[i].fill(j, new LedData);
	}
}

msg_t Light::moduleThread(void* arg) {

	(void) arg;

	bool noRecall = true;
	LedData* state;

	while (!chThdShouldTerminate()) {
		chSemWait(&_sem);

		while (TRUE) {
			noRecall = true;

			for (uint8_t i = 0; i < N_LEDS; ++i) {
				if (!data[i].isEmpty()) {
					state = data[i].getHead();

					switch (state->state) {
						case FADE:
							state->current.setRGB(state->startColor.getR() + state->diff.getR() * state->steps / state->totalSteps,
									state->startColor.getG() + state->diff.getG() * state->steps / state->totalSteps,
									state->startColor.getB() + state->diff.getB() * state->steps / state->totalSteps
									);

							leds[i].shine(state->current);

							state->steps++;

							if (state->steps == state->totalSteps) {
								leds[i].shine(state->endColor);
								data[i].pop();

								if (!data[i].isEmpty())
									noRecall = false;
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
			}

			waitMs(_threadDelay);

			if (noRecall)
				break;
		}
	}

	return (msg_t)0;
}

