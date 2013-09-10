#ifndef LEKA_MOTI_ARDUINO_DEBUG_H_
#define LEKA_MOTI_ARDUINO_DEBUG_H_

#include <Arduino.h>
#include <Serial.h>

namespace Debug {

	bool debug = false;

	void log(String string){
		if (debug) {
			serial.println(string);	
		}
	}
}

	
#endif