#ifndef LEKA_MOTI_ARDUINO_SERIAL_H_
#define LEKA_MOTI_ARDUINO_SERIAL_H_

#include <Arduino.h>

#ifndef serial
#define serial Serial
#endif

namespace sio {

	// Variables
	static const uint8_t dataHeader = 0x0f;
	static const uint8_t dataFooter = 0xf0;

	static const uint8_t readyCheck = 0xff;

	static const uint8_t numberOfSensors = 0x02;

	static const uint8_t initPhase = 0xAA;

	static const uint8_t accelSensor = 0x01;
	static const uint8_t accelData   = 0x06;
	static const uint8_t gyroSensor  = 0x02;
	static const uint8_t gyroData    = 0x06;

	//	Methods
	void writeByte(uint8_t value);
	void writeInt(int value);

	uint8_t readByte();

	bool avalaible();

}

#endif