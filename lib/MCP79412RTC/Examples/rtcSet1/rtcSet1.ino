/*----------------------------------------------------------------------*
 * Example sketch for Arduino MCP79412 Library by Jack Christensen      *
 *                                                                      *
 * Sets the RTC date and time to a hard-coded value.                    *
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

void setup(void)
{
    delay(2000);
    Serial.begin(9600);
    
    setTime(23, 31, 30, 13, 2, 2009);   //set the system time to 23h31m30s on 13Feb2009
                                        //the setTime() function is from the Time.h library.
                                        //setTime(hour, minute, second, day, month, year);
    RTC.set(now());                     //set the RTC from the system time 
}

void loop(void)
{
    printTime(now());
    delay(1000);
}

//Print time (and date) given a time_t value
void printTime(time_t t)
{
    printI00(hour(t), ':');
    printI00(minute(t), ':');
    printI00(second(t), ' ');
    Serial.print(dayShortStr(weekday(t)));
    Serial.print(' ');
    printI00(day(t), ' ');
    Serial.print(monthShortStr(month(t)));
    Serial.print(' ');
    Serial.println(year(t));
}

//Print an integer in "00" format (with leading zero),
//followed by a delimiter.
//Input value assumed to be between 0 and 99.
void printI00(int val, char delim)
{
    if (val < 10) Serial.print('0');
    Serial.print(val);
    Serial.print(delim);
    return;
}
