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
#include <Serial.h>

/**
 * @file Serial.cpp
 * @author Ladislas de Toldi
 * @version 1.0
 */

/**
 * @brief Send the value of a uint8_t as a 8 bits (1 byte) binary
 *
 * writeByte() sends values as 8 bits binaries. It uses Serial.write() and is used inside sendDataBinary().
 *
 * @param value the value you need to write.
 */
void sio::writeByte(uint8_t value){
	serial.write(value);
}

/**
 * @brief Send the value of a int16_t as a 16 bits (2 bytes) binary
 *
 * writeInt() is used to send the two bytes that comprise a two byte (16 bit) integer.
 *
 * Serial.write(lowByte(value)) sends the low byte
 * Serial.write(highByte(value)) sends the high byte
 *
 * @param value the value you want to write
 */
void sio::writeInt(int value){
	serial.write(lowByte(value));
	serial.write(highByte(value));
}

/**
 * @brief read byte in serial buffer
 *
 * @return the value
 */
uint8_t sio::readByte(){
	return serial.read();
}

/**
 * @brief check if there is serial data avalaible
 *
 * @return return true if serial communication is avalaible, false if it's not.
 */
bool sio::avalaible(){
	if (serial.available() > 0) {
		return true;
	}
	else
		return false;
}
