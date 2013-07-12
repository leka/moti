#include "Moti.h"
#include "Arduino.h"

//##############################//
// REMOTE CONTROL FROM COMPUTER //
//##############################//

/**
 * @brief Display the help options when using remote control from the Arduino Serial Monitor
 */
void MOTI::remoteDisplayHelp(){
	Serial.println(F("\n========== Moti's Help =========="));
	Serial.println(F("h       ---> Show help"));
	Serial.println(F("r       ---> Enable remote control of the robot"));
	Serial.println(F("d       ---> Send sensors data"));
	Serial.println(F("L/r/g/b ---> Output color with led (e.g. L/125/26/213)"));
	Serial.println(F("f       ---> Go forward"));
	Serial.println(F("F/speed ---> Go forward at chosen speed (e.g. F/200)"));
	Serial.println(F("b       ---> Go backward"));
	Serial.println(F("B/speed ---> Go backward at chosen speed (e.g. F/200)"));
	Serial.println(F("q       ---> Quit remote control"));
}

/**
 * @brief Check for serial commands from computer.
 *
 * Command are send as bytes and note as ASCII characters. Therefore, to activate the remote, you have to press "r" from the Arduino Serial Monitor or send a byte with the value "114" otherwise.
 */
void MOTI::serialServer(){
	if(getRemoteState() == false){
		while(Serial.available() > 0){
			byte recievedByte = Serial.read();

			if(recievedByte == 114){
				Serial.println(F("Remote control activated"));
				setRemoteState(true);
			}
			else {
				Serial.println(F("Press \"r\" to activate remote control."));
			}
		}
	}

	if(getRemoteState() == true){
		serialRouter();
	}
}

/**
 * @brief This method acts like a router for the serial commands.
 *
 * It treats and interprets the serial byte to execute certain commands.
 * Read the code to know exactly what should be send and the corresponding action.
 */
void MOTI::serialRouter(){
	while(getRemoteState() == true){

		while(Serial.available() > 0){
			byte recievedByte = Serial.read();

			if(recievedByte == 104){
				remoteDisplayHelp();
			}
			else if(recievedByte == 114){
				Serial.println(F("Remote control is already activated"));
				setRemoteState(true);
			}
			else if(recievedByte == 100){
				Serial.println(F("Sending data as JSON"));
				checkSensors();
				sendDataJson();
			}
			else if(recievedByte == 76){
				Serial.println(F("Turn led on with rgb: "));
				setRemoteState(true);
			}
			else if(recievedByte == 102){
				Serial.println(F("Go forward"));
				setRemoteState(true);
			}
			else if(recievedByte == 70){
				Serial.println(F("Go forward at speed: "));
				setRemoteState(true);
			}
			else if(recievedByte == 98){
				Serial.println(F("Go backward"));
				setRemoteState(true);
			}
			else if(recievedByte == 66){
				Serial.println(F("Go backward at speed: "));
				setRemoteState(true);
			}
			else if(recievedByte == 113){
				Serial.println(F("Leaving the remote control mode."));
				setRemoteState(false);
			}
			else {
				Serial.println(F("Don't know how to do that, sorry..."));
			}
		}
	}
}