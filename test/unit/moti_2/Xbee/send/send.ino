
/*
  XBEE #2 SENDER
  ==============
  Button-Arduino-Xbee#2 > Xbee#1-Arduino-led
  Most code from : XBee Analog Duplex sender
  http://www.faludi.com/classes/sociableobjects/code/XBee_Analog_Duplex_Sender.pde
 */
const int button = 2;
const int led = 13; // just to see when zigbee is ok
int buttonState;
int lastButtonState = LOW;
int i = 0;

void setup() {
  Serial.begin(115200);
  pinMode (led, OUTPUT);
  pinMode (button, INPUT);
  setDestination();
  blink(led, 3);
}

void loop() {

  buttonState = i%2;
  if (buttonState != lastButtonState) {
    // Send serial data to xbee #1
    Serial.println(buttonState, DEC);
    lastButtonState = buttonState;
  }
  i++;
  delay(500);
}

// Xbee configuration
void setDestination() {
  Serial.print("+++");
  char thisByte = 0;
  while (thisByte != '\r') { // wait for xbee response
    if (Serial.available() > 0) {
      thisByte = Serial.read();
    }
  }
  Serial.print("ATRE\r");
  Serial.print("ATDL0\r"); // sent to xbee 0
  Serial.print("ATMY1\r"); // this xbee is 1
  Serial.print("ATID1111\r");
  Serial.print("ATCN\r");
}

// Blink
void blink(int thisPin, int howManyTimes) {
  for (int blinks=0; blinks< howManyTimes; blinks++) {
    digitalWrite(thisPin, HIGH);
    delay(200);
    digitalWrite(thisPin, LOW);
    delay(200);
  }
}
