/**************************************************************
 * ARDUINO_OSC 0005
 *
 * Firmware to send OSC messages from an Arduino board to a PC
 * and to receive OSC messages sent from the PC.
 *
 * Right now, only messages with a single integer argument
 * are supported in either direction.
 *
 * Uses the following serial OSC format:
 * 0xBE MSG_LENGTH OSC_MESSAGE CHECKSUM
 * ---- ---------- ---/.../--  --------
 * 1b   1byte      4*n bytes   1byte
 *
 * PROTOCOL DETAILS
 * Digital pins 2..12 and analog inputs 0..5 are supported.
 * PWM output on PWM-capable digital pins is supported as well.
 * Below, the notation [2..12] means: any number from 2 to 12.
 * The notation [0|1] means: either 0 or 1.
 * Pin numbers are always part of the OSC address. 
 * The single integer argument for each OSC message
 * represents either HIGH/LOW, or an 8bit analog value.
 *
 * PC->ARDUINO MESSAGE FORMAT
 * /pinmode/[2..12]  [0|1] - set a pin to input or output mode
 *
 * /report/adc [0|1]    - turn all analog pin reporting on/off (Default: off)
 * /report/adc/[0..5] [0|1]  - set analog pin reporting for one pin on/off
 * /report/in [0|1]     - turn digital pin reporting on/off (default: on)
 *
 * /out/5 [0|1]         - set a digital pin to [low|high]
 * /pwm/10 [0..255]     - set duty on a pwm-enabled pin 
 * 
 * ARDUINO->PC PROTOCOL 
 * /in/[2..12] [0|1]    - a digital input pin changed to [high|low]
 * /adc/[0..5] [0..255] - analog input value changed to [0..255]
 * NOTE: input pins use pull-up resistors and are HIGH by default.
 * Therefore, 0 means HIGH, 1 means LOW (pulled to ground). 
 * Output pins are low by default.
 *
 * EXAMPLES: PC->ARDUINO 
 * /pinmode/5 0         - set pin 5 to INPUT
 * /pinmode/9 1         - set pin 9 to OUTPUT
 * /out/9 0             - set pin 9 to LOW
 * /out/12 1            - set pin 12 to HIGH
 * /pwm/10 255          - set PWM duty on pin 10 to 255 (100%)
 * /report/in 1         - turn digital input pin reporting on
 * /report/adc/4 0      - turn reporting of analog input 4 off
 *
 * EXAMPLES: ARDUINO->PC
 * /in/4 1              - digital input pin 4 pulled to ground
 * /adc/2 128           - analog input pin2 read 128 (=2.5V)
 * 
 * DEFAULT STARTUP CONFIGURATION
 *   - Pins 2-12 are all set to input, digital reporting enabled
 *     (change variable reportDigital to False to disable by default)
 *   - Analog reporting is disabled 
 *     (change variable reportAnalog to 0xFF to enable by default)
 *
 * NOTES:
 *   - Pins 0,1,13 cannot be used
 *   - Resolution on analog in and out is 8 bit.
 *   - Not all pins can be used for /pwm output. see arduino documentation
 *   - So far, not much error checking for bounds done
 *   - 115200 serial rate results in some read errors on Arduino.
 *     38400 is recommended.
 * 
 * MIT License:
 * Copyright (c) 2008 Bjoern Hartmann, Stanford HCI Group
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * bjoern@cs.stanford.edu 12/02/2008
 **************************************************************/

#define VERSION 5

#define MIN_A2D_DIFF 4  // threshold for reporting a2d changes
#define MAX_LENGTH 24   // size of buffer for building OSC msgs
#define SERIAL_SPEED 38400

#define FIRST_DIGITAL_PIN 2
#define LAST_DIGITAL_PIN 12
#define NUM_DIGITAL_PINS 11

#define FIRST_ANALOG_PIN 0
#define LAST_ANALOG_PIN 5
#define NUM_ANALOG_PINS 6


// define state constants for parsing FSM
#define OSC_RXOP_WAITFORSTART 0
#define OSC_RXOP_READSIZE 1
#define OSC_RXOP_READADDR 2
#define OSC_RXOP_READTAG 3
#define OSC_RXOP_READARG 4
#define OSC_RXOP_READCHECKSUM 5
//removed READMSG
#define OSC_RXOP_SKIPMSG 7
#define OSC_RXOP_READARG1BYTE1 8
#define OSC_RXOP_READARG1BYTE2 9
#define OSC_RXOP_READARG1BYTE3 10
#define OSC_RXOP_READARG1BYTE4 11
#define OSC_RXOP_READTAGBYTE1 12
#define OSC_RXOP_READTAGBYTE2 13
#define OSC_RXOP_READTAGBYTE3 14
#define OSC_RXOP_READTAGBYTE4 15
#define OSC_MAX_RX_MSG_SIZE 32


int incomingByte = 0;	// for incoming serial data
int k = FIRST_ANALOG_PIN;

int inputBuffer = 0xFFFF; // holds previous values of PORTB and PORTD (pins 0..7); start all high because of pull-ups
int a2dBuffer[6] = {0x00};   // holds previous A2D conversion values
char oscBuffer[MAX_LENGTH]={0x00}; // holds outgoing OSC message

unsigned int pinDir = 0x0000; //buffer that saves pin directions 0=input; 1=output; default: all in

char prefixReport[] = "/report/";
char prefixPinmode[] = "/pinmode/";
char prefixOut[] = "/out/";
char prefixPwm[] = "/pwm/";
char prefixIn[]="/in/";
char prefixA2d[]="/adc/";
char prefixReset[]="/reset"; //TODO: implement

char oscOutAddress[10]={0x00}; //string that holds outgoing osc message address

char* numbers[] = {"0","1","2","3","4","5","6","7","8","9","10","11","12"};

// which values should be reported?
byte reportAnalog = 0x00; //bitmask - 0=off, 1=on - default:all off 
boolean reportDigital = true; //no per-pin reporting for analog

//////parser variables////////
static byte oscRxNextOp = OSC_RXOP_WAITFORSTART; //keeps track of current state
// space for buffer in RAM
static char oscRxData[OSC_MAX_RX_MSG_SIZE];

byte oscRxMsgSize; // size of incoming msg
byte oscRxReadBytes; //number of bytes read
byte *oscRxAddr;
unsigned long oscRxIntArg1; //int argument of message
byte oscRxChecksum;


/***********************************************
 * SETUP - open serial comm and initialize pins
 ***********************************************/
void setup() {
  int i;
  reportAnalog=0x00;
  reportDigital=true;
  // set pins 2-12 as inputs   
  for(i=FIRST_DIGITAL_PIN; i<=LAST_DIGITAL_PIN; i++) {
    pinMode(i,INPUT);
    digitalWrite(i,HIGH); // use pull-ups
  } 
  Serial.begin(SERIAL_SPEED);
}

/***********************************************
 * LOOP - poll pin values and read incoming 
 * serial communication
 ***********************************************/
void loop() {

  // check all digital inputs
  if(reportDigital) {
    checkDiscreteInputs();
  }

  // check one analog input per loop
  if(reportAnalog & (1<<k)) {
    checkAnalogInput(k);
  }
  k=(k+1)%NUM_ANALOG_PINS;

  // handle all received serial bytes
  while (Serial.available() > 0) {
    incomingByte = Serial.read() & 0xFF;// read byte - truncate to 8bits to be safe
    oscRxHandler(incomingByte); // hand to message parser
  }

}

/***********************************************
 * Check all digital inputs and call 
 * oscSendMessageInt() if values has changed
 ***********************************************/
void checkDiscreteInputs() {
  int i;

  //read PORT B (13..8) and PORT D (pins 7..0) into one int
  unsigned int state = 0x0000 | (PINB << 8) | PIND;

  // if the state of a pin has changed since last time, 
  // and that pin is an input pin, send a message
  for(i=FIRST_DIGITAL_PIN;i<=LAST_DIGITAL_PIN;i++) {
    if(!(pinDir & (1<<i))) { //if pin is input
      if  ((state & (1<<i)) != (inputBuffer &(1<<i))) {
        strcpy(oscOutAddress,prefixIn);
        strcat(oscOutAddress,numbers[i]);
        oscSendMessageInt(oscOutAddress, !(state & (1<<i)));
      }
    }
  }

  //save current state to buffer
  inputBuffer= state;
}


/***********************************************
 * Check one analog input channel and call 
 * oscSendMessageInt() if its value has changed
 ***********************************************/
void checkAnalogInput(byte channel) {
  int result;
  int diff;
  // read a2d
  result = analogRead(channel) >> 2; //only use 8 MSBs

  // compare to last reading - if delta big enough,
  // send message
  //diff = result - a2dBuffer[channel];
  //if(diff>MIN_A2D_DIFF || diff<(int)((-1)*MIN_A2D_DIFF)) {
  if(result!=a2dBuffer[channel]) {
    a2dBuffer[channel]=result;
    strcpy(oscOutAddress,prefixA2d);
    strcat(oscOutAddress,numbers[channel]);
    oscSendMessageInt(oscOutAddress, result);
  }
}


/***********************************************
 * Send an OSC message with the passed in
 * address and a single integer argument
 ***********************************************/
void oscSendMessageInt(char * address, unsigned long value){
  byte offset=0;
  byte i=0;

  // clear buffer
  for(i=0; i<MAX_LENGTH; i++) {
    oscBuffer[i]=0x00;
  }

  //write packet header
  oscBuffer[offset++]=0xBE;

  //compute message length 
  //first compute address string length and padd if necessary
  byte addrlen = strlen(address);
  if(addrlen&0x03)				
    addrlen += 4-(addrlen&0x03);

  //then add type-tag length and arg length (both 4 for a simple int message)
  byte typetaglen=4;
  byte arglen = 4;

  //final length is sum of the three
  byte len = addrlen+typetaglen+arglen;

  //write message length
  oscBuffer[offset++]=(unsigned char)len;

  //write address
  strcpy(oscBuffer+offset,address); 
  offset+=addrlen;

  //write typetag
  oscBuffer[offset++]=',';
  oscBuffer[offset++]='i';
  oscBuffer[offset++]=0x00;
  oscBuffer[offset++]=0x00;

  //write argument
  oscBuffer[offset++]=*(((unsigned char *)(&value))+3);
  oscBuffer[offset++]=*(((unsigned char *)(&value))+2);
  oscBuffer[offset++]=*(((unsigned char *)(&value))+1);
  oscBuffer[offset++]=*(((unsigned char *)(&value))+0);

  //compute + write checksum
  byte checksum=0;
  for(i=2; i<offset; i++) {
    checksum+=oscBuffer[i];
  }
  oscBuffer[offset++]=checksum;

  //send message byte-by-byte
  for(i=0;i<offset;i++) {
    Serial.print(oscBuffer[i],BYTE);
  }
}


/***********************************************
 * Handle a received OSC message
 ***********************************************/
void oscReceiveMessageInt(char * msg, unsigned long value)
{
  int i;
  int outPin;
  
  //uncomment to echo message back for debugging
  //oscSendMessageInt(msg,value);
  
  // check if this is an output message, i.e., starts with "/out/"
  if(strncmp(msg,prefixOut,strlen(prefixOut))==0) {
    //if so, find which pin
    outPin = atoi(msg+strlen(prefixOut));
    if(outPin>=FIRST_DIGITAL_PIN && outPin<=LAST_DIGITAL_PIN) { //sanity check
      digitalWrite(outPin,(byte)(value & 0x01)); 
    }
    return;
  }

  // check if this is a pwm message, i.e., starts with "/pwm/"
  if(strncmp(msg,prefixPwm,strlen(prefixPwm))==0) {
    outPin = atoi(msg+strlen(prefixPwm));
    if(outPin>=FIRST_DIGITAL_PIN && outPin<=LAST_DIGITAL_PIN) { //sanity check
      pinDir = pinDir | (1<<outPin); //turn direction bit to out
      pinMode(outPin,OUTPUT); // turn DDR bit to output
      analogWrite(outPin,(byte)(value & 0xFF));
    }
    return;
  }

  // check if this is a "report" message which starts with "/report/"
  // changes which pins get reported
  if(strncmp(msg,prefixReport,strlen(prefixReport))==0) {
    //if it continues with "/in"

    if(strncmp(msg+strlen(prefixReport)-1,prefixIn,strlen(prefixIn)-1)==0) {
      reportDigital = (value!=0);
      return;
    }

    //else if it continues with "/adc/"
    else if(strncmp(msg+strlen(prefixReport)-1,prefixA2d,strlen(prefixA2d))==0) {
      //extract which analog pin we're talking about
      outPin = atoi(msg+strlen(prefixReport)-1+strlen(prefixA2d));
      //flip the bit in reportAnalog:
      if(outPin>=FIRST_ANALOG_PIN && outPin<=LAST_ANALOG_PIN) { //sanity check
        if(value==0) {
          reportAnalog = reportAnalog & ~(1<<outPin);
        }   
        else {
          reportAnalog = reportAnalog | (1<<outPin);
        }
      }
      return;
    }

    //else if it continues with "/adc" (no final slash)
    else if(strncmp(msg+strlen(prefixReport)-1,prefixA2d,strlen(prefixA2d)-1)==0) {
      //turn reporting for all analog pins on or off
      if(value==0) {
        reportAnalog=0x00;
      } 
      else {
        reportAnalog=0xFF;
      }
      return;
    }
  }
  
  //finally, this could be a "/pinmode/ message"
  if(strncmp(msg,prefixPinmode,strlen(prefixPinmode))==0) {
    outPin = atoi(msg+strlen(prefixPinmode));
    if(outPin>=FIRST_DIGITAL_PIN && outPin<=LAST_DIGITAL_PIN) { //sanity check
      if(value==0) {
        pinDir = pinDir & ~(1<<outPin); //turn bit in our own direction buffer to off = input
        pinMode(outPin,INPUT); //set DDR register bit to input
        digitalWrite(outPin,HIGH); //reenable pull-up
      } 
      else {
        pinDir = pinDir | (1<<outPin); //turn bit on
        pinMode(outPin,OUTPUT); // turn DDR bit to output
        digitalWrite(outPin,LOW); //set LOW by default
      }
    }
    return;
  }
  //is this a reset message? if so, reinitialize.
  if(strncmp(msg,prefixReset,strlen(prefixReset))==0) {
    oscRxNextOp = OSC_RXOP_WAITFORSTART;
    setup();
  }
}



/***********************************
 * PARSING OF MESSAGES BELOW
 ***********************************/





/***********************************
 * PARSER
 ***********************************/
void oscRxHandler(unsigned char c) {
  byte i;
  switch(oscRxNextOp) {
  case OSC_RXOP_WAITFORSTART:
    if(c==0xBE) { //0xBE is the magic start byte
      oscRxNextOp = OSC_RXOP_READSIZE;
    }
    break;

  case OSC_RXOP_READSIZE:
    oscRxMsgSize = c; // read message size
    oscRxReadBytes = 0; //reset index into message buffer
    if(oscRxMsgSize < (OSC_MAX_RX_MSG_SIZE-1)) {
      oscRxNextOp = OSC_RXOP_READADDR;
    } 
    else {
      oscRxNextOp = OSC_RXOP_SKIPMSG; //Msg is too long
    }
    break;

  case OSC_RXOP_READADDR:
    if(c!=0 && c!=',') {
      oscRxData[oscRxReadBytes++] = c; //copy normal addr byte
    } 
    else if (c==',') {
      //if we went straight from addr to to tag string, convert "," of tag string to 0x00
      // so our address string is properly zero-terminated
      //and jump ahead in the state machine to read second tag byte next
      oscRxData[oscRxReadBytes++]=0x00;
      oscRxNextOp = OSC_RXOP_READTAGBYTE2;
    }
    else {
      oscRxData[oscRxReadBytes++] = 0;
      if(!((oscRxReadBytes)&0x03)) { //skip 0s until we hit byte boundary
        oscRxNextOp = OSC_RXOP_READTAGBYTE1; 
      } 
    }
    break;

    // read type tag string bytes 1-4
  case OSC_RXOP_READTAGBYTE1:
    oscRxData[oscRxReadBytes++] = c;
    if(c==',') {
      // valid type tag start character found	
      oscRxNextOp = OSC_RXOP_READTAGBYTE2;
    } 
    else {
      // no type tag start char present
      // assume one int arg and read its first byte
      oscRxIntArg1 = 0;
      oscRxIntArg1 |= ((unsigned long)(c) << 0x18);
      oscRxNextOp = OSC_RXOP_READARG1BYTE2;
    }
    break;
  case OSC_RXOP_READTAGBYTE2:
    oscRxData[oscRxReadBytes++] = c;
    switch (c) {
    case 'i': //int32 argument
      oscRxNextOp = OSC_RXOP_READTAGBYTE3;
      break;
      // all other types besides int are not supported yet
      // so skip remainder of message
    case 'f': //float arg
    case 's': //string arg
    default:
      oscRxNextOp = OSC_RXOP_SKIPMSG;
    }
    break;
  case OSC_RXOP_READTAGBYTE3:
    oscRxData[oscRxReadBytes++] = c;
    switch (c) {
      // null - message has only one arg - we're ok
    case 0:
      oscRxNextOp = OSC_RXOP_READTAGBYTE4;
      break;
      // all others: not yet supported; skip rest of message
    default:
      oscRxNextOp = OSC_RXOP_SKIPMSG;
      break;
    }
    break;
  case OSC_RXOP_READTAGBYTE4:
    oscRxData[oscRxReadBytes++] = c;
    switch (c) {
      // null - message has only one arg - we're ok
    case 0:
      oscRxNextOp = OSC_RXOP_READARG1BYTE1;
      break;
      // all others: not yet supported; skip rest of message
    default:
      oscRxNextOp = OSC_RXOP_SKIPMSG;
      break;
    }
    break;

    // read argument bytes 1-4
  case OSC_RXOP_READARG1BYTE1:
    oscRxData[oscRxReadBytes++] = c;
    oscRxIntArg1 = 0;
    oscRxIntArg1 |= ((unsigned long)(c) << 0x18);
    oscRxNextOp = OSC_RXOP_READARG1BYTE2;
    break;
  case OSC_RXOP_READARG1BYTE2:
    oscRxData[oscRxReadBytes++] = c;
    oscRxIntArg1 |= ((unsigned long)(c) << 0x10);
    oscRxNextOp = OSC_RXOP_READARG1BYTE3;
    break;
  case OSC_RXOP_READARG1BYTE3:
    oscRxData[oscRxReadBytes++] = c;
    oscRxIntArg1 |= ((unsigned long)(c) << 0x08);
    oscRxNextOp = OSC_RXOP_READARG1BYTE4;
    break;
  case OSC_RXOP_READARG1BYTE4:
    oscRxData[oscRxReadBytes++] = c;
    oscRxIntArg1 |= (unsigned long)(c);
    oscRxNextOp = OSC_RXOP_READCHECKSUM;
    break;

    // read checksum byte; check msg integrity; fire off user function
  case OSC_RXOP_READCHECKSUM:
    // check that we read the right number of bytes
    if (oscRxReadBytes != oscRxMsgSize) {
      oscSendMessageInt("/error/msgsize/",oscRxReadBytes);
    } 
    else {
      oscRxChecksum = 0;
      for (i=0; i<oscRxMsgSize; i++) {
        oscRxChecksum+=oscRxData[i];
      }
      if(oscRxChecksum == c) {
        // checksum matched and we're done with this msg
        // -> fire off user function
        oscReceiveMessageInt(oscRxData,oscRxIntArg1);

      } 
      else {
        // mismatch - throw this message away
        oscSendMessageInt("/error/checksum",oscRxChecksum);
      }
    }
    // wait for next message header
    oscRxNextOp = OSC_RXOP_WAITFORSTART;
    break;

    //skip rest of message - called if an error was detected in the current 
    //incoming message
  case OSC_RXOP_SKIPMSG:
    if(++oscRxReadBytes == (oscRxMsgSize+1)) {
      oscRxNextOp = OSC_RXOP_WAITFORSTART;
    }
    break;
  default:
    oscRxNextOp = OSC_RXOP_WAITFORSTART;
  }
}
