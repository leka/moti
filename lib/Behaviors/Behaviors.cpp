#include <Arduino.h>
#include <Behaviors.h>


/**
 * @file Behaviors.cpp
 * @author Ladislas de Toldi
 * @version 1.0
 */

//-----------------------------------------------------//
// GENERAL
//-----------------------------------------------------//

/**
 * @brief Behaviors Class Constructor
 */
Behaviors::Behaviors(){
	behavior = SHUT_DOWN;
}

/**
 * @brief set the current behavior
 */
void Behaviors::setBehavior(uint8_t _behavior){
	behavior = _behavior;
}

/**
 * @brief get the current behavior
 */
uint8_t Behaviors::getBehavior(){
	return behavior;
}

/**
 * @brief Router method, checks which behavior should be called
 */
void Behaviors::router(){
	sensors.read();

	if (sensors.readXYZ(2) > getWakeUpThreshold()) {
		setBehavior(CRUISE);
	}
	if (sensors.readXYZ(0) > getBumpThreshold();) {
		setBehavior(ESCAPE);
	}
	if (timer() % 50 == 0) {
		setBehavior(SPINBLINK);
	}
	if (sensors.readXYZ(2) > getPickUpThreshold()) {
		setBehavior(STABILIZE);
	}
	if (timer() > getTimeToSleep()) {
		setBehavior(SHUT_DOWN);	
	}
	else {
		setBehavior(CRUISE);
	}
}

/*
 * @brief Server method, serves the behavior
 */
void Behaviors::server(){
	switch (getBehavior()) {
		case CRUISE:
			cruise();
			break;

		case ESCAPE:
			escape();
			break;

		case STABILIZE:
			stabilize();
			break;

		case SHUT_DOWN:
			shutDown();
			break;

		case SPINBLINK:
			stopAndBling();
			break;

		default:
			break;
	}
}

//-----------------------------------------------------//
// BEHAVIORS
//-----------------------------------------------------//



void Behaviors::remote(){
	while(SerialCom::avalaible()){

		uint8_t numberOfActions;

		// Read first byte of stream.
		uint8_t recievedByte = SerialCom::readByte();

		// If first byte is equal to dataHeader, start recording
		if(recievedByte == SerialCom::dataHeader){
			delay(10);

			SerialCom::writeByte(SerialCom::readyCheck);

			delay(10);

			// Get the number of actions to execute
			numberOfActions = SerialCom::readByte();

			// Execute each actions
			for (uint8_t i = 0 ; i < numberOfActions ; i++){
				uint8_t actionType;
				uint8_t numberData;
				uint8_t dataBuffer[10];

				// Get action type
				actionType = SerialCom::readByte();

				// Get number of data
				numberData = SerialCom::readByte();

				// For each data, store them in dataBuffer
				for(uint8_t j ; j < numberData ; j++){
					dataBuffer[j] = SerialCom::readByte();
					delay(10);
				}

				if(actionType == 0x01 && actionType != SerialCom::dataFooter){
					motors.spinRightWheel(dataBuffer[0], dataBuffer[1]);
				}
				else if(actionType == 0x02 && actionType != SerialCom::dataFooter){
					motors.spinLeftWheel(dataBuffer[0], dataBuffer[1]);
				}
				else if(actionType == 0x03 && actionType != SerialCom::dataFooter){
					rightLed.writeRgb(dataBuffer[0], dataBuffer[1], dataBuffer[2]);
				}
				else if(actionType == 0x04 && actionType != SerialCom::dataFooter){
					sensors.read();
					// sendBinaryData(sensors);
				}
			}
		}
	}
}




