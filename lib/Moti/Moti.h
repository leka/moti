/*
   Copyright (C) 2013-2014 Ladislas de Toldi <ladislas at weareleka dot com>
   and Leka <http://weareleka.com>

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

#ifndef LEKA_MOTI_MODULE_MOTI_H_
#define LEKA_MOTI_MODULE_MOTI_H_

/**
 * @file Moti.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Toolbox.h"
#include "Sensors.h"

#define HISTORY_SIZE 6

void waitMs(uint16_t ms);

namespace Moti {

	// Thread
	msg_t moduleThread(void* arg);
	void start(void* arg = NULL, tprio_t priority = NORMALPRIO + 1);
	void run(void);
	void stop(void);

	// Methods
	uint8_t getLapsZ(void);

	// States
	void detectStuck(void);
	bool isStuck(void);
	void detectFall(void);
	bool isFalling(void);

	void detectShake(void);
	bool isShaken(void);
	bool isShakenX(void);
	bool isShakenY(void);
	bool isShakenZ(void);

	void detectSpin(void);
	bool isSpinning(void);
	bool isSpinningY(void);
	bool isSpinningP(void);
	bool isSpinningR(void);

}

#endif
