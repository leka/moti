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

#ifndef LEKA_MOTI_ARDUINO_COMMUNICATION_H_
#define LEKA_MOTI_ARDUINO_COMMUNICATION_H_

/**
 * @file Communication.h
 * @author Ladislas de Toldi & Flavien Raynaud
 * @version 1.0
 */

#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Moti.h"
#include "Light.h"
#include "DriveSystem.h"
#include "Sensors.h"

namespace Communication {

	void sendMotorData(void);
	void sendLedData(void);
	void sendSensorData(void);
	void sendAllData(void);

}

#endif
