///
/// @file	PlainProtocol.h
/// @brief	Library header
///
/// @details	DFRobot PlainProtocol for arduino
/// @n	
/// @n @b	Project PlainProtocol
/// @n @a	Developed with [embedXcode](http://embedXcode.weebly.com)
/// 
/// @author	qiao
/// @author	qiao
/// @date	13-4-2 上午9:17
/// @version	1.0
/// 
/// @copyright	© qiao, 2013年
/// @copyright	CC = BY NC SA
///
/// @see	ReadMe.txt for references
///

/*
                                  PlainProtocol Frame
 |----------------------------------------------------------|-------------------------------|
 |  <Command>Content;                                       | <speed>100;                   |
 |----------------------------------------------------------|-------------------------------|
 |  <Command>Content1,Content2;                             | <speed>100,200;               |
 |----------------------------------------------------------|-------------------------------|
 |  <Command1>Content1;<Command2>Content2;                  | <speed>100; <direction>100;   |
 |----------------------------------------------------------|-------------------------------|
 |  #Address<Command>Content;                               | #1<speed>100;                 |
 |----------------------------------------------------------|-------------------------------|
 |  #Address<Command>Content1,Content2;                     | #1<speed>100,200;             |
 |----------------------------------------------------------|-------------------------------|
 |  #Address1<Command1>Content1;#Address2<Command2>Content2;| #1<speed>100;#2<direction>100;|
 |----------------------------------------------------------|-------------------------------|
 */
#ifndef ARDUINO
#define ARDUINO 103
#endif

// Core library - IDE-based
#if defined(MPIDE) // chipKIT specific
#include "WProgram.h"
#elif defined(DIGISPARK) // Digispark specific
#include "Arduino.h"
#elif defined(ENERGIA) // LaunchPad, FraunchPad and StellarPad specific
#include "Energia.h"
#elif defined(MAPLE_IDE) // Maple specific
#include "WProgram.h"
#elif defined(CORE_TEENSY) // Teensy specific
#include "WProgram.h"
#elif defined(WIRING) // Wiring specific
#include "Wiring.h"
#elif defined(ARDUINO) && (ARDUINO >= 100) // Arduino 1.0x and 1.5x specific
#include "Arduino.h"
#elif defined(ARDUINO) && (ARDUINO < 100)  // Arduino 23 specific
#include "WProgram.h"
#endif // end IDE

#ifndef PlainProtocol_LocalLibrary_h
#define PlainProtocol_LocalLibrary_h

#define MaxContentLenth  5      //the max lenth of content, you can change it on your own

class PlainProtocol {
private:

  String frame;                           //the frame of the protocol
  HardwareSerial& SerialTransceiver;      //serial port to communicate with
  unsigned long serialBaud;               //baud of the serial
  void sendFrame();                       //send the frame prototype
  boolean parseFrame(String theFrame);    //parse the frame received
  boolean isNumber(String&  stringbuf);   //confirm whether the string is a valid number
  
public:
  boolean isSendingAddress,isReceivedAddress; //whether using address mode for received and sending
  
  String receivedCommand,sendingCommand;      //input and output command name
  int receivedAddress,sendingAddress;         //input and output adress number
  int receivedContent[MaxContentLenth],sendingContent[MaxContentLenth];   //input and output content
  int receivedContentLenth,sendingContentLenth;   //input and output content lenth

  //Constructor
#if defined(UBRR1H)       //if there exists Serial1, use Serial1
  PlainProtocol(HardwareSerial& serialSelect=Serial1, unsigned long baud=57600);
#else                     //if not, use Serial instead
  PlainProtocol(HardwareSerial& serialSelect=Serial, unsigned long baud=57600);
#endif
  void init();            //initiation for the PlainProtocol
  
  /*
   This function should be put in the loop and called periodically.
   when receiving a valid frame, results will be put in the variables: receivedCommand, receivedAddress, receivedContent, receivedContentLenth, and return true.
  */
  boolean receiveFrame();

  //send the frame directly
  void sendFrame(String theFrame);
  
  //send the frame without address, the content should be int only.
  void sendFrame(String command, int lenth, ...);
  
  //send the frame with address, the content should be int only.
  void sendFrame(int address, String command, int lenth, ...);
  
  void write(String command);
  void write(String command,int sendingContent0);
  void write(String command,int sendingContent0, int sendingContent1);
  void write(String command,int sendingContent0, int sendingContent1, int sendingContent2);
  void write(String command,int sendingContent0, int sendingContent1, int sendingContent2, int sendingContent3);
  void write(String command,int sendingContent0, int sendingContent1, int sendingContent2, int sendingContent3, int sendingContent4);

  boolean available();

  
  
  
  

};

#endif
