#include "Monitor.h"

#define serial Serial1

namespace Monitor {

	void sendMotorsData(void) {
		serial.print(F("M,"));  /* M like Motors */
		serial.print(Drive::getRightDirection());
		serial.print(F(","));
		serial.print(Drive::getRightSpeed());
		serial.print(F(","));
		serial.print(Drive::getLeftDirection());
		serial.print(F(","));
		serial.print(Drive::getLeftSpeed());
	}


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
