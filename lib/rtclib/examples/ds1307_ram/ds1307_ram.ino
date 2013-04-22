// RAM read and write functions using a DS1307 RTC connected via I2C and Wire lib.
// 2012-11-06 www.idreammicro.com http://opensource.org/licenses/mit-license.php

#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 RTC;

void setup () {
    Serial.begin(57600);
    Wire.begin();
    RTC.begin();
    
    // Write bytes in RAM.
    uint8_t data[13] = {
        'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!', '\n', 
    };
    RTC.writeBytesInRam(0x08, 13, data);
}

void loop () {
    // Read bytes in RAM.
    uint8_t data[13] = { 0 };
    RTC.readBytesInRam(0x08, 13, data);
    
    // Print bytes on Serial.
    Serial.write(data, 13);
    delay(5000);
}
