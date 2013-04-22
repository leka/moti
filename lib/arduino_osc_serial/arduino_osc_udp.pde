#include <Ethernet.h>
#include <UdpRaw.h>


/**************************************************************
 * ARDUINO_OSC_UDP 0001
 * based on ARDUINO_OSC 0005
 *
 * Firmware to send and receive OSC messages from an Arduino board to a PC
 * over UDP using the Arduino Shield.
 *
 * Right now, only messages with a single integer argument
 * are supported.
 *
 * Uses the standard OSC packet format (no serial wrapping)
 * 
 * PROTOCOL DETAILS
 * Digital pins 0..9 and analog inputs 0..5 are supported.
 * Digital pins 8 and 9 are still screwey.
 *
 * Below, the notation [0..9] means: any number from 0 to 9.
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
 * /in/[0..9] [0|1]    - a digital input pin changed to [high|low]
 * /adc/[0..5] [0..255] - analog input value changed to [0..255]
 * NOTE: input pins use pull-up resistors and are HIGH by default.
 * Therefore, 0 means HIGH, 1 means LOW (pulled to ground). 
 *
 *
 * EXAMPLES: PC->ARDUINO 
 * /pinmode/5 0         - set pin 5 to INPUT
 * /pinmode/9 1         - set pin 9 to OUTPUT
 * /out/9 0             - set pin 9 to LOW
 * /out/7 1            - set pin 7 to HIGH
 * /pwm/9 255          - set PWM duty on pin 9 to 255 (100%)
 * /report/in 1         - turn digital input pin reporting on
 * /report/adc/4 0      - turn reporting of analog input 4 off
 *
 * EXAMPLES: ARDUINO->PC
 * /in/4 1              - digital input pin 4 pulled to ground
 * /adc/2 128           - analog input pin2 read 128 (=2.5V)
 * 
 * DEFAULT STARTUP CONFIGURATION
 *   - Pins 0..9 are all set to input, digital reporting enabled
 *     (change variable reportDigital to False to disable by default)
 *   - Analog reporting is disabled 
 *     (change variable reportAnalog to 0xFF to enable by default)
 *
 * YOU WILL HAVE TO CHANGE ETHERNET CONFIGURATION TO MATCH YOUR
 * ENVIRONMENT BEFORE COMPILING/UPLOADING!
 *
 * NOTES:
 *   - Pins 10-13 cannot be used (needed for SPI communication with ethernet shield)
 *   - Resolution on analog in and out is 8 bit. 
 * 
 * MIT License:
 * Copyright (c) 2008 Bjoern Hartmann
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
 * bjoern@cs.stanford.edu 12/28/2008
 **************************************************************/

#define VERSION 1


#define MAX_LENGTH 32   // size of buffer for OSC msgs (in and out)


#define FIRST_DIGITAL_PIN 0
#define LAST_DIGITAL_PIN 9
#define NUM_DIGITAL_PINS 10

#define FIRST_ANALOG_PIN 0
#define LAST_ANALOG_PIN 5
#define NUM_ANALOG_PINS 6


/* ETHERNET CONFIGURATION *************************************/
/* ARDUINO: set MAC, IP address of Ethernet shield, its gateway,
   and local port to listen on for incoming packets */
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //MAC address to use
byte ip[] = { 192, 168, 11, 200 }; // Arduino's IP address
byte gw[] = { 192, 168, 11, 1 };   // Gateway IP address
int localPort = 8888; //local port to listen on

/* TARGET: set this to IP/Port of computer that will receive
 * UDP messages from Arduino */
byte targetIp[] = {192,168,11,15};
int targetPort = 8000;
/***************************************************************/


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
char prefixEcho[]="/echo";

char oscOutAddress[10]={0x00}; //string that holds outgoing osc message address
char* numbers[] = {"0","1","2","3","4","5","6","7","8","9","10","11","12"};



/* Buffers for received messages */
byte rcvIp[4]; //source ip from which last packet originated
int rcvPort; // source port from which last packet originated
byte rcvBuffer[MAX_LENGTH]; //messagebuf for incoming packet


// which values should be reported? configured in setup()
byte reportAnalog; //bitmask - 0=off, 1=on - default:all off 
boolean reportDigital; //no per-pin reporting for analog

/* timer variables */
int a2dReportFrequency = 10; //report frequency for analog data in ms
unsigned long currentMillis=1;
unsigned long nextExecuteTime=0; // for comparison with timer0_overflow_count

byte oscRxMsgSize; // size of incoming msg
byte oscRxReadBytes; //number of bytes read

unsigned long oscRxIntArg1; //int argument of incoming osc message


/***********************************************
 * SETUP - open serial comm and initialize pins
 ***********************************************/
void setup() {
  int i;
  
  reportAnalog=0x00; 
  reportDigital=true;

  // set all digital pins as inputs
  for(i=FIRST_DIGITAL_PIN; i<=LAST_DIGITAL_PIN; i++) {
    pinMode(i,INPUT);
    digitalWrite(i,HIGH); // use pull-ups
  } 
  
  Ethernet.begin(mac,ip,gw);
  UdpRaw.begin(localPort);
  //DEBUG: Serial.begin(9600);
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
	// check analog inputs every 10ms
	currentMillis = millis();
	if(currentMillis > nextExecuteTime) {  
		nextExecuteTime = currentMillis + (a2dReportFrequency -1); // run this every 10ms (arbitrary?)
		for(k=0;k<NUM_ANALOG_PINS;k++) {
			if(reportAnalog & (1<<k)) {
		    checkAnalogInput(k);
		  }
		}
	}

  //if there's data available, read a packet
  if(UdpRaw.available()) {
    oscRxMsgSize = UdpRaw.readPacket(rcvBuffer,MAX_LENGTH,rcvIp,(uint16_t *)&rcvPort);
    if(oscRxMsgSize <= MAX_LENGTH) {
      oscHandleRxPacket();
    } else {
      //PANIC - we've already clobbered mem past our buffer boundary
      //reset?
    }
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

  //send message as one packet
  UdpRaw.sendPacket((byte *)oscBuffer,offset,targetIp,targetPort);

}




/***********************************************
 * Handle a received OSC message
 ***********************************************/
void oscReceiveMessageInt(char * msg, unsigned long value)
{
  int i;
  int outPin;
  
  //uncomment to echo message back for debugging
  Serial.println(msg);
  Serial.println(value);
  
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
    setup();
    return;
  }
  //is this an echo message? if so, send it back.
  if(strncmp(msg,prefixEcho,strlen(prefixReset))==0) {
    oscSendMessageInt(prefixEcho,0);
  }
}


/***********************************
 * PARSER
 ***********************************/
void oscHandleRxPacket() {
  byte i;
  int intArg;
  unsigned char c;
  oscRxReadBytes=0;
  
  //read address and null-terminate it if necessary
  while (true) {
    c=(unsigned char) rcvBuffer[oscRxReadBytes];
    if(c!=0 && c!=',') {
      oscRxReadBytes++;
    } 
    else if (c==',') {
      //if we went straight from addr to to tag string, convert "," of tag string to 0x00
      // so our address string is properly zero-terminated
      //and jump ahead in the state machine to read second tag byte next
      rcvBuffer[oscRxReadBytes++]=0x00;
      break;
    }
    else {
      oscRxReadBytes++;
      if(!((oscRxReadBytes)&0x03)) { //skip 0s until we hit byte boundary
        break; 
      } 
    }
  }
  
  
  //read typetag if present 
  if(rcvBuffer[oscRxReadBytes]==',') {
    // found typetag start, assume its ',' 'i' 0x00 0x00
    oscRxReadBytes++;
    if(rcvBuffer[oscRxReadBytes]=='i') {
       oscRxReadBytes+=3; //skip following  0x00 twice
       //now read argument
       oscRxIntArg1 = readLongInt(rcvBuffer,oscRxReadBytes);
       //dispatch message
       oscReceiveMessageInt((char *)rcvBuffer,oscRxIntArg1);
    }
  } else {
    // no type tag, read argument right away
    oscRxIntArg1 = readLongInt(rcvBuffer,oscRxReadBytes);
    //dispatch message
    oscReceiveMessageInt((char *)rcvBuffer,oscRxIntArg1);
    
  }
}

// read an unsigned long int from 4 bytes in buffer,
// starting at offset, MSB first
unsigned long readLongInt(byte * buffer, int offset) {
  unsigned long result=0;
  result |= ((unsigned long)(buffer[offset]) << 0x18);
  result |= ((unsigned long)(buffer[offset+1]) << 0x10);
  result |= ((unsigned long)(buffer[offset+2]) << 0x08);
  result |= ((unsigned long)(buffer[offset+3]));
  return result;
}

