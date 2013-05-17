/*
# This Sample code is for showing the colorful light of the breakout randomly
# Product: RGB LED Breakout(5050)
# SKU    : DFR0238

# Connection:
     R-Digital 9
     G-Digital 10
     B-Digital 11
     GND-Gnd
*/
#include <RGBLED.h>

RGBLED myled = RGBLED(9,10,11);

void setup(){
//  myled.InitPins();
}
void loop(){
  myled.colorRGB(random(0,255),random(0,255),random(0,255)); //R:0-255 G:0-255 B:0-255
  delay(1000);
}
