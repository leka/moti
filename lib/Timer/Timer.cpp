#include <Arduino.h>
#include <Timer.h>

/**
 * @file Timer.cpp
 * @author Simon Monk - http://www.simonmonk.org
 * @licence GNU GPL
 * @version 1.0
 */


Timer::Timer(void){
}

int8_t Timer::every(unsigned long period, void (*callback)(), int repeatCount){
	int8_t i = findFreeEventIndex();
	if (i == -1) return -1;

	_events[i].eventType = EVENT_EVERY;
	_events[i].period = period;
	_events[i].repeatCount = repeatCount;
	_events[i].callback = callback;
	_events[i].lastEventTime = millis();
	_events[i].count = 0;
	return i;
}

int8_t Timer::every(unsigned long period, void (*callback)()){
	return every(period, callback, -1); // - means forever
}

int8_t Timer::after(unsigned long period, void (*callback)()){
	return every(period, callback, 1);
}

int8_t Timer::oscillateOrPulse(uint8_t pin, unsigned long period, uint8_t startingValue, int repeatCount, void (*callback)(void)){
	int8_t i = findFreeEventIndex();
	if (i == NO_TIMER_AVAILABLE) return NO_TIMER_AVAILABLE;

	_events[i].eventType = EVENT_OSCILLATE;
	_events[i].pin = pin;
	_events[i].period = period;
	_events[i].pinState = startingValue;
	digitalWrite(pin, startingValue);
	_events[i].repeatCount = repeatCount;
	_events[i].callback = callback;
	_events[i].lastEventTime = millis();
	_events[i].count = 0;
	return i;
}

int8_t Timer::oscillate(uint8_t pin, unsigned long period, uint8_t startingValue, int repeatCount, void (*callback)(void)){
	return oscillateOrPulse(pin, period, startingValue, repeatCount*2-1, callback); // full cycles not transitions
}

int8_t Timer::oscillate(uint8_t pin, unsigned long period, uint8_t startingValue){
	return oscillateOrPulse(pin, period, startingValue, -1, 0); // forever
}

/**
 * This method will generate a pulse of startingValue, starting immediately and of
 * length period. The pin will be left in the !startingValue state
 */
int8_t Timer::pulse(uint8_t pin, unsigned long period, uint8_t startingValue, void (*callback)(void)){
	return oscillateOrPulse(pin, period, startingValue, 1, callback); // once
}

void Timer::stop(int8_t id){
	if (id >= 0 && id < MAX_NUMBER_OF_EVENTS) {
		_events[id].eventType = EVENT_NONE;
	}
}

void Timer::update(void){
	for (int8_t i = 0; i < MAX_NUMBER_OF_EVENTS; i++)
	{
		if (_events[i].eventType != EVENT_NONE)
		{
			_events[i].update();
		}
	}
}

int8_t Timer::findFreeEventIndex(void){
	for (int8_t i = 0; i < MAX_NUMBER_OF_EVENTS; i++)
	{
		if (_events[i].eventType == EVENT_NONE)
		{
			return i;
		}
	}
	return NO_TIMER_AVAILABLE;
}
