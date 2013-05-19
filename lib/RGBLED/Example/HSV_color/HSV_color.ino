/*
# This Sample code is for showing the full color of the breakout
# Product: RGB LED Breakout(5050)
# SKU    : DFR0238

# Connection:
     R-D9
     G-D10
     B-D11
     GND-Gnd
*/
#include <RGBLED.h>

RGBLED myled = RGBLED(9,10,11); //9:Red  10:Green   11:Blue

void setup(){
//  myled.InitPins();
}

void loop(){
  
 for(int j = 0;j < 360; j++){  
 myled.colorHSV(j,255,255);     //H:0-360   S:0-255  V:0-255
 delay(20);
 }

}
