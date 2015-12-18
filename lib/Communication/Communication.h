/*
   Copyright (C) 2013-2014 Ladislas de Toldi <ladislas at leka dot com> and Leka <http://leka.io>

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

#ifndef LEKA_MOTI_MODULE_COMMUNICATION_H_
#define LEKA_MOTI_MODULE_COMMUNICATION_H_

/**
 * @file Communication.h
 * @author Ladislas de Toldi & Flavien Raynaud
 * @revision Gareth Dys
 * @version 2.0
 */

#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Moti.h"
#include "Light.h"
#include "DriveSystem.h"
#include "Sensors.h"

 #define serialPort Serial1

namespace Communication {

	void sendMotorData(void);
	void sendLedData(void);
	void sendSensorData(void);
	void sendAllData(void);

}

class Interface_Communication
{
public:
   //Interface_Communication(arguments);
   virtual ~Interface_Communication();
   
   virtual void sendData(void) = 0;
   virtual void getData(void) = 0;

protected:

private:


   /* data */
};

class Bluetooth : public Interface_Communication
{
public:
   Bluetooth();
   ~Bluetooth();

   void sendData(void) override;
   void getData(void) override;

   void updateFrame(void);

private:

   float _accX;
   float _accY;
   float _accZ;
   
   //Yaw 
   float _gyrY;
   //Pitch
   float _gyrP;
   //Roll
   float _gyrR;

   float _eulerPhi;
   float _eulerTheta;
   float _eulerPsi;

   /* data */
};

//Interface for for class setting the rules for all data frame sizes
// class Frame
// {
// public:
//     Frame(arguments);
//    ~ Frame();

//     data 
// private:
//    uint8_t _ID;
//    uint8_t _frameSize;
//    Byte* data;
// };

#endif
