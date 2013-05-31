#include <Arduino.h>
#include <Wire.h>

#include <CommunicationUtils.h>
#include <DebugUtils.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <FreeSixIMU.h>



FreeSixIMU myaccel = FreeSixIMU();

int value[3];

void setup() {

  delay(1000);

  Serial.println("Hello");
  delay(500);
  Serial.begin(9600);
  Serial.println("Serial OK");
  delay(500);
  Wire.begin();
  myaccel.init();
  Serial.println("Accel OK");
  Serial.println("Begining Loop");

}

void loop() {
  // put your main code here, to run repeatedly:

  myaccel.getRawValues(value);

  Serial.print("Value 1 :");
  Serial.print(value[0]);

  Serial.print(" Value 2 :");
  Serial.print(value[1]);

  Serial.print(" Value 3 :");
  Serial.println(value[2]);

  delay(50);
}