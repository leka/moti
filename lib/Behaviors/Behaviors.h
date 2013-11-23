#ifndef LEKA_MOTI_ARDUINO_BEHAVIORS_H_
#define LEKA_MOTI_ARDUINO_BEHAVIORS_H_

#include <Arduino.h>
#include <Wire.h>

#include "Sensors.hpp"
#include "Led.hpp"
#include "Motor.hpp"
#include "Serial.hpp"

enum BehaviorName {
		WAKE_UP, WAIT, REACT, REMOTE, CRUISE, ESCAPE, STABILIZE, SHUT_DOWN, SPINBLINK
	};


/**
 * @class Behaviors
 * @brief Moti's Behaviors
 */
class Behaviors {

	public:

		Behaviors();

		void init();

		void router();
		void server();

		//Behaviors
		void setBehavior(uint8_t behavior);
		uint8_t getBehavior();

		void cruise();
		void wait();
		void wakeup();
		void react();
		void stabilize();
		void escape();
		void stopAndBlink();
		void shutDown();
		void remote();

	private:
		//	Variables
		uint8_t orderNumber;
		uint8_t reactNumber;
		uint8_t behavior;

		//	Objects
		Led rightLed = Led(11, 12, 13);
		Led leftLed = Led(8, 9, 10);
		Sensors sensors;
};

#endif