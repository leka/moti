#include <PlainProtocol.h>

PlainProtocol mytest(Serial, 57600);

void setup() {
  mytest.init();
}

void loop() {
  mytest.write("speed",100);          //set the speed to 100
  mytest.write("destination", 23, 56); //set the destination to (23,56)
  delay(500);
}