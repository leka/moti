#include <Arduino.h>
#include <Moti.h>

//##############################//
// REMOTE CONTROL FROM COMPUTER //
//##############################//


void Moti::readCommands(Motors& motors, Led& led, Sensors& sensors){
	while(Serial.available() > 0){

		uint8_t numberOfActions;

		// Read first byte of stream.
		uint8_t recievedByte = Serial.read();

		// If first byte is equal to dataHeader, start recording
		if(recievedByte == DATA_HEADER){
			delay(10);

			Serial.write(READY_TO_ANSWER);

			delay(200);

			// Get the number of actions to execute
			numberOfActions = Serial.read();

			// Execute each actions
			for (uint8_t i = 0 ; i < numberOfActions ; i++){
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

				if(actionType == 0x01 && actionType != DATA_FOOTER){
					motors.spinRightWheel(dataBuffer[0], dataBuffer[1]);
				}
				else if(actionType == 0x02 && actionType != DATA_FOOTER){
					motors.spinLeftWheel(dataBuffer[0], dataBuffer[1]);
				}
				else if(actionType == 0x03 && actionType != DATA_FOOTER){
					led.printRgb(dataBuffer[0], dataBuffer[1], dataBuffer[2]);
				}
				else if(actionType == 0x04 && actionType != DATA_FOOTER){
					sensors.checkSensors();
					sendBinaryData(sensors);
				}
			}
		}
	}
}

/**
 * @brief Check for serial commands from computer.
 *
 * Command are send as bytes and note as ASCII characters. Therefore, to activate the remote, you have to press "r" from the Arduino Serial Monitor or send a byte with the value "114" otherwise.
 */
void Moti::serialServer(){
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
void Moti::serialRouter(){
	while(getRemoteState() == true){

		while(Serial.available() > 0){
			byte recievedByte = Serial.read();

			if(recievedByte == 104){ ///< corresponds to the letter h in Arduino Serial Monitor
			}
			else if(recievedByte == 114){ ///< corresponds to the letter r in Arduino Serial Monitor
				Serial.println(F("Remote control is already activated"));
				setRemoteState(true);
			}
			else if(recievedByte == 100){ ///< corresponds to the letter d in Arduino Serial Monitor
				Serial.println(F("Sending data as JSON"));
				sensors.checkSensors();
				sendJson();
			}
			else if(recievedByte == 109){ ///< corresponds to the letter m in Arduino Serial Monitor
				Serial.println(F("Entering Machine Learning state"));
				setLearningState(true);
				while(getLearningState() == true){
					sensors.checkSensors();
					sendJson();
					delay(getLoopDelay());
					while(Serial.available() > 0){
						byte recievedByte = Serial.read();
						if(recievedByte == 77){ ///< corresponds to the letter h in Arduino Serial Monitor
							setLearningState(false);
						}
					}
				}
			}
			else if(recievedByte == 76){ ///< corresponds to the letter L in Arduino Serial Monitor
				Serial.println(F("Turn led on with rgb: "));
				setRemoteState(true);
			}
			else if(recievedByte == 102){ ///< corresponds to the letter f in Arduino Serial Monitor
				Serial.println(F("Go forward"));
				setRemoteState(true);
			}
			else if(recievedByte == 70){ ///< corresponds to the letter F in Arduino Serial Monitor
				Serial.println(F("Go forward at speed: "));
				setRemoteState(true);
			}
			else if(recievedByte == 98){ ///< corresponds to the letter b in Arduino Serial Monitor
				Serial.println(F("Go backward"));
				setRemoteState(true);
			}
			else if(recievedByte == 66){ ///< corresponds to the letter B in Arduino Serial Monitor
				Serial.println(F("Go backward at speed: "));
				setRemoteState(true);
			}
			else if(recievedByte == 113){ ///< corresponds to the letter q in Arduino Serial Monitor
				Serial.println(F("Leaving the remote control mode."));
				setRemoteState(false);
			}
			else {
				Serial.println(F("Don't know how to do that, sorry..."));
			}
		}
	}
}