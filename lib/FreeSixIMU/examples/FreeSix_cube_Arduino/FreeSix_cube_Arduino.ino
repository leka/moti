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
int r,g,b,R,G,B;

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
  r = String(q[1], DEC);
  g = String(q[2], DEC);
  b = String(q[3], DEC);

  R = constrain(r, 0, 255);
  G = constrain(g, 0, 255);
  B = constrain(b, 0, 255);
  
  myled.colorRGB(R, G, B);
  serialPrintFloatArr(q, 4);
  Serial.println(""); //line break
 
  delay(60);
}
