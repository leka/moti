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