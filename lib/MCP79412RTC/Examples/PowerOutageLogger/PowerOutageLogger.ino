/*----------------------------------------------------------------------*
 * Power Outage Logger using Microchip MCP79412 RTC.                    *
 * Assumes the RTC is running and set to UTC.                           *
 * A maximum of 7 outages (power down/up times) can be logged in the    *
 * RTC's SRAM.                                                          *
 *                                                                      *
 * Jack Christensen 23Aug2012                                           *
 *                                                                      *
 * This work is licensed under the Creative Commons Attribution-        *
 * ShareAlike 3.0 Unported License. To view a copy of this license,     *
 * visit http://creativecommons.org/licenses/by-sa/3.0/ or send a       *
 * letter to Creative Commons, 171 Second Street, Suite 300,            *
 * San Francisco, California, 94105, USA.                               *
 *----------------------------------------------------------------------*/ 
 
#include <MCP79412RTC.h>          //http://github.com/JChristensen/MCP79412RTC
#include <Streaming.h>            //http://arduiniana.org/libraries/streaming/
#include <Time.h>                 //http://www.arduino.cc/playground/Code/Time  
#include <Timezone.h>             //http://github.com/JChristensen/Timezone
#include <Wire.h>                 //http://arduino.cc/en/Reference/Wire (included with Arduino IDE)

#define FIRST_OUTAGE_ADDR 0x08    //address of first outage timestamps in RTC SRAM
#define OUTAGE_LENGTH 8           //8 data bytes for each outage (start and end timestamps, both are time_t values)
#define MAX_OUTAGES 7             //maximum number of outage timestamp pairs that can be stored in SRAM
#define MAX_OUTAGE_ADDR FIRST_OUTAGE_ADDR + OUTAGE_LENGTH * (MAX_OUTAGES - 1)    //last outage address
#define APP_ID 1                  //APP_ID and 4 bytes of the RTC ID are stored in sram to provide
                                  //a way to recognize that the logging data structure has been initialized
#define RTC_ID_LO 0x00            //lower 4 bytes of RTC unique ID are stored at sram addr 0x00
#define APP_ID_ADDR 0x04          //address of appID (1)
#define NBR_OUTAGES_ADDR 0x05     //address containing number of outages currently stored in SRAM
#define NEXT_OUTAGE_ADDR 0x06     //address containing pointer to next outage
#define RFU_ADDR 0x07             //reserved for future use

//US Eastern Time Zone (New York, Detroit)
TimeChangeRule myDST = {"EDT", Second, Sun, Mar, 2, -240};    //Daylight time = UTC - 4 hours
TimeChangeRule mySTD = {"EST", First, Sun, Nov, 2, -300};     //Standard time = UTC - 5 hours
Timezone myTZ(myDST, mySTD);
TimeChangeRule *tcr;              //pointer to the time change rule, used to get TZ abbrev
time_t utc, local, lastUTC;

void setup()  {
    Serial.begin(115200);

    setSyncProvider(RTC.get);     //the function to get the time from the RTC
    Serial << "RTC SYNC";
    if (timeStatus()!= timeSet) Serial << " FAIL";
    Serial << endl;

    //logClear();
    logOutage();
}

void loop()
{
    //nothing here in loop() has anything to do with logging power outages,
    //we just print the time every second so that something is happening.
    utc = now();
    if (utc != lastUTC) {
        lastUTC = utc;
        local = myTZ.toLocal(utc, &tcr);
        Serial << endl;
        printTime(utc, "UTC");
        printTime(local, tcr -> abbrev);
    }
}

//initialize the log data structure in the RTC SRAM if needed.
//log a new outage if one occurred.
//print out the outages logged.
void logOutage(void)
{
    union {
        uint8_t b[8];
        struct {
            uint32_t hi;
            uint32_t lo;
        };
    } uniqueID;                   //8-byte RTC "unique ID" with access to upper and lower halves
    
    uint32_t loID;                //lower half of the unique ID read from sram
    uint8_t appID;                //app ID read from sram
    uint8_t nOutage;              //number of outages stored in sram
    uint8_t nextOutage;           //address of next outage timestamps in sram
    uint8_t outageAddr;           //outage address in sram
    time_t powerDown, powerUp;    //power outage timestamps
    
    RTC.idRead(uniqueID.b);       //get the RTC's ID
    loID = read32(RTC_ID_LO);     //if already initialized, the lower half of the ID is stored at SRAM addr 0x00,
    appID = RTC.sramRead(APP_ID_ADDR);     //and the app ID (1) is at addr 0x04.
    Serial << "RTC ID";
    for (uint8_t i=0; i<8; i++) {
        Serial << (uniqueID.b[i] < 16 ? " 0" : " ") << _HEX(uniqueID.b[i]);
    }
    
    if ( loID != uniqueID.lo || appID != 1 ) {              //logging initialized?
        write32(RTC_ID_LO, uniqueID.lo);                    //least significant half of the RTC unique ID
        RTC.sramWrite(APP_ID_ADDR, APP_ID);                 //app ID
        RTC.sramWrite(NBR_OUTAGES_ADDR, 0);                 //number of outages
        RTC.sramWrite(NEXT_OUTAGE_ADDR, FIRST_OUTAGE_ADDR); //next location for outage times
        RTC.sramWrite(RFU_ADDR, 0);                         //reserved for future use
        Serial << "Logging initialized" << endl;            //no, do it now
    }
    
    //if an outage has occurred, record it
    if ( RTC.powerFail(&powerDown, &powerUp) ) {
        nOutage = RTC.sramRead(NBR_OUTAGES_ADDR);
        nextOutage = RTC.sramRead(NEXT_OUTAGE_ADDR);
        write32(nextOutage, powerDown);
        write32(nextOutage + 4, powerUp);
        nextOutage += OUTAGE_LENGTH;
        if (nextOutage > MAX_OUTAGE_ADDR) nextOutage = FIRST_OUTAGE_ADDR;
        RTC.sramWrite(NEXT_OUTAGE_ADDR, nextOutage);
        if (nOutage < MAX_OUTAGES) RTC.sramWrite(NBR_OUTAGES_ADDR, ++nOutage);
    }
    
    //print out all the outages logged
    nOutage = RTC.sramRead(NBR_OUTAGES_ADDR);
    nextOutage = RTC.sramRead(NEXT_OUTAGE_ADDR);
    outageAddr = nextOutage - OUTAGE_LENGTH;
    if (outageAddr < FIRST_OUTAGE_ADDR) outageAddr = MAX_OUTAGE_ADDR;
    Serial << endl << endl << "Power outages logged: " << _DEC(nOutage) << endl;
    for (uint8_t i=nOutage; i>0; i--) {
        powerDown = read32(outageAddr);
        powerUp = read32(outageAddr + 4);
        Serial << endl << _DEC(i) << ": Power down ";
        printTime(myTZ.toLocal(powerDown, &tcr), tcr -> abbrev);
        Serial << _DEC(i) << ": Power up   ";
        printTime(myTZ.toLocal(powerUp, &tcr), tcr -> abbrev);
        outageAddr -= OUTAGE_LENGTH;
        if (outageAddr < FIRST_OUTAGE_ADDR) outageAddr = MAX_OUTAGE_ADDR;
    }
}

//destroy the logging data structure and log data
void logClear(void)
{
    for (uint8_t i=0; i<MAX_OUTAGE_ADDR + OUTAGE_LENGTH; i++) {
        RTC.sramWrite(i, 0);
    }
}

//write a time_t or other uint32_t value to sram starting at addr
void write32(uint8_t addr, uint32_t t)
{
    union {
        uint8_t b[4];
        uint32_t t;
    } i;

    i.t = t;
    RTC.sramWrite(addr, i.b, 4);
}

//read a time_t or other uint32_t value from sram starting at addr
time_t read32(uint8_t addr)
{
    union {
        uint8_t b[4];
        time_t t;
    } i;

    RTC.sramRead(addr, i.b, 4);
    return i.t;
}

//Print time with time zone
void printTime(time_t t, char *tz)
{
    sPrintI00(hour(t));
    sPrintDigits(minute(t));
    sPrintDigits(second(t));
    Serial << ' ' << dayShortStr(weekday(t)) << ' ';
    sPrintI00(day(t));
    Serial << ' ' << monthShortStr(month(t)) << ' ' << year(t) << ' ' << tz << endl;
}

//Print an integer in "00" format (with leading zero).
//Input value assumed to be between 0 and 99.
void sPrintI00(int val)
{
    if (val < 10) Serial << '0';
    Serial << val;
    return;
}

//Print an integer in ":00" format (with leading zero).
//Input value assumed to be between 0 and 99.
void sPrintDigits(int val)
{
    Serial << ':';
    if(val < 10) Serial << '0';
    Serial << val;
}
