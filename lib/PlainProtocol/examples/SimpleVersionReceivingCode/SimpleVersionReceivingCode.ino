#include <PlainProtocol.h>

PlainProtocol mytest(Serial, 57600);

int motorSpeed;
int motorDestination[2];

void setup() {
  mytest.init();
}

void loop() {

  if (mytest.available()) {
    if (mytest.receivedCommand=="speed") {
      //the "speed" process
      motorSpeed=mytest.receivedContent[0];
    }
    else if (mytest.receivedCommand=="destination"){
      //the "destination" process
      motorDestination[0]=mytest.receivedContent[0];
      motorDestination[1]=mytest.receivedContent[1];
    }
    else{
      //no matching command
    }
  }
}