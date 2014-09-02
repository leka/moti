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

/**
 * @file Serial.h
 * @author Ladislas de Toldi & Flavien Raynaud
 * @version 1.0
 */

#include <Arduino.h>
#include "Moti.h"
#include "Color.h"

typedef enum {
	COMMAND_GO,
	COMMAND_SPIN,
	COMMAND_STOP,
	COMMAND_FADE,

	COMMAND_TOGGLE,

	COMMAND_NONE
} COMMAND_TYPE;

typedef struct {
	Direction direction;
	uint8_t speed;
	uint16_t duration;
} GO_CMD;

typedef struct {
	Rotation rotation;
	uint8_t speed;
	uint16_t angle;
} SPIN_CMD;

typedef struct {
	LedIndicator indicator;
	uint8_t startR, startG, startB;
	uint8_t endR, endG, endB;
	uint16_t duration;
} FADE_CMD;

typedef union {
	GO_CMD go;
	SPIN_CMD spin;
	FADE_CMD fade;
} COMMAND;

class ReadCommand {
	public:
		ReadCommand(void);

		uint8_t getHeader(void);
		void resetHeader(void);

		void readControlCommand(void);

		uint8_t readByte(void);
		uint16_t readTwoBytes(void);

		COMMAND getCommand();
		COMMAND_TYPE getType();

	private:
		COMMAND cmd;
		COMMAND_TYPE type;
		uint8_t _header;
};

#endif
