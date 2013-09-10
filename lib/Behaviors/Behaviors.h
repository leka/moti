#ifndef LEKA_MOTI_ARDUINO_BEHAVIORS_H_
#define LEKA_MOTI_ARDUINO_BEHAVIORS_H_

#include <Arduino.h>
#include <Motors.h>
#include <Sensors.h>
#include <Led.h>

enum BehaviorName {
		CRUISE, ESCAPE, STABILIZE, SHUT_DOWN, SPINBLINK
	};


/**
 * @class Behaviors
 * @brief Moti's Behaviors
 */
class Behaviors {

	public:		

		Behaviors();
		//	Server & Router
		void router();
		void server();

		//Behaviors
		void setBehavior(uint8_t behavior);
		uint8_t getBehavior();
		
		void cruise();
		void stabilize();
		void escape();
		void stopAndBling();
		void shutDown();
		void remote();

	private:
		//	Variables
		uint8_t behavior;

		//	Objects
		Led rightLed = Led(11, 12, 13);
		Led leftLed = Led(8, 9, 10);
		Sensors sensors;
		Motors motors;
};

#endif