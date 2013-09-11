#ifndef LEKA_MOTI_ARDUINO_TIMER_H_
#define LEKA_MOTI_ARDUINO_TIMER_H_

/**
 * @file Timer.h
 * @brief Timer takes care of all the time related issues
 * @author Simon Monk - http://www.simonmonk.org
 * @licence GNU GPL
 * @version 1.0
 */

#include <inttypes.h>
#include <Event.h>

#ifndef MAX_NUMBER_OF_EVENTS
#define MAX_NUMBER_OF_EVENTS (10)
#endif

#define TIMER_NOT_AN_EVENT (-2)
#define NO_TIMER_AVAILABLE (-1)

class Timer {

	public:

		Timer(void);

		int8_t every(unsigned long period, void (*callback)(void));
		int8_t every(unsigned long period, void (*callback)(void), int repeatCount);
		int8_t after(unsigned long duration, void (*callback)(void));
		int8_t oscillate(uint8_t pin, unsigned long period, uint8_t startingValue);
		int8_t oscillate(uint8_t pin, unsigned long period, uint8_t startingValue, int repeatCount, void (*callback)(void) = 0);
		/**
		 * This method will generate a pulse of pulseValue, starting immediately and of
		 * length period. The pin will be left in the !pulseValue state
		 */
		int8_t pulse(uint8_t pin, unsigned long period, uint8_t startingValue, void (*callback)(void) = 0);

		void stop(int8_t id);
		void update(void);

	protected:

		Event _events[MAX_NUMBER_OF_EVENTS];
		int8_t oscillateOrPulse(uint8_t pin, unsigned long period, uint8_t startingValue, int repeatCount, void (*callback)(void));
		int8_t findFreeEventIndex(void);
};

#endif
