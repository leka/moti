#include "Behaviors.hpp"

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
	delay(50);
	rightLed.open();
	delay(50);
	leftLed.open();
	delay(50);
	setBehavior(WAKE_UP);
	reactNumber = 0;
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

	if (sensors.readXYZ(2) > 510 && getBehavior() == WAIT) {
		setBehavior(CRUISE);
	}

	if (sensors.readXYZ(0) > 250 && getBehavior() == WAIT) {
		setBehavior(REACT);
	}

	if (sensors.readXYZ(2) > 510 && getBehavior() == SHUT_DOWN) {
		setBehavior(WAKE_UP);
	}
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
			Serial.println("Cruise");
			cruise();
			break;

		case WAIT:
			Serial.println("Wait");
			wait();
			break;

		case WAKE_UP:
			Serial.println("Wake Up");
			wakeup();
			break;

		case REACT:
			Serial.println("React");
			react();
			break;

		case ESCAPE:
			Serial.println("Escape");
			escape();
			break;

		case STABILIZE:
			stabilize();
			break;

		case SHUT_DOWN:
			Serial.println("Shut Down");
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
	uint8_t speed = 90;
	uint8_t i = 0;

	delay(1000);

	while (i < 255) {
		leftLed.blinkSync(RAND, 76);
		rightLed.blinkSync(RAND, 148);
		i++;
		delay(20);
	}

	motors.goForward(speed);
	delay(2500);
	motors.goRight(speed);
	delay(1500);
	motors.goForward(speed);
	delay(2000);
	motors.goRight(speed);
	delay(3000);

	motors.stop();
	setBehavior(WAIT);
}

void Behaviors::wait(){
	//motors.spinLeft(150);
	motors.stop();
	leftLed.blinkSync(RAND, 400);
	rightLed.blinkSync(RAND, 600);
}

void Behaviors::react(){
	uint16_t stopDelay;
	uint16_t spinDelay;
	uint8_t speed = 90;

	if (reactNumber == 0) {
		spinDelay = 250;
		stopDelay = 100;

		motors.spinLeft(speed);
		delay(spinDelay);

		motors.stop();
		delay(stopDelay);

		motors.spinRight(speed);
		delay(spinDelay * 2);

		motors.stop();
		delay(stopDelay);

		motors.spinLeft(speed);
		delay(spinDelay * 2);

		motors.stop();
		delay(stopDelay);

		motors.spinRight(speed);
		delay(spinDelay);

		motors.stop();

		reactNumber++;
		setBehavior(WAIT);
		delay(3000);
	}

	else if (reactNumber == 1) {
		spinDelay = 250;
		stopDelay = 250;

		motors.goForward(speed);
		delay(150);
		motors.stop();
		delay(200);

		motors.goForward(speed);
		delay(300);
		motors.stop();
		motors.goBackward(speed);
		delay(100);
		motors.stop();
		delay(200);

		motors.spinLeft(speed);
		delay(spinDelay);

		motors.stop();
		delay(stopDelay);

		motors.spinRight(speed);
		delay(spinDelay * 2);

		motors.stop();
		delay(stopDelay);

		motors.spinLeft(speed);
		delay(spinDelay * 2);

		motors.stop();
		delay(stopDelay);

		motors.spinRight(speed);
		delay(spinDelay);

		motors.stop();

		reactNumber = 0;
		setBehavior(ESCAPE);
		delay(3000);
	}


}


void Behaviors::wakeup(){
	uint8_t speed = 90;

	for (uint8_t i = 0 ; i < 255 ; i++){
		leftLed.writeRgb(i, i*i, i*i*i);
		rightLed.writeRgb(i, i*i, i*i*i);
		delay(20);
	}

	delay(2000);

	uint8_t i = 0;

	// for (int i = 0 ; i < 2 ; i++) {
	// 	motors.spinLeft(speed);
	// 	delay(1000);
	// 	motors.spinRight(speed);
	// 	delay(1000);
	// }

	motors.goForward(speed);
	delay(1500);
	motors.stop();

	i = 0;

	while (i < 255) {
		leftLed.blinkSync(RAND, 76);
		rightLed.blinkSync(RAND, 148);
		i++;
		delay(10);
	}

	delay(1000);
	setBehavior(WAIT);
}


void Behaviors::stabilize(){
	motors.stop();
	delay(500);
}

void Behaviors::escape(){
	uint8_t speed = 90;

	leftLed.writeRgb(BLUE);
	rightLed.writeRgb(BLUE);

	delay(1000);

	motors.goBackward(speed);
	delay(2000);

	motors.stop();
	delay(1000);

	motors.spinLeft(speed);
	delay(500);

	motors.stop();
	delay(1000);

	leftLed.writeRgb(RAND);
	rightLed.writeRgb(RAND);

	motors.goForward(speed);
	delay(2000);

	motors.goRight(speed);
	delay(1000);

	motors.goForward(speed);
	delay(2000);

	motors.stop();
	delay(500);

	setBehavior(SHUT_DOWN);
}

void Behaviors::shutDown(){
	motors.stop();
	leftLed.turnOff();
	rightLed.turnOff();
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




