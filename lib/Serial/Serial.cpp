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

uint8_t readByte(void) {
	while (!serial.available());

	return (uint8_t)serial.read();
}

uint16_t readTwoBytes(void) {
	uint8_t first = readByte();
	uint8_t second = readByte();

	return ((uint16_t)first << 8) + (uint16_t)second;
}

ReadCommand::ReadCommand(void) { }

void ReadCommand::read(void) {
	type = COMMAND_NONE;

	if (readByte() == 42) {
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
	}
	else
		ReadCommand();
}

COMMAND ReadCommand::getCommand(void) {
	return cmd;
}

COMMAND_TYPE ReadCommand::getType(void) {
	return type;
}
