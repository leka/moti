////////////////////////////////////////////////////////////
// Arduino firmware for use with FreeSixCube processing example
////////////////////////////////////////////////////////////

#include <FreeSixIMU.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>

#include <RGBLED.h>

#define DEBUG
#ifdef DEBUG
#include "DebugUtils.h"
#endif

#include "CommunicationUtils.h"
#include "FreeSixIMU.h"
#include <Wire.h>


float q[4]; //hold q values

RGBLED myled = RGBLED(44,45,46);
float R,G,B, Rr;
float RGB[6];

// Set the FreeIMU object
FreeSixIMU my3IMU = FreeSixIMU();

void setup() {
  Serial.begin(115200);
  Wire.begin();

  delay(5);
  my3IMU.init();
  delay(5);
}


void loop() { 
  my3IMU.getQ(q);
  my3IMU.getValues(RGB); 

  Rr = 0.1*sqrt( pow(RGB[0],2) + pow(RGB[1],2) + pow(RGB[2],2));
  // r = decodeFloat(q[1]);
  // g = decodeFloat(q[2]);
  // b = decodeFloat(q[3]);

  R = constrain(RGB[0], 0, 255);
  G = constrain(RGB[1], 0, 255);
  B = constrain(RGB[2], 0, 255);
  
  myled.colorRGB(R, G, B);
  Serial.print(RGB[0]);
  Serial.print("\t");
  Serial.print(RGB[1]);
  Serial.print("\t");
  Serial.print(RGB[2]);
  Serial.print("\t");
  Serial.println(Rr);
  // serialPrintFloatArr(q, 4);
  // Serial.println(""); //line break
 
  delay(60);
}

// float decodeFloat(String inString) {
//   byte inData[4];

//   if (inString.length() == 8) {
//     inData[0] = (byte) unhex(inString.substring(0, 2));
//     inData[1] = (byte) unhex(inString.substring(2, 4));
//     inData[2] = (byte) unhex(inString.substring(4, 6));
//     inData[3] = (byte) unhex(inString.substring(6, 8));
//   }

//   int intbits = (inData[3] << 24) | ((inData[2] & 0xff) << 16) | ((inData[1] & 0xff) << 8) | (inData[0] & 0xff);
//   return Float.intBitsToFloat(intbits);
// }
