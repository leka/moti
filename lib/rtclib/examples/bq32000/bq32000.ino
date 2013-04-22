// Demonstrates the functionality of the TI BQ32000 RTC connected via I2C
// 2013-02-27 Alexander Hiam http://opensource.org/licenses/mit-license.php

#include <Wire.h>
#include <RTClib.h>


RTC_BQ32000 RTC;

void setup () {
    Serial.begin(57600);
    Wire.begin();
    RTC.begin();
    
    // following line sets the RTC to the date & time this sketch was compiled
    //RTC.adjust(DateTime(__DATE__, __TIME__));  
    
    // The BQ32000 can generate a square wave output on the IRQ pin, uncomment one of 
    // the following lines to use it:
    RTC.setIRQ(0); // IRQ square wave disabled
    //RTC.setIRQ(1); // 1Hz square wave on IRQ
    //RTC.setIRQ(2); // 512Hz square wave on IRQ

    // If the IRQ square wave output is disabled this method will set the IRQ pin's 
    // state to either HIGH or LOW:
    RTC.setIRQLevel(HIGH);

    RTC.setCalibration(0);
    // Set to a value in the range [-31,31] to adjust clock frequency
    // as needed. Refer to Table 13 in the BQ32000 datasheet from here:
    //  http://www.ti.com/product/bq32000
    
    // The BQ32000 includes a trickle charge circuit that can be enabled if using a 
    // super capacitor for backup power; uncomment one of the following lines if needed.
    RTC.setCharger(0); // Disabled
    //RTC.setCharger(1); // Charge voltage = VCC-0.5V
    //RTC.setCharger(2); // Charge voltage = VCC
    // *Make sure the charge circuit is disabled if using a battery for backup power!*
}

void loop () {
    DateTime now = RTC.now();
    
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
    Serial.print(" since 2000 = ");
    Serial.print(now.get());
    Serial.print("s = ");
    Serial.print(now.get() / 86400L);
    Serial.println("d");
    
    // calculate a date which is 7 days and 30 seconds into the future
    DateTime future (now.get() + 7 * 86400L + 30);
    
    Serial.print(" now + 7d + 30s: ");
    Serial.print(future.year(), DEC);
    Serial.print('/');
    Serial.print(future.month(), DEC);
    Serial.print('/');
    Serial.print(future.day(), DEC);
    Serial.print(' ');
    Serial.print(future.hour(), DEC);
    Serial.print(':');
    Serial.print(future.minute(), DEC);
    Serial.print(':');
    Serial.print(future.second(), DEC);
    Serial.println();
    
    Serial.println();
    delay(3000);
}