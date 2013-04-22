/*----------------------------------------------------------------------*
 * Example sketch for Arduino MCP79412 Library by Jack Christensen      *
 *                                                                      *
 * Sets the RTC date and time to a hard-coded value, using a            *
 * tmElements_t structure. The same structure is then used to           *
 * read the RTC once per second. This sketch only uses the Time         *
 * library for the tmElements_t definition.                             *
 *                                                                      *
 * This is just a simple demonstration of setting the RTC time.         *
 * Note that each time the sketch is run (or the microcontroller is     *
 * reset), the RTC will be set to the same hard-coded time, so this     *
 * example may be of limited usefulness as an actual clock.             *
 *                                                                      *
 * This work is licensed under the Creative Commons Attribution-        *
 * ShareAlike 3.0 Unported License. To view a copy of this license,     *
 * visit http://creativecommons.org/licenses/by-sa/3.0/ or send a       *
 * letter to Creative Commons, 171 Second Street, Suite 300,            *
 * San Francisco, California, 94105, USA.                               *
 *----------------------------------------------------------------------*/
 
#include <MCP79412RTC.h>    //http://github.com/JChristensen/MCP79412RTC
#include <Time.h>           //http://www.arduino.cc/playground/Code/Time  
#include <Wire.h>           //http://arduino.cc/en/Reference/Wire (included with Arduino IDE)

tmElements_t tm;

void setup(void)
{
    delay(2000);
    Serial.begin(9600);
    
    tm.Hour = 23;             //set the tm structure to 23h31m30s on 13Feb2009
    tm.Minute = 31;
    tm.Second = 30;
    tm.Year = 2009 - 1970;    //tmElements_t.Year is the offset from 1970.
    tm.Month = 2;
    tm.Day = 13;
    RTC.write(tm);            //set the RTC from the tm structure
}

void loop(void)
{
    RTC.read(tm);
    Serial.print(tm.Hour, DEC);
    Serial.print(':');
    Serial.print(tm.Minute,DEC);
    Serial.print(':');
    Serial.print(tm.Second,DEC);
    Serial.print(' ');
    Serial.print(tm.Year + 1970, DEC);
    Serial.print('-');
    Serial.print(tm.Month, DEC);
    Serial.print('-');
    Serial.print(tm.Day, DEC);
    Serial.println();
    delay(1000);
}

