#include "Monitor.h"

#define serial Serial1

namespace Monitor {

    void sendMotorsData(void) {
        serial.println(F("M"));  /* M like Motors */
        serial.println(Drive::getRightDirection());
        
        serial.println(Drive::getRightSpeed());
        
        serial.println(Drive::getLeftDirection());
        
        serial.println(Drive::getLeftSpeed());
    }


    void sendLedsData(void) {
        Color color = Light::getColor(HEART);

        serial.println(F("L")); /* L like Leds */
        serial.println(Light::getState(HEART));
        
        serial.println(color.getR());
        
        serial.println(color.getG());
        
        serial.println(color.getB());
    }

    void sendSensorsData(void) {
        serial.println(F("S"));
        serial.println(Sensors::getAccX());
        
        serial.println(Sensors::getAccY());
        
        serial.println(Sensors::getAccZ());
        
        serial.println(Sensors::getGyrYDeg());
        
        serial.println(Sensors::getGyrPDeg());
        
        serial.println(Sensors::getGyrRDeg());
    }

    void sendAllData(void) {
        serial.println(F("A")); /* A like All */
        serial.println(millis());

        sendMotorsData();
        sendLedsData();
        sendSensorsData();
    }

}
