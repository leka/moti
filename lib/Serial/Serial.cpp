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
#include "Serial.h"

#define serial Serial1

/**
 * @file Serial.cpp
 * @author Ladislas de Toldi & Flavien Raynaud
 * @version 1.0
 */


ReadCommand::ReadCommand(void) {
	_header = 0;
}

/**
 * @brief Returns the header read from serial
 * @return the header (if it did not change since last frame, will not change)
 */
uint8_t ReadCommand::getHeader(void) {
	if ((_header != 1) && (_header != 42) && serial.available())
		_header = readByte();

	return _header;
}

/**
 * @brief Resets the header (set it to 0)
 */
void ReadCommand::resetHeader(void) {
	_header = 0;
}

/**
 * @brief Read a control command (GO, SPIN, STOP, FADE LED)
 */
void ReadCommand::readControlCommand(void) {
	type = COMMAND_NONE;

	uint8_t actionByte = readByte();

	if (actionByte > 0x03)
		return;

	type = (COMMAND_TYPE)actionByte;

	switch (type) {
		case COMMAND_GO:
			cmd.go.direction = (Direction)readByte();
			cmd.go.speed = readByte();
			cmd.go.duration = readTwoBytes();
			break;

		case COMMAND_SPIN:
			cmd.spin.rotation = (Rotation)readByte();
			cmd.spin.speed = readByte();
			cmd.spin.angle = readTwoBytes();
			break;

		case COMMAND_STOP:
			break;

		case COMMAND_FADE:
			cmd.fade.indicator = (LedIndicator)readByte();
			cmd.fade.startR = readByte();
			cmd.fade.startG = readByte();
			cmd.fade.startB = readByte();
			cmd.fade.endR = readByte();
			cmd.fade.endG = readByte();
			cmd.fade.endB = readByte();
			cmd.fade.duration = readTwoBytes();

		default:
			break;
	}

	_header = 0; /* Reset the header to tell that the control command has been handled */
}

uint8_t ReadCommand::readByte(void) {
	while (!serial.available());

	/* uint8_t u = serial.read();

	   Serial.println(u); */

	return (uint8_t)serial.read();
}

uint16_t ReadCommand::readTwoBytes(void) {
	uint8_t first = readByte();
	uint8_t second = readByte();

	return ((uint16_t)first << 8) + (uint16_t)second;
}

COMMAND ReadCommand::getCommand(void) {
	return cmd;
}

COMMAND_TYPE ReadCommand::getType(void) {
	return type;
}
