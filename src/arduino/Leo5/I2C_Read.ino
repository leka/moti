
/*
THIS FUNCTION READS ONE OR TWO BYTES FROM THE I2C BUS
*/


int I2C_Read(byte address,byte command,byte n){  
  int data_;
  int DATA;  
  
  Wire.beginTransmission(address);
  Wire.write(command);
  Wire.endTransmission();
  Wire.requestFrom(address,n);
  while(Wire.available())
  {
   DATA = Wire.read();
   
    
   
  }
  return(DATA);
}

