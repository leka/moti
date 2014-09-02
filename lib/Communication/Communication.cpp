#include "Communication.h"

#define serial Serial1

namespace Communication {

/**
 * @brief Writes motors data to the serial
 */
void sendMotorsData(void) {
	serial.print(F("M,"));  /* M like Motors */
	serial.print(DriveSystem::getRightDirection());
	serial.print(F(","));
	serial.print(DriveSystem::getRightSpeed());
	serial.print(F(","));
	serial.print(DriveSystem::getLeftDirection());
	serial.print(F(","));
	serial.print(DriveSystem::getLeftSpeed());
}


/**
 * @brief Writes leds data to the serial
 */
void sendLedsData(void) {
	Color color = Light::getColor(HEART);

	serial.print(F("L,")); /* L like Leds */
	serial.print(Light::getState(HEART));
	serial.print(F(","));
	serial.print(color.getR());
	serial.print(F(","));
	serial.print(color.getG());
	serial.print(F(","));
	serial.print(color.getB());
}


/**
 * @brief Writes sensors data to the serial
 */
void sendSensorsData(void) {
	serial.print(F("S,"));
	serial.print(Sensors::getAccX());
	serial.print(F(","));
	serial.print(Sensors::getAccY());
	serial.print(F(","));
	serial.print(Sensors::getAccZ());
	serial.print(F(","));
	serial.print(Sensors::getGyrYDeg());
	serial.print(F(","));
	serial.print(Sensors::getGyrPDeg());
	serial.print(F(","));
	serial.print(Sensors::getGyrRDeg());
}


/**
 * @brief Writes motors, leds and sensors data to the serial
 */
void sendAllData(void) {
	serial.print(F("A,")); /* A like All */
	serial.print(millis());
	serial.print(F(";"));

	sendMotorsData();
	serial.print(F(";"));
	sendLedsData();
	serial.print(F(";"));
	sendSensorsData();
	serial.println(F(""));
	serial.flush();
}

}
