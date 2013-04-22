ReadMe file for Arduino MCP79412 Library v1.0
https://github.com/JChristensen/MCP79412RTC
Jack Christensen Sep 2012

This work is licensed under the Creative Commons Attribution-ShareAlike 3.0
Unported License. To view a copy of this license, visit
http://creativecommons.org/licenses/by-sa/3.0/ or send a letter to Creative
Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.

================================================================================
Arduino library to support the Microchip MCP79412 Real-Time Clock. This library
is intended for use with the Arduino Time.h library,
http://www.arduino.cc/playground/Code/Time.

The MCP79412 library is a drop-in replacement for the DS1307RTC.h library by
Michael Margolis that is supplied with the Arduino Time library above. To change
from using a DS1307 RTC to an MCP79412 RTC, it is only necessary to change the
#include statement to include MCP79412RTC.h instead of DS1307RTC.h.

This library also implements functions to support the additional
features of the MCP79412.

--------------------------------------------------------------------------------
To use the library:
(1) Go to https://github.com/JChristensen/MCP79412RTC/downloads and download the
file in the compressed format of your choice (zip or tar.gz) to a convenient
location on your PC.
(2) Uncompress the downloaded file. This will result in a folder containing all
the files for the library, that has a name similar to "JChristensen-
MCP79412-42e98a7".
(3) Rename the folder to just "MCP79412".
(4) Copy the renamed folder to the Arduino sketchbook\libraries folder.

--------------------------------------------------------------------------------
The following example sketches are included with the Timezone library:

rtcSet1: Set the RTC date and time using a hard-coded value in the sketch.

rtcSet2: Similar to rtcSet1, a different way to hard-code the date and time.

rtcSet3: Set the RTC to the sketch compile date and time.

rtcSetSerial: Set the RTC via serial input from the Arduino monitor.

TimeRTC: Same as the example of the same name provided with the Time library,
demonstrating the interchangeability of the MCP79412RTC library with the
DS1307RTC library.

PowerOutageLogger: A comprehensive example that implements a power failure
logger using the MCP79412RTC's ability to capture power down and power up times.
Power failure events are logged to the MCP79412RTC's SRAM. Output is to the
Arduino serial monitor.

--------------------------------------------------------------------------------
Similar to the DS1307RTC library, the MCP79412 library instantiates an RTC
object; the user does not need to do this.

To use the MCP79412 library, the Time and Wire libraries must also be included.
For brevity, these includes are not repeated in the examples below:
#include <MCP79412RTC.h>          //http://github.com/JChristensen/MCP79412RTC
#include <Time.h>                 //http://www.arduino.cc/playground/Code/Time
#include <Wire.h>                 //http://arduino.cc/en/Reference/Wire
                                  //(Wire.h is included with Arduino IDE)

================================================================================
SETTING AND READING THE TIME

--------------------------------------------------------------------------------
The get() method reads the current time from the RTC and returns it as a time_t
value.

    time_t myTime;
    myTime = RTC.get();

--------------------------------------------------------------------------------
The set(time_t t) method sets the RTC to the given time_t value.
The example below first sets the system time (maintained by the Time library) to
a hard-coded date and time, then sets the RTC from the system time. The
setTime(hr, min, sec, day, month, year) function comes from the Time library.

    setTime(23, 31, 30, 13, 2, 2009);   //set the system time to
                                        //23h31m30s on 3Feb2009
    RTC.set(now());                     //set the RTC from the system time

--------------------------------------------------------------------------------
The read(tmElements_t &tm) method reads the current time from the RTC and
returns it as a tmElements_t structure.
(See the Arduino Time library for details on the tmElements_t structure:
http://www.arduino.cc/playground/Code/Time.)

    tmElements_t tm;
    RTC.read(tm);
    Serial.print(tm.Hour, DEC);
    Serial.print(':');
    Serial.print(tm.Minute,DEC);
    Serial.print(':');
    Serial.println(tm.Second,DEC);

--------------------------------------------------------------------------------
The write(tmElements_t &tm) method sets the RTC to the date and time
as represented in a tmElements_t structure.

    tmElements_t tm;
    tm.Hour = 23;             //set the tm structure to 23h31m30s on 13Feb2009
    tm.Minute = 31;
    tm.Minute = 30;
    tm.Day = 13;
    tm.Month = 2;
    tm.Year = 2009 - 1970;    //tmElements_t.Year is the offset from 1970.
    RTC.write(tm);            //set the RTC from the tm structure

--------------------------------------------------------------------------------
The isRunning() method returns a boolean value (true or false) indicating
whether the RTC's oscillator is running. When there is no backup battery
present, the RTC will reset when it is next powered up, and the oscillator will
not be running. Setting the time starts the oscillator.

    if ( RTC.isRunning() )
        //do something
    else
        //do something else

================================================================================
READING AND WRITING STATIC RAM (SRAM)

The MCP79412 RTC has 64 bytes of battery-backed SRAM that can be read and
written with the following methods using addresses between 0 and 63. Addresses
passed to these functions are constrained to the valid range by an AND function.

--------------------------------------------------------------------------------
sramWrite(byte addr, byte value) writes a single byte to the SRAM.

    RTC.sramWrite(3, 14);   //write the value 14 to SRAM address 3

--------------------------------------------------------------------------------
sramWrite(byte addr, byte *values, byte nBytes) writes multiple bytes to
consecutive SRAM locations. nBytes must be between 1 and 31. Invalid values of
nBytes, or combinations of addr and nBytes that would result in addressing past
the last byte of SRAM will result in no action.

    //write 1, 2, ..., 8 to the first eight SRAM locations
    byte buf[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    RTC.sramWrite(0, buf, 8);

--------------------------------------------------------------------------------
sramRead(byte addr) reads a single byte from SRAM and returns the value.

    byte val;
    val = RTC.sramRead(3);  //read the value from SRAM location 3

--------------------------------------------------------------------------------
sramRead(byte addr, byte *values, byte nBytes) reads multiple bytes from
consecutive SRAM locations. nBytes must be between 1 and 32. Invalid values of
nBytes, or combinations of addr and nBytes that would result in addressing past
the last byte of SRAM will result in no action.

    //read the last eight locations of SRAM into buf
    byte buf[8];
    RTC.sramRead(56, buf, 8);

================================================================================
READING AND WRITING EEPROM

The MCP79412 RTC has 128 bytes of non-volatile EEPROM that can be read and
written with the following methods using addresses between 0 and 127. Addresses
passed to these functions are constrained to the valid range by an AND function.

EEPROM is paged memory with a page size of 8 bytes; when writing multiple bytes,
this this limits the number of bytes that can be written to 8. Page writes must
start on a page boundary.

--------------------------------------------------------------------------------
eepromWrite(byte addr, byte value) writes a single byte to EEPROM.

    RTC.eepromWrite(42, 55);   //write the value 55 to EEPROM address 42

--------------------------------------------------------------------------------
eepromWrite(byte addr, byte *values, byte nBytes) writes a page (8 bytes) or
less to EEPROM. addr should be a page start address (0, 8, ..., 120), but
if not, is ruthlessly coerced into a valid value with an AND function. nBytes
must be between 1 and 8, other values result in no action.

    //write 1, 2, ..., 8 to the first eight EEPROM locations
    byte buf[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    RTC.eepromWrite(0, buf, 8);

--------------------------------------------------------------------------------
eepromRead(byte addr) reads a single byte from EEPROM and returns the value.

    byte val;
    val = RTC.eepromRead(42);  //read the value from EEPROM location 42

--------------------------------------------------------------------------------
eepromRead(byte addr, byte *values, byte nBytes) reads multiple bytes from
consecutive EEPROM locations. nBytes must be between 1 and 32. Invalid values of
nBytes, or combinations of addr and nBytes that would result in addressing past
the last byte of EEPROM will result in no action.

    //read the last eight locations of EEPROM into buf
    byte buf[8];
    RTC.eepromRead(120, buf, 8);

================================================================================
ALARM FUNCTIONS

The MCP79412 RTC has two alarms (Alarm-0 and Alarm-1) that can be used
separately or simultaneously. When an alarm is triggered, a flag is set in the
RTC that can be detected with the alarm() function below. Optionally, the RTC's
Multi-Function Pin (MFP) can be driven to either a low or high logic level when
an alarm is triggered. When using the MFP with both alarms, be sure to read the
comments on the alarmPolarity function below.

--------------------------------------------------------------------------------
setAlarm(uint8_t alarmNumber, time_t alarmTime) sets an alarm date and time.
This sets the alarm registers only, it does not enable the alarm, this is done
using the enableAlarm() function. alarmNumber is 0 or 1, but is ruthlessly
masked to ensure a valid value. Note that depending on the alarm type chosen
(see enableAlarm() below), only selected date or time parts may act as alarm
critera. Nevertheless, valid values should be specified in the alarmTime
parameter.

    //set alarm-1 for 30 seconds after midnight on 21Dec2012
    tmElements_t tm;
    tm.Hour = 0;
    tm.Minute = 0;
    tm.Second = 30;
    tm.Year = CalendarYrToTm(2012);
    tm.Month = 12;
    tm.Day = 21;
    RTC.setAlarm(ALARM_1, makeTime(tm));

--------------------------------------------------------------------------------
enableAlarm(uint8_t alarmNumber, uint8_t alarmType) enable or disable the given
alarm (0 or 1). alarmNumber is masked to ensure a value of 0 or 1. alarmType is
one of the following: ALM_MATCH_SECONDS, ALM_MATCH_MINUTES, ALM_MATCH_HOURS,
ALM_MATCH_DAY, ALM_MATCH_DATE, ALM_MATCH_DATETIME, ALM_DISABLE.

    //disable alarm-0
    RTC.enableAlarm(ALARM_0, ALM_DISABLE);

    //enable alarm-1 to trigger when the minutes match.
    //assuming alarm-1 is set as in the example above, this will trigger the
    //alarm every hour, on the hour (minutes=0).
    RTC.enableAlarm(ALARM_1, ALM_MATCH_MINUTES);

    //enable alarm-1 to trigger when the seconds match.
    //assuming alarm-1 is set as in the example above, this will trigger the
    //alarm once a minute, at 30 seconds past the minute.
    RTC.enableAlarm(ALARM_1, ALM_MATCH_SECONDS);

--------------------------------------------------------------------------------
alarm(uint8_t alarmNumber) tests whether the given alarm (0 or 1) has been
triggered, and returns a corresponding boolean value (true or false). Clears the
alarm flag to ensure that the next trigger event can be trapped.

    if ( RTC.alarm(ALARM_0) )
        //alarm-0 has triggered
    else
        //alarm-0 has not triggered

--------------------------------------------------------------------------------
alarmPolarity(boolean polarity) specifies the logic level on the Multi-Function
Pin (MFP) when an alarm is triggered. The default is LOW. When both alarms are
active, the two are ORed together to determine the level of the MFP. With alarm
polarity set to LOW (the default), this causes the MFP to go low only when BOTH
alarms are triggered. With alarm polarity set to HIGH, the MFP will go high when
EITHER alarm is triggered. Note that the state of the MFP is independent of the
alarm "interrupt" flags, and the alarm() function will indicate when an alarm is
triggered regardless of the polarity.

    RTC.alarmPolarity(HIGH);    //drives MFP high when an alarm is triggered

================================================================================
CALIBRATION, POWER FAILURE DETECTION, AND MISCELLANEOUS FUNCTIONS

--------------------------------------------------------------------------------
calibWrite(int value) writes the given value to the RTC calibration register.
This is an adjustment factor in PPM, and must be between -127 and 127. Negative
numbers cause the RTC to run faster, positive numbers cause it to run slower.

    RTC.calibWrite(13);     //makes the RTC run slower by 13 parts per million.
    RTC.calibWrite(-42);    //makes the RTC run faster by 42 parts per million.

--------------------------------------------------------------------------------
calibRead(void) returns the value of the RTC calibration register.

    int value;
    value = RTC.calibRead();

--------------------------------------------------------------------------------
powerFail(time_t *powerDown, time_t *powerUp) returns a boolean value (true or
false) to indicate whether a power failure has occurred. If one occurred, the
power down and power up timestamps are returned in the variables given by the
caller, the RTC's power fail flag is reset and the power up/down timestamps are
cleared.

Note that the power down and power up timestamp registers do not contain values
for seconds or for the year. The returned time stamps will therefore contain the
current year from the RTC. However, there is a chance that a power outage spans
from one year to the next. If this occurs, the power down timestamp would appear
to be at a later time than the power up timestamp; if this is encountered,
powerFail() will subtract one year from the power down timestamp before
returning it.

Still, there is an assumption that the timestamps are being read in the same
year as that when the power up occurred.

Finally, note that once the RTC records a power outage, it must be cleared
before another can be recorded. If two power outages occur before powerFail()
is called again, the time stamps for the earlier outage will be returned.

    time_t powerDown, powerUp;    //power outage timestamps
    if ( RTC.powerFail(&powerDown, &powerUp) ) {
        //do something
    else
        //do something else

--------------------------------------------------------------------------------
squareWave(uint8_t freq) enables or disables the square wave output on the
multi-function pin (MFP). freq is one of the following: SQWAVE_1_HZ,
SQWAVE_4096_HZ, SQWAVE_8192_HZ, SQWAVE_32768_HZ, SQWAVE_NONE

    RTC.squareWave(SQWAVE_1_HZ);    //output a 1Hz square wave on the MFP

--------------------------------------------------------------------------------
out(boolean level) sets the logic level on the MFP when it's not being used as a
square wave or alarm output. The default value after an RTC chip reset is HIGH.

    RTC.out(LOW);   //set the MFP to a low logic level

--------------------------------------------------------------------------------
idRead(byte *uniqueID) returns the 64-bit unique ID from the RTC into the given
8-byte array.

    byte buf[8];
    RTC.idRead(buf);

