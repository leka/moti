
#include <RGBLED.h>

RGBLED myled = RGBLED(44,45,46);

void setup(){
//  myled.InitPins();
}
void loop(){
  myled.colorRGB(random(0,255),random(0,255),random(0,255)); //R:0-255 G:0-255 B:0-255
  delay(200);
}
