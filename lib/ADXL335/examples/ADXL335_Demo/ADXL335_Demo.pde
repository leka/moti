/*
ADXL335 Accelerometer Demo
Derek Chafin
September 22, 2011
Public Domain

Demonstrates how to use the ADXL335 library

Pin Connections:

analog 0: connected to x-axis
analog 1: connected to y-axis
analog 2: connected to z-axis
aref: connected to +3.3V
*/

#include <ADXL335.h>

const int pin_x = A0;
const int pin_y = A1;
const int pin_z = A2;
const float aref = 3.3;
ADXL335 accel(pin_x, pin_y, pin_z, aref);

void setup()
{
  Serial.begin(9600);
  
  Serial.println("X,\tY,\tZ,\tRho,\tPhi,\tTheta");
}

void loop()
{
  //this is required to update the values
  accel.update();
  
  //this tells us how long the string is
  int string_width;

  float x;
  float y;
  float z;
  
  //for these variables see wikipedia's
  //definition of spherical coordinates
  float rho;
  float phi;
  float theta;  
  
  x = accel.getX();
  y = accel.getY();
  //if the project is laying flat and top up the z axis reads ~1G
  z = accel.getZ();
  rho = accel.getRho();
  phi = accel.getPhi();
  theta = accel.getTheta();
  
  Serial.print(formatFloat(x, 2, &string_width));
  Serial.print(",\t");
  Serial.print(formatFloat(y, 2, &string_width));
  Serial.print(",\t");
  Serial.print(formatFloat(z, 2, &string_width));
  Serial.print(",\t");
  Serial.print(formatFloat(rho, 2, &string_width));
  Serial.print(",\t");
  Serial.print(formatFloat(phi, 2, &string_width));
  Serial.print(",\t");
  Serial.print(formatFloat(theta, 2, &string_width));
  Serial.println("");
  
  delay(1000);
}

//this function was taken from my format float library
String formatFloat(double value, int places, int* string_width)
{
  //if value is positive infinity
  if (isinf(value) > 0)
  {
    return "+Inf";
  }
    
  //Arduino does not seem to have negative infinity
  //keeping this code block for reference
  //if value is negative infinity
  if(isinf(value) < 0)
  {
    return "-Inf";
  }
  
  //if value is not a number
  if(isnan(value) > 0)
  {
    return "NaN";
  }
  
  //always include a space for the dot
  int num_width = 1;

  //if the number of decimal places is less than 1
  if (places < 1)
  {
    //set places to 1
    places = 1;
    
    //and truncate the value
    value = (float)((int)value);
  }
  
  //add the places to the right of the decimal
  num_width += places;
  
  //if the value does not contain an integral part  
  if (value < 1.0 && value > -1.0)
  {
    //add one for the integral zero
    num_width++;
  }
  else
  {

    //get the integral part and
    //get the number of places to the left of decimal
    num_width += ((int)log10(abs(value))) + 1;
  }
  //if the value in less than 0
  if (value < 0.0)
  {
    //add a space for the minus sign
    num_width++;
  }
  
  //make a string the size of the number
  //plus 1 for string terminator
  char s[num_width + 1]; 
  
  //put the string terminator at the end
  s[num_width] = '\0';
  
  
  //initalize the array to all zeros
  for (int i = 0; i < num_width; i++)
  {
    s[i] = '0';
  }
  
  //characters that are not changed by 
  //the function below will be zeros
  
  //set the out variable string width
  //lets the caller know what we came up with
  *string_width = num_width;
  
  //use the avr-libc function dtosrtf to format the value
  return String(dtostrf(value,num_width,places,s));  
}