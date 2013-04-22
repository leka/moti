
void CheckLed()
  {


  }

void CheckAccelero()
{
  // -------------- accelEROMETER -----------------//
 Serial.println(" ");
  Serial.println(F("---- Accelerometer Checking ------ "));
accel.powerOn();  // fais tout bugger
delay(20);


// Place the ADXL345 in interrupt mode (activity)
Serial.print(F("Accelero"));
  delay(1);
  accel.set_bw(ADXL345_BW_12);
  Serial.print("BW_OK? ");
  delay(1);
  
  Serial.println(accel.status, DEC);
  delay(1);
       //accel.setInterrupt(ADXL345_INT_ACTIVITY_BIT,0); // disable Activity interrupt

     accel.setInterruptLevelBit(0); // if set to 0 sets the interrupts to active high
     accel.setActivityThreshold(ReveilEteint); //<< Sets the THRESH_ACT byte which holds the threshold value for detecting activity.(easy) 0<255 (hard)

     accel.setActivityX(1);
     accel.setActivityY(1);
     accel.setActivityZ(1);
     accel.setActivityAc(0); // In dc-coupled(0) operation, the current acceleration magnitude is compared directly with THRESH_ACT    
     accel.setLowPower(1);

     accel.setInterruptMapping(ADXL345_INT_ACTIVITY_BIT,ADXL345_INT1_PIN); // Set the mapping of an interrupt to pin 
     accel.setInterrupt(ADXL345_INT_ACTIVITY_BIT,1); // enable Activity interrupt

  //Put the ADXL345 into +/- 8G range 
  accel.setRangeSetting(8);
 // accel.setFullResBit(1);
 // gains[0] = 1;
 // gains[1] = 1;
 // gains[2] = 1;
 // accel.setAxisGains(gains);
 accel.setRate(25); 
 


 
 delay(20);

//---------------- DONE CHECKING ACCELERO -------------------

  
}






void sendAtCommand() {
  Serial.println("Sending command to the XBee");

  // send the command
  xbee.send(atRequest);

  // wait up to 5 seconds for the status response
  if (xbee.readPacket(5000)) {
    // got a response!

    // should be an AT command response
    if (xbee.getResponse().getApiId() == AT_COMMAND_RESPONSE) {
      xbee.getResponse().getAtCommandResponse(atResponse);

      if (atResponse.isOk()) {
        Serial.print("Command [");
        Serial.print(atResponse.getCommand()[0]);
        Serial.print(atResponse.getCommand()[1]);
        Serial.println("] was successful!");

        if (atResponse.getValueLength() > 0) {
          Serial.print("Command value length is ");
          Serial.println(atResponse.getValueLength(), DEC);

          Serial.print("Command value: ");
          
          for (int i = 0; i < atResponse.getValueLength(); i++) {
            Serial.print(atResponse.getValue()[i], HEX);
            Serial.print(" ");
          }

          Serial.println("");
        }
      } 
      else {
        Serial.print("Command return error code: ");
        Serial.println(atResponse.getStatus(), HEX);
      }
    } else {
      Serial.print("Expected AT response but got ");
      Serial.print(xbee.getResponse().getApiId(), HEX);
    }   
  } else {
    // at command failed
    if (xbee.getResponse().isError()) {
      Serial.print("Error reading packet.  Error code: ");  
      Serial.println(xbee.getResponse().getErrorCode());
    } 
    else {
      Serial.print("No response from radio");  
    }
  }
}


