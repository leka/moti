
void CheckLed()
{


}

void CheckMem()
{
  
  
  
  
 Serial.println(" ");
  Serial.println("---- Memory Checking ------ ");
uint8_t        status;
  ATD45DB161D::ID id;
  
  
  // Initialize dataflash 
  dataflash.Init();
    
  delay(10);
  
  // Read status register 
  status = dataflash.ReadStatusRegister();
  
  // Read manufacturer and device ID 
  dataflash.ReadManufacturerAndDeviceID(&id);



  // Display status register 
  Serial.print(F("Status register :"));
  Serial.print(status, BIN);
  Serial.print('\n');

  // Display manufacturer and device ID 
  Serial.print(F("Manufacturer ID (00011111):\n"));  // Should be 00011111
  Serial.print(id.manufacturer, BIN);
  Serial.print('\n');

  Serial.print(F("Device ID (part 1) (00011111):\n")); // Should be 00011111
  Serial.print(id.device[0], BIN);
  Serial.print('\n');

  Serial.print(F("Device ID (part 2)(00000000)  :\n")); // Should be 00000000
  Serial.print(id.device[1], BIN);
  Serial.print('\n');

  Serial.print(F("Extended Device Information String Length  (00000000):\n")); // 00000000
  Serial.print(id.extendedInfoLength, BIN);
  Serial.print('\n');
  

  //dataflash.DeepPowerDown();
  
      
  
// ------------- CHECK MEMORY DONE ----// 
  
}

void TestMemory()
{
  delay(1);
}





void CheckConsole()
{
 
  // ------------ PORT USB ---------- //
  
   if (Serial.available()) {

    int val = Serial.read();
    switch (val){
   
  case 'H' :
      Serial.println(F("---------Help--------")); //
      Serial.println(F("A : Affiche Accelero X"));
      Serial.println(F("B : Fade Blue"));
      Serial.println(F("C : Affiche le son"));
      Serial.println(F("D : Test moteurs"));
      Serial.println(F("E : Blink LEDS"));
      Serial.println(F("F : Debug Micro"));
      Serial.println(F("G : Strong Green"));
      Serial.println(F("H : Help"));
      Serial.println(F("J : Shutdown"));
      Serial.println(F("K : Remote control from RPI"));
      Serial.println(F("L : Stop remote control"));
      Serial.println(F("N : Motor + Number + direction +speed (ex : N00123, mot0,sens 0,vit 123) "));
      Serial.println(F("Q : LED + Number ex O0123 : led R set to 123"));
      Serial.println(F("T :Test Xbee"));
            Serial.println(F("U : Test AT command of XBEE"));

      Serial.println(F("R : Fade Red"));
      Serial.println(F("S : Reset"));
  

      break;
            
      case 'U' :      
             // get SH
      sendAtCommand();
      
      // set command to SL
      atRequest.setCommand(slCmd);  
      sendAtCommand();
    
      // set command to AI
      atRequest.setCommand(assocCmd);  
      sendAtCommand();
      break;
            
            
      case 'T' :
              Serial.println(F("T :Test Xbee"));
              xbee.send(tx);
             
             
      break;
            
            
       case 'Q' :
       
        buffer[0]=0;
      buffer[1]=0;
      buffer[2]=0;
      buffer[0] =  Serial.read();  // recupère la led a allumer
      RGB_num = atoi(buffer);
     
       
       for(i=0; i<3; i++)
	    {
	    buffer[i] = Serial.read();
	    }
         RGB[RGB_num] = atoi(buffer);    // récupère la puissance de la couleur
        
            break;

      
      
       case 'N' :
      buffer[0]=0;
      buffer[1]=0;
      buffer[2]=0;
      buffer[0] =  Serial.read();  // recupère le moteur à commander (0 ou 1 )
      motor_nb_cmd = atoi(buffer);
      
      buffer[0]=0;
      buffer[1]=0;
      buffer[2]=0;
      buffer[0] =  Serial.read();  // recupère le sens (0 ou 1 )
      direction_cmd = atoi(buffer);
       
       
       for(i=0; i<3; i++)
	    {
	    buffer[i] = Serial.read();
	    }
        speed_cmd = atoi(buffer);    // récupère la vitesse du dit moteur
        
        if(direction_cmd == 0)
        {
          Moteur[motor_nb_cmd]= 0 + speed_cmd;
        }
        else
        {
          Moteur[motor_nb_cmd]= 0 - speed_cmd;
        }
        
        Serial.println(F("OK"));

       break;
      
      
      
      
      case 'S' :
      Serial.println(F("Setup"));
      delay(1);
      setup();
      break;
      
         case 'K' :
      Serial.println(F("Remote control from RPI now !"));
      delay(1);
      remote_ctrl = true;
      break;
      case 'L' :
      Serial.println(F("Stop remote ctrl"));
      delay(1);
      remote_ctrl = false;
      break;
      case 'D' :
     delay(1);
     Serial.println(F("Moteur 1"));
  digitalWrite(mot_IN1,0);
  digitalWrite(mot_IN2,1);
  delay(200);
  
  digitalWrite(mot_IN1,1);
  digitalWrite(mot_IN2,0);
  delay(200);
    digitalWrite(mot_IN1,0);
  digitalWrite(mot_IN2,0);
    Serial.println(F("Moteur 2"));
  digitalWrite(mot_IN3,0);
  digitalWrite(mot_IN4,1);
  delay(200);
  
  digitalWrite(mot_IN3,1);
  digitalWrite(mot_IN4,0);
  delay(200);
    digitalWrite(mot_IN3,0);
  digitalWrite(mot_IN4,0);
      break;

   case 'A' :
      Serial.println(F("Accelero"));
        // Get Acceleration
          accel.readAccel(xyz);
         Serial.println(xyz[1]);
    break;
    
    case 'C' :
      Serial.println(F("Son"));
       mic = analogRead(MicAnalog);
         Serial.println(mic);
    break;
    
    case 'R' :
    Serial.println(F("Fade"));
      for(int fadeValue = 0 ; fadeValue < 140; fadeValue +=5) { 
      // sets the value (range from 0 to 255):
      analogWrite(RGB_2, fadeValue);  
      delay(10);                            
      } 
      digitalWrite(RGB_2,0);
     break;
     
      case 'G' :
    Serial.println(F("Strong"));
    digitalWrite(RGB_3,1);
     delay(200);
     digitalWrite(RGB_3,0);
     break;
     
      case 'B' :
    Serial.println(F("Fade"));
      for(int fadeValue = 0 ; fadeValue < 140; fadeValue +=5) { 
      // sets the value (range from 0 to 255):
      analogWrite(RGB_1, fadeValue);  
      delay(10);                            
      } 
      digitalWrite(RGB_1,0);
     break;
     
     case 'P' :
     CrazyActivity +=1;
     Serial.println(CrazyActivity);
     break;
     
     case 'M' :
     CrazyActivity -=1;
     Serial.println(CrazyActivity);
     break;
     
      case 'E' :
      Serial.println(F("Warning : Strong light is going to arrive!"));
      delay(500);
      
      Blinki(3);
      break;
      
      case 'F' :
      Serial.println(F("Debug micro Forever"));
      debugson = 1;
      break;
      
      case 'J' :
      Serial.println(F("Power down !"));
      delay(10);
      Shutdown();
      break;
      

      
       
       
      default :
       Serial.println(F("what ? Press H for Help"));
      
    }
   }
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


