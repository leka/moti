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
}

void Behaviors::init(){
	delay(500);
	serial.begin(115200);
	delay(50);
	motors.init();
	delay(50);
	sensors.open();
	delay(50);
	sensors.open();
	motors.init();
	rightLed.open();
	leftLed.open();
	setBehavior(SHUT_DOWN);
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


	// TO BE MODIFIED
	// if (sensors.readXYZ(2) > 500) {
	// 	setBehavior(CRUISE);
	// }
	// if (sensors.readXYZ(0) < -30) {
	// 	setBehavior(ESCAPE);
	// }
	// if (millis() % 10000 == 0) {
	// 	setBehavior(SPINBLINK);
	// }
	// if (sensors.readXYZ(2) > 320) {
	// 	setBehavior(STABILIZE);
	// }
	// if (millis() > 50000) {
	// 	setBehavior(SHUT_DOWN);	
	// }
	// if (serial.available() > 0) {
	// 	setBehavior(REMOTE);	
	// }
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

void Behaviors::cruise(){
	serial.println("Cruising");
	motors.goForward();
}

void Behaviors::stabilize(){
	serial.println("Stabilizing");
	motors.stop();
	delay(500);
}

void Behaviors::escape(){
	motors.stop();
	delay(1000);
	motors.goBackward();
	delay(1000);
	motors.stop();
	delay(1000);
	motors.spinLeft();
	delay(500);
	setBehavior(CRUISE);
}

void Behaviors::shutDown(){
	motors.stop();
}

void Behaviors::stopAndBling(){
	motors.stop();
	leftLed.blinkSync(RAND, 300);
	rightLed.blinkSync(RAND, 700);
	setBehavior(CRUISE);
}


void Behaviors::remote(){
	serial.println("Serial");
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




