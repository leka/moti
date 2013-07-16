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

// Stream scheme:

// Action type -- number of data -- data(1) -- data(2) -- ... -- data(n)
//   1 byte    --      2 bytes   --  1 byte -- ...

// Right Motor -- 0x01 -- 2 data -- speed (1 byte) -- direction (1 byte)
// Left Motor  -- 0x02 -- 2 data -- speed (1 byte) -- direction (1 byte)
// Led         -- 0x03 -- 3 data -- red (1 byte)       -- green (1 byte) -- blue (1 byte)
// Sensors     -- 0x04 -- 0 data

uint8_t dataHeader = 0x0f;
uint8_t dataFooter = 0xf0;

void serverPi(){
	while(Serial.available() > 0){

		uint8_t numberActions;

		// Read first byte of stream.
		uint8_t recievedByte = Serial.read();

		// If first byte is equal to dataHeader, start recording
		if(recievedByte == dataHeader){

			digitalWrite(13, HIGH);
			delay(200);
			digitalWrite(13, LOW);
			delay(200);
			digitalWrite(13, HIGH);
			delay(200);
			digitalWrite(13, LOW);


			delay(200);

			// Get the number of actions to execute
			numberActions = Serial.read();

			// Execute each actions
			for (uint8_t i = 0 ; i < numberActions ; i++){
				uint8_t actionType;
				uint8_t numberData;
				uint8_t dataBuffer[10];

				// Get action type
				actionType = Serial.read();

				// Get number of data
				numberData = Serial.read();

				// For each data, store them in dataBuffer
				for(uint8_t j ; j < numberData ; j++){
					dataBuffer[j] = Serial.read();
					delay(10);
				}

				if(actionType == 0x01 && actionType != dataFooter){
					Moti.spinRightWheel(dataBuffer[0], dataBuffer[1]);
				}
				else if(actionType == 0x02 && actionType != dataFooter){
					Moti.spinLeftWheel(dataBuffer[0], dataBuffer[1]);
				}
				else if(actionType == 0x03 && actionType != dataFooter){
					Moti.printRgbColor(dataBuffer[0], dataBuffer[1], dataBuffer[2]);
				}
				else if(actionType == 0x04 && actionType != dataFooter){
					Moti.checkSensors();
				}
			}
		}
	}
}



//#######//
// SETUP //
//#######//

void setup() {
	Moti.initVerbose();
	pinMode(13, OUTPUT);
}

//######//
// LOOP //
//######//

void loop() {
	/**
	 * First, we check if any serial commands were sent to the robot. If so, we enter the remote control state and stop the standard execution of void loop().
	 */
	serverPi();

	/**
	 * Then, if there is no serial command to execute, the robot goes on and lives a happy life.
	 */

	delay(Moti.getLoopDelay());
}




