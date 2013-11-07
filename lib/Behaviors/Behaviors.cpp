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
	sensors.init();
	delay(50);
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

	if (sensors.readXYZ(2) > 510 && getBehavior() == SHUT_DOWN) {
		setBehavior(CRUISE);
	}
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
			stopAndBlink();
			break;

		default:
			break;
	}
}

//-----------------------------------------------------//
// BEHAVIORS
//-----------------------------------------------------//

void Behaviors::cruise(){
	leftLed.turnOff();
	rightLed.turnOff();

	leftLed.blinkAsync(RED, 2, 500);
	rightLed.blinkAsync(GREEN, 5, 200);

	leftLed.turnOff();
	rightLed.turnOff();

	delay(1000);

	leftLed.writeRgb(BLUE);
	rightLed.writeRgb(GREEN);

	for (int i = 0 ; i < 4 ; i++) {
		motors.spinLeft();
		delay(200);
		motors.spinRight();
		delay(200);
	}

	delay(1000);

	motors.goForward();
	delay(1500);

	motors.stop();
	delay(500);

	motors.spinRight();
	delay(500);

	motors.stop();
	delay(500);

	motors.goForward();
	delay(1000);

	motors.stop();
	delay(500);

	motors.spinRight();
	delay(500);

	motors.stop();
	delay(500);

	motors.goForward();
	delay(1500);

	motors.stop();
	delay(500);

	for (int i = 0 ; i < 3 ; i++) {
		motors.spinLeft();
		delay(150);
		motors.spinRight();
		delay(150);
	}

	motors.stop();
	delay(500);

	setBehavior(SHUT_DOWN);
	orderNumber = 1;
}

void Behaviors::stabilize(){
	motors.stop();
	delay(500);
}

void Behaviors::escape(){
	leftLed.blinkAsync(RED, 10, 75);
	delay(500);
	leftLed.blinkAsync(RED, 4, 350);

	delay(1000);

	motors.goLeft(180);
	delay(1500);

	motors.stop();

	leftLed.blinkAsync(RAND, 5, 200);
	rightLed.blinkAsync(RAND, 10, 100);

	delay(200);

	leftLed.turnOff();
	rightLed.turnOff();

	delay(500);

	leftLed.writeRgb(RAND);
	rightLed.writeRgb(RAND);

	motors.spinRight();
	delay(1000);

	motors.stop();
	delay(500);

	motors.goRight();
	delay(1500);

	motors.stop();
	delay(500);

	motors.spinRight();
	delay(750);

	motors.stop();
	delay(500);

	setBehavior(SHUT_DOWN);
	orderNumber = 0;
}

void Behaviors::shutDown(){
	motors.stop();
	leftLed.blinkSync(RAND, 150);
	rightLed.blinkSync(RAND, 400);
}

void Behaviors::stopAndBlink(){
	motors.stop();
	leftLed.blinkSync(RAND, 300);
	rightLed.blinkSync(RAND, 700);
	setBehavior(CRUISE);
}


void Behaviors::remote(){
	serial.println("Serial");
	while(sio::avalaible()){

		uint8_t numberOfActions;

		// Read first byte of stream.
		uint8_t recievedByte = sio::readByte();

		// If first byte is equal to dataHeader, start recording
		if(recievedByte == sio::dataHeader){
			delay(10);

			sio::writeByte(sio::readyCheck);

			delay(10);

			// Get the number of actions to execute
			numberOfActions = sio::readByte();

			// Execute each actions
			for (uint8_t i = 0 ; i < numberOfActions ; i++){
				uint8_t actionType;
				uint8_t numberData;
				uint8_t dataBuffer[10];

				// Get action type
				actionType = sio::readByte();

				// Get number of data
				numberData = sio::readByte();

				// For each data, store them in dataBuffer
				for(uint8_t j ; j < numberData ; j++){
					dataBuffer[j] = sio::readByte();
					delay(10);
				}

				if(actionType == 0x01 && actionType != sio::dataFooter){
					motors.spinRightWheel(dataBuffer[0], dataBuffer[1]);
				}
				else if(actionType == 0x02 && actionType != sio::dataFooter){
					motors.spinLeftWheel(dataBuffer[0], dataBuffer[1]);
				}
				else if(actionType == 0x03 && actionType != sio::dataFooter){
					rightLed.writeRgb(dataBuffer[0], dataBuffer[1], dataBuffer[2]);
				}
				else if(actionType == 0x04 && actionType != sio::dataFooter){
					sensors.read();
					// sendBinaryData(sensors);
				}
			}
		}
	}
}




