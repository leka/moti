#include "Monitor.h"

#define serial Serial1

namespace Monitor {

    void sendMotorsData(void) {
        serial.print(F("M,"));  /* M like Motors */
        serial.flush();
        serial.print(Drive::getRightDirection());
        serial.flush();
        serial.print(F(","));
        serial.flush();
        serial.print(Drive::getRightSpeed());
        serial.flush();
        serial.print(F(","));
        serial.flush();
        serial.print(Drive::getLeftDirection());
        serial.flush();
        serial.print(F(","));
        serial.flush();
        serial.println(Drive::getLeftSpeed());
        serial.flush();
    }


    void sendLedsData(void) {
        Color color = Light::getColor(HEART);

        serial.print(F("L,")); /* L like Leds */
        serial.flush();
        serial.print(Light::getState(HEART));
        serial.flush();
        serial.print(F(","));
        serial.flush();
        serial.print(color.getR());
        serial.flush();
        serial.print(F(","));
        serial.flush();
        serial.print(color.getG());
        serial.flush();
        serial.print(F(","));
        serial.flush();
        serial.println(color.getB());
        serial.flush();
    }

    void sendSensorsData(void) {
        serial.print(F("S,"));
        serial.flush();
        serial.print(Sensors::getAccX());
        serial.flush();
        serial.print(F(","));
        serial.flush();
        serial.print(Sensors::getAccY());
        serial.flush();
        serial.print(F(","));
        serial.flush();
        serial.print(Sensors::getAccZ());
        serial.flush();
        serial.print(F(","));
        serial.flush();
        serial.print(Sensors::getGyrYDeg());
        serial.flush();
        serial.print(F(","));
        serial.flush();
        serial.print(Sensors::getGyrPDeg());
        serial.flush();
        serial.print(F(","));
        serial.flush();
        serial.println(Sensors::getGyrRDeg());
        serial.flush();
    }

    void sendAllData(void) {
        serial.print(F("A,")); /* A like All */
        serial.flush();
        serial.println(millis());
        serial.flush();

        sendMotorsData();
        sendLedsData();
        sendSensorsData();
    }

}
