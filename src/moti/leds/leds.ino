/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int R = 10;
int G = 9;
int B = 8;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);  
  pinMode(B, OUTPUT);    
}

// the loop routine runs over and over again forever:
void loop() {
  
  digitalWrite(R, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(B, HIGH);
  delay(200);               
  digitalWrite(R, LOW);
  digitalWrite(G, LOW);
  digitalWrite(B, LOW);
  delay(200);               

}
