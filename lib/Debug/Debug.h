#ifndef LEKA_MOTI_ARDUINO_DEBUG_H_
#define LEKA_MOTI_ARDUINO_DEBUG_H_

#ifndef debug
#define debug false
#endif

#include <Arduino.h>
#include <Serial.h>

namespace Debug {

	void log(String string){
		if (debug) {
			serial.println(string);	
		}
	}
}

	
#endif