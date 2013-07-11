//######################################################################//
//	MOTI SOFTWARE v2.0													//
//	COPYRIGHT WE ARE LEKA! - SOURCE CODE DISTRIBUTED UNDER MIT LICENCE	//
//######################################################################//


//###########//
// LIBRARIES //
//###########//

#include "Arduino.h"

#include "Moti.h"

#include "RGBLED.h"

#include <Wire.h>

#include <CommunicationUtils.h>
#include <DebugUtils.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <FreeSixIMU.h>


MOTI Moti = MOTI();
String inData;

//#######//
// SETUP //
//#######//

void setup() {
	Moti.initVerbose();
}

void listenForSerialCommand();
void serialServer();
void serialRouter();


//######//
// LOOP //
//######//

void loop() {
	/**
	 * First check if serial commands have been sent to the robot.
	 */
	listenForSerialCommand();


	while(Serial.available() > 0){
		char recieved = Serial.read();
		inData += recieved;

		if (recieved == '\n'){

			if(inData == "help\n" || inData == "h\n"){
				Serial.println(F("\n========== Moti's Help =========="));
				Serial.println(F("h or help   ---> Show help"));
				Serial.println(F("r or remote ---> Enable remote control of the robot"));
				Serial.println(F("d or data   ---> Send sensors data"));
				Serial.println(F("L/r/g/b     ---> Output color with led (e.g. L/125/26/213)"));
				Serial.println(F("f           ---> Go forward"));
				Serial.println(F("F/speed     ---> Go forward at chosen speed (e.g. F/200)"));
				Serial.println(F("b           ---> Go backward"));
				Serial.println(F("B/speed     ---> Go backward at chosen speed (e.g. F/200)"));
				Serial.println(F("q or quit   ---> Quit remote control"));
			}
			else if(inData == "remote\n"){
				Moti.setRemoteState(true);
			}
			else if(inData == "quit\n"){
				Moti.setRemoteState(false);
			}
		}
	}

	/**
	 * Then do the rest of the program
	 */
	if(Moti.getRemoteState() == true){
		Serial.println("Moti remote state is: true");
	}
	else{
		Serial.println("Moti remote state is: false");
	}

	inData = ""; // Clear recieved buffer
	delay(Moti.getLoopDelay());
}

void listenForSerialCommand(){
	while(Serial.available() > 0){
		char recieved = Serial.read();
		inData += recieved;

		if (recieved == '\n'){

			if(inData == "help\n" || inData == "h\n"){
				Serial.println(F("\n========== Moti's Help =========="));
				Serial.println(F("h or help   ---> Show help"));
				Serial.println(F("r or remote ---> Enable remote control of the robot"));
				Serial.println(F("d or data   ---> Send sensors data"));
				Serial.println(F("L/r/g/b     ---> Output color with led (e.g. L/125/26/213)"));
				Serial.println(F("f           ---> Go forward"));
				Serial.println(F("F/speed     ---> Go forward at chosen speed (e.g. F/200)"));
				Serial.println(F("b           ---> Go backward"));
				Serial.println(F("B/speed     ---> Go backward at chosen speed (e.g. F/200)"));
				Serial.println(F("q or quit   ---> Quit remote control"));
			}
			else if(inData == "r\n" || inData == "remote\n"){
				Serial.println(F("Remote control activated"));
				Moti.setRemoteState(true);
			}
			else {
				Serial.println(F("Before sending command, you must enable the remote control mode by sending \"r\" or \"remote\"."));
			}
		}
	}
}

void remoteControl(){
	if(Moti.getRemoteSate()){
		
	}

}
