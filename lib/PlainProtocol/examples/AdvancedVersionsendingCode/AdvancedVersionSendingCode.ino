#include <PlainProtocol.h>

PlainProtocol mytest;

void setup() {
  mytest.init();
}

void loop() {
  static unsigned long loopTimer=millis();
  //send the frame
  if (millis()-loopTimer>100) {
    loopTimer=millis();

    //the following two function do the same thing
    mytest.sendFrame("<speed>,56,93,812;");
    mytest.sendFrame("speed"/*sendingCommand*/,3/*sendingContentLenth*/,56,93,812/*three sendingContent, int only*/);

    //the following two function do the same thing
    mytest.sendFrame("#3<speed>,56,93;");
    mytest.sendFrame(3/*sendingAddress*/,"speed"/*sendingCommand*/,2/*sendingContentLenth*/,56,93/*two sendingContent, int only*/);

    //the following three function do the same thing
    mytest.sendFrame("<speed>;");
    mytest.sendFrame("speed"/*sendingCommand*/);//the string without ';' will deal with command without content
    mytest.sendFrame("speed"/*sendingCommand*/,0/*sendingContentLenth*/);
  }
}