#include <PlainProtocol.h>

PlainProtocol mytest;

void setup() {
  mytest.init();
  Serial.begin(57600);
}

void loop() {
  //Receive frame from serial. This function should be put in the loop and called periodically as following:
  if (mytest.receiveFrame()) {
    //if the received command is "speed", do the "speed" process. 
    if (mytest.receivedCommand=="speed") {
      //the "speed" process
      //the received command, the type is "Class String"
      Serial.println(mytest.receivedCommand);
      //the Lenth of received Content 
      Serial.println(mytest.receivedContentLenth);
      for (int i=0; i<mytest.receivedContentLenth; i++) {
        //the received content in an array
        Serial.println(mytest.receivedContent[i]);
      }
      Serial.println();
    }
    else if (mytest.receivedCommand=="torque"){
      //torque process
      //the same as above
      Serial.println(mytest.receivedCommand);
      Serial.println(mytest.receivedContentLenth);
      for (int i=0; i<mytest.receivedContentLenth; i++) {
        Serial.println(mytest.receivedContent[i]);
      }
      Serial.println();
    }
    else{
      //no matching command
      Serial.println("command not available");
    }
  }
}