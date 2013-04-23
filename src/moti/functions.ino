
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








