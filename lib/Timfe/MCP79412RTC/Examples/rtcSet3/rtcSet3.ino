/*----------------------------------------------------------------------*
 * Example sketch for Arduino MCP79412 Library by Jack Christensen      *
 *                                                                      *
 * Sets the RTC date and time to the sketch compile time.               *
 * Re-running this sketch by pressing the reset button, etc., will      *
 * cause the RTC time to be reset to the *same* compile time.           *
 * Upload the sketch again to recompile it with the current time.       *
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
    
    setTime(compileTime());    //set the system time to the sketch compile time
    RTC.set(now());            //set the RTC from the system time
}

void loop(void)
{
    printTime(now());
    delay(1000);
}

//Function to return the compile date and time as a time_t value
time_t compileTime(void)
{
#define FUDGE 15        //fudge factor to allow for compile time (seconds, YMMV)

    char *compDate = __DATE__, *compTime = __TIME__, *months = "JanFebMarAprMayJunJulAugSepOctNovDec";
    char chMon[3], *m;
    int d, y;
    tmElements_t tm;
    time_t t;

    strncpy(chMon, compDate, 3);
    chMon[3] = '\0';
    m = strstr(months, chMon);
    tm.Month = ((m - months) / 3 + 1);

    tm.Day = atoi(compDate + 4);
    tm.Year = atoi(compDate + 7) - 1970;
    tm.Hour = atoi(compTime);
    tm.Minute = atoi(compTime + 3);
    tm.Second = atoi(compTime + 6);
    t = makeTime(tm);
    return t + FUDGE;        //add fudge factor to allow for compile time
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
