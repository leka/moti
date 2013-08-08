#include <Arduino.h>
#include <Moti.h>

//###########################//
// DATA TRANSFER TO COMPUTER //
//###########################//

/**
 * @brief Send the value of a uint8_t as a 8 bits (1 byte) binary
 *
 * sendBinaryByte() sends values as 8 bits binaries. It uses Serial.write() and is used inside sendDataBinary().
 *
 * @param value the value you need to send.
 */
void Moti::sendBinaryByte(uint8_t value){
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
void Moti::sendBinaryInt(int value){
	Serial.write(lowByte(value));
	Serial.write(highByte(value));
}

/**
 * @brief send the sensors' values as binaries
 *
 * sendDataBinaries is used to send the accelerometer and gyroscope values to the compter/Raspberry-Pi as binaries and NOT as strings.
 * It uses sendBinaryByte(uint8_t value) and sendBinaryInt(int value) to Serial.write() the values.
 */
void Moti::sendDataBinaries(){
	sensors.checkSensors();

	sendBinaryByte(START_ANSWER);

	sendBinaryByte(NUMBER_OF_SENSORS);

	sendBinaryByte(ACC_SENSOR);
	sendBinaryInt(ACC_DATA);

	sendBinaryInt(sensors.getXYZ(0));
	sendBinaryInt(sensors.getXYZ(1));
	sendBinaryInt(sensors.getXYZ(2));

	sendBinaryByte(GYR_SENSOR);
	sendBinaryInt(GYR_DATA);

	sendBinaryInt(sensors.getYPR(0));
	sendBinaryInt(sensors.getYPR(1));
	sendBinaryInt(sensors.getYPR(2));

	sendBinaryByte(END_ANSWER);
}

/**
 * @brief Send data formated as a JSON string
 *
 * sendJson() is used to interface the robot with other high level languages such as Processing or Javascript.
 * It can also be useful as a debug print out to check the consistency of the sensors.
 */
void Moti::sendJson(){
	String json;

	json = "{\"accel\":{\"x\":";
	json = json + sensors.getXYZ(0);
	json = json + ",\"y\":";
	json = json + sensors.getXYZ(1);
	json = json + ",\"z\":";
	json = json + sensors.getXYZ(2);
	json = json + "},\"gyro\":{\"yaw\":";
	json = json + sensors.getYPR(0);
	json = json + ",\"pitch\":";
	json = json + sensors.getYPR(1);
	json = json + ",\"roll\":";
	json = json + sensors.getYPR(2);
	json = json + "}}";

	Serial.println(json);
}
