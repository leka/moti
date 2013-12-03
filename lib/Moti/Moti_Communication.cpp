#include <Arduino.h>
#include <Moti.h>

//###########################//
// DATA TRANSFER TO COMPUTER //
//###########################//

/**
 * @brief Send the value of a uint8_t as a 8 bits (1 byte) binary
 *
 * writeBinaryByte() sends values as 8 bits binaries. It uses Serial.write() and is used inside sendDataBinary().
 *
 * @param value the value you need to send.
 */
void Moti::writeBinaryByte(uint8_t value){
	serial.write(value);
}

/**
 * @brief Send the value of a int16_t as a 16 bits (2 bytes) binary
 *
 * writeBinaryInt() is used to send the two bytes that comprise a two byte (16 bit) integer.
 *
 * Serial.write(lowByte(value)) sends the low byte
 * Serial.write(highByte(value)) sends the high byte
 *
 * @param value [description]
 */
void Moti::writeBinaryInt(int value){
	serial.write(lowByte(value));
	serial.write(highByte(value));
}

/**
 * @brief send the sensors' values as binaries
 *
 * sendDataBinaries is used to send the accelerometer and gyroscope values to the compter/Raspberry-Pi as binaries and NOT as strings.
 * It uses writeBinaryByte(uint8_t value) and writeBinaryInt(int value) to Serial.write() the values.
 */
void Moti::sendBinaryData(Sensors& sensors){
	sensors.checkSensors();

	writeBinaryByte(START_ANSWER);

	writeBinaryByte(NUMBER_OF_SENSORS);

	writeBinaryByte(ACC_SENSOR);
	writeBinaryInt(ACC_DATA);

	writeBinaryInt(sensors.getXYZ(0));
	writeBinaryInt(sensors.getXYZ(1));
	writeBinaryInt(sensors.getXYZ(2));

	writeBinaryByte(GYR_SENSOR);
	writeBinaryInt(GYR_DATA);

	writeBinaryInt(sensors.getYPR(0));
	writeBinaryInt(sensors.getYPR(1));
	writeBinaryInt(sensors.getYPR(2));

	writeBinaryByte(END_ANSWER);
}

/**
 * @brief Send data formated as a JSON string
 *
 * sendJson() is used to interface the robot with other high level languages such as Processing or Javascript.
 * It can also be useful as a debug print out to check the consistency of the sensors.
 */
void Moti::sendJson(Sensors& sensors){

	Serial.print(F("{"));
		Serial.print(F("\"accel\":"));
			Serial.print(F("{"));

				Serial.print(F("\"x\":"));
				Serial.print(XYZ[0]);
				Serial.print(F(","));

				Serial.print(F("\"y\":"));
				Serial.print(XYZ[1]);
				Serial.print(F(","));

				Serial.print(F("\"z\":"));
				Serial.print(XYZ[2]);

			Serial.print(F("},"));

		Serial.print(F("\"gyro\":"));
			Serial.print(F("{"));

				Serial.print(F("\"yaw\":"));
				Serial.print(YPR[0]);
				Serial.print(F(","));

				Serial.print(F("\"pitch\":"));
				Serial.print(YPR[1]);
				Serial.print(F(","));

				Serial.print(F("\"roll\":"));
				Serial.print(YPR[2]);

			Serial.print(F("},"));

		Serial.print(F("\"rgb\":"));
			Serial.print(F("{"));

				Serial.print(F("\"red\":"));
				Serial.print(rgb[0]);
				Serial.print(F(","));

				Serial.print(F("\"green\":"));
				Serial.print(rgb[1]);
				Serial.print(F(","));

				Serial.print(F("\"blue\":"));
				Serial.print(rgb[2]);

			Serial.print(F("}"));
	Serial.println(F("}"));
}
