/*
   Copyright (C) 2013-2014 Ladislas de Toldi <ladislas at leka dot io>
   and Leka <http://leka.io>

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

/**
 * @file Communication.cpp
 * @author Ladislas de Toldi and Flavien Raynaud
 * @revision Gareth Dys
 * @version 2.0
 */

#include "Communication.h"

#define serial Serial1



namespace Communication {
	/**
	 * @brief Writes motors data to the serial
	 */
	void sendMotorData(void) {
		serial.print(F("M,"));  /* M like Motors */
		serial.print(DriveSystem::getRightMotorDirection());
		serial.print(F(","));
		serial.print(DriveSystem::getRightMotorSpeed());
		serial.print(F(","));
		serial.print(DriveSystem::getLeftMotorDirection());
		serial.print(F(","));
		serial.print(DriveSystem::getLeftMotorSpeed());
	}


	/**
	 * @brief Writes leds data to the serial
	 */
	void sendLedData(void) {
		Color color = Light::getColor(HEART);

		serial.print(F("L,")); /* L like Leds */
		serial.print(Light::getState(HEART));
		serial.print(F(","));
		serial.print(color.getR());
		serial.print(F(","));
		serial.print(color.getG());
		serial.print(F(","));
		serial.print(color.getB());
	}


	/**
	 * @brief Writes sensors data to the serial
	 */
	void sendSensorData(void) {
		serial.print(F("S,"));
		serial.print(Sensors::getAccX());
		serial.print(F(","));
		serial.print(Sensors::getAccY());
		serial.print(F(","));
		serial.print(Sensors::getAccZ());
		serial.print(F(","));
		serial.print(Sensors::getGyrYDeg());
		serial.print(F(","));
		serial.print(Sensors::getGyrPDeg());
		serial.print(F(","));
		serial.print(Sensors::getGyrRDeg());
	}


	/**
	 * @brief Writes motors, leds and sensors data to the serial
	 */
	void sendAllData(void) {
		serial.print(F("A,")); /* A like All */
		serial.print(millis());
		serial.print(F(";"));

		sendMotorData();
		serial.print(F(";"));
		sendLedData();
		serial.print(F(";"));
		sendSensorData();
		serial.println(F(""));
		serial.flush();
	}
}

//Bluetooth class and functionalities implementation

Bluetooth::Bluetooth(void){

	_accX = Sensors::getAccX();
	_accY = Sensors::getAccY();
    _accZ = Sensors::getAccZ();
   
   //Yaw 
    _gyrY = Sensors::getGyrY();
   //Pitch
    _gyrP = Sensors::getGyrP();
   //Roll
    _gyrR = Sensors::getGyrR();;

    _eulerPhi = Sensors::getEulerPhi();
    _eulerTheta = Sensors::getEulerTheta();
    _eulerPsi = Sensors::getEulerPhi();

    _command = "";

    for (int i = 0; i <17; i ++)
    {
    	_values[i] = 0;
    }
}

Bluetooth::~Bluetooth(void){

}

void Bluetooth::updateFrame(void){
	
	_accX = Sensors::getAccX();
	_accY = Sensors::getAccY();
    _accZ = Sensors::getAccZ();
   
   //Yaw 
    _gyrY = Sensors::getGyrY();
   //Pitch
    _gyrP = Sensors::getGyrP();
   //Roll
    _gyrR = Sensors::getGyrR();;

    _eulerPhi = Sensors::getEulerPhi();
    _eulerTheta = Sensors::getEulerTheta();
    _eulerPsi = Sensors::getEulerPhi();
}

void Bluetooth::sendData(void){

	String frame = String();

	frame ="[";
	frame += millis();
	frame += ",";
	frame += _accX;
	frame += ",";
	frame += _accY;
	frame += ",";
	frame += _accZ;
	frame += ",";
	frame += _gyrY;
	frame +=  ","; 
	frame += _gyrP;
	frame += ",";
	frame += _gyrR;
	frame += ",";
	frame += _eulerPhi;
	frame += ",";
	frame += _eulerTheta;
	frame += ",";
	frame += _eulerPsi;
	frame += "]";

	serialPort.println(frame);

}

void Bluetooth::getData(void){

	String command = "";
	
	while(serialPort.available()) { 
       char caracter= (char)serialPort.read();
       
       // ******* Be sure that what we get is the right value (especially because of noise)
       if (caracter=='['){
         command = "";
         command += (char)caracter; 
       }
       else if (caracter=='-'){
         command += (char)caracter; 
       }  
       else if (caracter=='+'){
         command += (char)caracter; 
       }  
       else if (caracter==','){
         //command += (char)caracter; 
       }
       else if (isdigit(caracter)) {
         command += (char)caracter; 
       }
       else if (caracter==']'){
         command += (char)caracter; 
         if (command.charAt(0)=='[' && command.length()>50){
           _command = command;
           getValuesFromBluetooth();
           command = "";
           break;
         }
         else{
           command = "";
           break;
         }
       }
       else {
         command = "";
         break;
       }
     }
}

void Bluetooth::getValuesFromBluetooth(void)
{
	//substring(from,to), from value is inclusive, to value is exclusive
	serialPort.println("GVFB");
	int k = 9;
	_values[0]=_command.substring(1,5).toInt();
	serialPort.println(_values[0]);
	_values[1]=_command.substring(5,9).toInt();
	serialPort.println(_values[1]);
	// for(int i = 9; i <45: i+3){
	// 	_values[i]=_command.substring(i,i+3) ;
	// }
	for(int i = 2; i < 17; i ++){
		_values[i]=_command.substring(k,k+3).toInt();
		k += 3;
	}
	
}

uint8_t Bluetooth::getValues(int position){

	return _values[position];

}

String Bluetooth::getString(void){
	return _command;
}

Interface_Communication::~Interface_Communication(void){

}


