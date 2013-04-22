/*----------------------------------------------------------------------*
 * MCP79412RTC.h - Arduino library for the Microchip MCP79412           *
 * Real-Time Clock. This library is intended for use with the Arduino   *
 * Time.h library, http://www.arduino.cc/playground/Code/Time           *
 *                                                                      *
 * This library is a drop-in replacement for the DS1307RTC.h library    *
 * by Michael Margolis that is supplied with the Arduino Time library   *
 * above. To change from using a DS1307 RTC to an MCP79412 RTC, it is   *
 * only necessary to change the #include statement to include this      *
 * library instead of DS1307RTC.h.                                      *
 *                                                                      *
 * In addition, this library implements functions to support the        *
 * additional features of the MCP79412.                                 *
 *                                                                      *
 * Jack Christensen 29Jul2012                                           *
 *                                                                      *
 * This work is licensed under the Creative Commons Attribution-        *
 * ShareAlike 3.0 Unported License. To view a copy of this license,     *
 * visit http://creativecommons.org/licenses/by-sa/3.0/ or send a       *
 * letter to Creative Commons, 171 Second Street, Suite 300,            *
 * San Francisco, California, 94105, USA.                               *
 *----------------------------------------------------------------------*/ 

#ifndef MCP79412RTC_h
#define MCP79412RTC_h
#include <Time.h>

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

//define release-independent I2C functions
#if ARDUINO >= 100
#define i2cRead Wire.read
#define i2cWrite Wire.write
#else
#define i2cRead Wire.receive
#define i2cWrite Wire.send
#endif

//MCP7941x I2C Addresses
#define RTC_ADDR 0x6F
#define EEPROM_ADDR 0x57

//MCP7941x Register Addresses
#define TIME_REG 0x00        //7 registers, Seconds, Minutes, Hours, DOW, Date, Month, Year
#define DAY_REG 0x03         //the RTC Day register contains the OSCON, VBAT, and VBATEN bits
#define YEAR_REG 0x06        //RTC year register   
#define CTRL_REG 0x07        //control register
#define CALIB_REG 0x08       //calibration register
#define UNLOCK_ID_REG 0x09   //unlock ID register
#define ALM0_REG 0x0A        //alarm 0, 6 registers, Seconds, Minutes, Hours, DOW, Date, Month
#define ALM1_REG 0x11        //alarm 1, 6 registers, Seconds, Minutes, Hours, DOW, Date, Month
#define ALM0_DAY 0x0D        //DOW register has alarm config/flag bits
#define PWRDWN_TS_REG 0x18   //power-down timestamp, 4 registers, Minutes, Hours, Date, Month
#define PWRUP_TS_REG 0x1C    //power-up timestamp, 4 registers, Minutes, Hours, Date, Month
#define TIMESTAMP_SIZE 8     //number of bytes in the two timestamp registers
#define SRAM_START_ADDR 0x20 //first SRAM address
#define SRAM_SIZE 64         //number of bytes of SRAM
#define EEPROM_SIZE 128      //number of bytes of EEPROM
#define EEPROM_PAGE_SIZE 8   //number of bytes on an EEPROM page
#define UNIQUE_ID_ADDR 0xF0  //starting address for unique ID
#define UNIQUE_ID_SIZE 8     //number of bytes in unique ID

//Control Register bits
#define OUT 7       //sets logic level on MFP when not used as square wave output
#define SQWE 6      //set to enable square wave output
#define ALM1 5      //alarm 1 is active
#define ALM0 4      //alarm 0 is active
#define EXTOSC 3    //set to drive the RTC registers from an external oscillator instead of a crystal
#define RS2 2       //RS2:0 set square wave output frequency: 0==1Hz, 1==4096Hz, 2==8192Hz, 3=32768Hz
#define RS1 1
#define RS0 0
enum {SQWAVE_1_HZ, SQWAVE_4096_HZ, SQWAVE_8192_HZ, SQWAVE_32768_HZ, SQWAVE_NONE};

//Other Control Bits
#define ST 7        //Seconds register (TIME_REG) oscillator start/stop bit, 1==Start, 0==Stop
#define HR1224 6    //Hours register (TIME_REG+2) 12 or 24 hour mode (24 hour mode==0)
#define AMPM 5      //Hours register (TIME_REG+2) AM/PM bit for 12 hour mode 
#define OSCON 5     //Day register (TIME_REG+3) oscillator running (set and cleared by hardware)
#define VBAT 4      //Day register (TIME_REG+3) set by hardware when Vcc fails and RTC runs on battery.
                    //VBAT is cleared by software, clearing VBAT also clears the timestamp registers
#define VBATEN 3    //Day register (TIME_REG+3) VBATEN==1 enables backup battery, VBATEN==0 disconnects the VBAT pin (e.g. to save battery)
#define LP 5        //Month register (TIME_REG+5) leap year bit

//Alarm Control Bits
#define ALMPOL 7    //Alarm Polarity: Defines the logic level for the MFP when an alarm is triggered.
#define ALMC2 6     //Alarm configuration bits determine how alarms match. See ALM_MATCH defines below.
#define ALMC1 5
#define ALMC0 4
#define ALMIF 3     //Alarm Interrupt Flag: Set by hardware when an alarm was triggered, cleared by software.
enum {ALM_MATCH_SECONDS, ALM_MATCH_MINUTES, ALM_MATCH_HOURS, ALM_MATCH_DAY, ALM_MATCH_DATE, ALM_RESERVED_5, ALM_RESERVED_6, ALM_MATCH_DATETIME, ALM_DISABLE};
//Note ALM_MATCH_DAY triggers alarm at midnight
#define ALARM_0 0   //constants for calling functions
#define ALARM_1 1

class MCP79412RTC
{
    public:
        MCP79412RTC();
        static time_t get(void);
        static void set(time_t t);
        static void read(tmElements_t &tm);
        static void write(tmElements_t &tm);
        void sramWrite(byte addr, byte value);
        void sramWrite(byte addr, byte *values, byte nBytes);
        byte sramRead(byte addr);
        void sramRead(byte addr, byte *values, byte nBytes);
        void eepromWrite(byte addr, byte value);
        void eepromWrite(byte addr, byte *values, byte nBytes);
        byte eepromRead(byte addr);
        void eepromRead(byte addr, byte *values, byte nBytes);
        int calibRead(void);
        void calibWrite(int value);
        void idRead(byte *uniqueID);
        boolean powerFail(time_t *powerDown, time_t *powerUp);
        void squareWave(uint8_t freq);
        void setAlarm(uint8_t alarmNumber, time_t alarmTime);
        void enableAlarm(uint8_t alarmNumber, uint8_t alarmType);
        boolean alarm(uint8_t alarmNumber);
        void out(boolean level);
        void alarmPolarity(boolean polarity);
        boolean isRunning(void);

    private:
        static void ramWrite(byte addr, byte value);
        static void ramWrite(byte addr, byte *values, byte nBytes);
        static byte ramRead(byte addr);
        static void ramRead(byte addr, byte *values, byte nBytes);
        static byte eepromWait(void);
        static uint8_t dec2bcd(uint8_t num);
        static uint8_t bcd2dec(uint8_t num);
};

extern MCP79412RTC RTC;

#endif

