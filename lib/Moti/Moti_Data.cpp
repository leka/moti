#include "Moti.h"
#include "Arduino.h"

//###########################//
// DATA TRANSFER TO COMPUTER //
//###########################//

/**
 * @brief Send sensors data formated for machine learning
 *
 * sendDataLearning() is used to stream data separated with a "space" so that they can be saved and imported directly in Excel as .csv for analysis.
 */
void MOTI::sendDataLearning(){

	Serial.print(XYZ[0]);
	Serial.print(F(" "));

	Serial.print(XYZ[1]);
	Serial.print(F(" "));

	Serial.print(XYZ[2]);
	Serial.print(F(" "));

	Serial.print(YPR[0]);
	Serial.print(F(" "));

	Serial.print(YPR[1]);
	Serial.print(F(" "));

	Serial.println(YPR[2]);
}

/**
 * @brief send the sensors' values as binaries
 *
 * sendDataBinaries is used to send the accelerometer and gyroscope values to the compter/Raspberry-Pi as binaries and NOT as strings.
 * It uses sendBinaryByte(uint8_t value) and sendBinaryInt(int value) to Serial.write() the values.
 */
void MOTI::sendDataBinaries(){
	checkSensors();

	sendBinaryByte(START_ANSWER);

	sendBinaryByte(NUMBER_OF_SENSORS);

	sendBinaryByte(ACC_SENSOR);
	sendBinaryInt(ACC_DATA);

	sendBinaryInt(getXYZ(0));
	sendBinaryInt(getXYZ(1));
	sendBinaryInt(getXYZ(2));

	sendBinaryByte(GYR_SENSOR);
	sendBinaryInt(GYR_DATA);

	sendBinaryInt(getYPR(0));
	sendBinaryInt(getYPR(1));
	sendBinaryInt(getYPR(2));

	sendBinaryByte(END_ANSWER);
}

/**
 * @brief Send the value of a uint8_t as a 8 bits (1 byte) binary
 *
 * sendBinaryByte() sends values as 8 bits binaries. It uses Serial.write() and is used inside sendDataBinary().
 *
 * @param value the value you need to send.
 */
void MOTI::sendBinaryByte(uint8_t value){
	Serial.write(value);
}

/**
 * @brief Send the value of a int16_t as a 16 bits (2 bytes) binary
 *
 * sendBinaryInt() is used to send the two bytes that comprise a two byte (16 bit) integer.
 *
 * Serial.write(lowByte(value)) sends the low byte
 * Serial.write(highByte(value)) sends the high byte
 *
 * @param value [description]
 */
void MOTI::sendBinaryInt(int value){
	Serial.println(lowByte(value));
	Serial.println(highByte(value));
}

/**
 * @brief Send data formated as a JSON string
 *
 * sendDataJson() is used to interface the robot with other high level languages such as Processing or Javascript.
 * It can also be useful as a debug print out to check the consistency of the sensors.
 */
void MOTI::sendDataJson(){
	Serial.print(F("{"));
		Serial.print(F("\" accel\": "));
			Serial.print(F("{"));

				Serial.print(F(" \"x\": "));
				Serial.print(XYZ[0]);
				Serial.print(F(","));

				Serial.print(F(" \"y\": "));
				Serial.print(XYZ[1]);
				Serial.print(F(","));

				Serial.print(F(" \"z\": "));
				Serial.print(XYZ[2]);

			Serial.print(F(" },"));

		Serial.print(F("\" gyro\": "));
			Serial.print(F("{"));

				Serial.print(F(" \"yaw\": "));
				Serial.print(YPR[0]);
				Serial.print(F(","));

				Serial.print(F(" \"pitch\": "));
				Serial.print(YPR[1]);
				Serial.print(F(","));

				Serial.print(F(" \"roll\": "));
				Serial.print(YPR[2]);

			Serial.print(F(" },"));

		Serial.print(F("\" rgb\": "));
			Serial.print(F("{"));

				Serial.print(F(" \"red\": "));
				Serial.print(rgb[0]);
				Serial.print(F(","));

				Serial.print(F(" \"green\": "));
				Serial.print(rgb[1]);
				Serial.print(F(","));

				Serial.print(F(" \"blue\": "));
				Serial.print(rgb[2]);

			Serial.print(F(" }"));
	Serial.println(F("}"));
}
