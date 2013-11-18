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
