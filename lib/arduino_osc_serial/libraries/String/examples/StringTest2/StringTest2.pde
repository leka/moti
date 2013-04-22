/*
  String demo
 
 Demonstrates the functionality of the String library
 
 To test it, send the microcontroller a few different strings.
 Try strings with white space at the beginning, at the end, and 
 on both.
 
 Try the string "What's up?"
 
 by Tom Igoe
 created 20 Oct. 2006
 */


#include <WString.h>                // include the String library
String inString = String(90);  // allocate a new String
String verString = String("String library version ");

void setup() {
  // open the serial port:
 Serial.begin(9600);
  // blink an LED:
  blink(13,3);
  // Say hello:
 Serial.print(verString.toCharArray());
  Serial.println(inString.version());
}

void loop () {
  // read serial data in:
  if(Serial.available() > 0) {
    serialEvent(); 
  }
}

void serialEvent() {

  // get the latest character:
  char inChar = Serial.read();
  // if you don't get a newline, add it to the string:
  if ((inChar != '\n') && (inChar != '\r')) {
    inString.append(inChar);
  } 
  else {
    // print the whole string:
    Serial.print("String = ");
    Serial.println(inString.toCharArray());
    Serial.print("String Length: ");

    // print the length of the string:
    Serial.println(inString.length(), DEC);


    // trim the string:
    inString.trim();
    Serial.println(inString.toCharArray());
    Serial.print("trimmed string Length: ");
    // print the length of the string:
    Serial.println(inString.length(), DEC);

    // compare the string to another arbitrary string:
    Serial.print("String equals What's up?: ");
    Serial.println(inString.equals("What's up?"), DEC);

    // look for a subString:
    Serial.print("String contains OK: ");
    Serial.println(inString.contains("OK"), DEC);

    // copy a given string in:
    inString.setArray("What's up, Doc?");
    Serial.println(inString.toCharArray());
    // print the length of the string:
    Serial.println(inString.length(), DEC);
    // empty the string:
    inString = "";
    // print a blank line:
    Serial.println("-----------------------------------------");
   
    }
}


//  blink method blinks an LED a given number of times
 
void blink(int thisPin, int howManyTimes) {
  // set the LED's pin as an output:
  pinMode(thisPin, OUTPUT);
  // blink the LED:
  for (int t = 0; t < howManyTimes; t++) {
    digitalWrite(thisPin, HIGH);
    delay(200);
    digitalWrite(thisPin, LOW);
    delay(200);
  } 
}

