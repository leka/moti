
/*
THIS FUNCTION WRITES A BYTE TO THE I2C BUS
*/

void I2C_Write(byte address,byte command,byte data){  

 Wire.beginTransmission(address);
 Wire.write(command);
 Wire.write(data);
 Wire.endTransmission(); 
 
}

