import processing.opengl.*;
import processing.serial.*;


PrintWriter output;
String timestamp = year() +"-"+ nf(month(),2) +"-"+ nf(day(),2) + "-"  + nf(hour(),2) + "-"+nf(minute(),2) +"-"+ nf(second(),2)+"-";
Serial myPort;        // The serial port
PFont police;
float r=255, g=255, b=255, speed=0; 
int i=1,xPos = 1;         

float[] c = {0,0,0,0,0,0,0,0,0,1};
float[] x = new float[6];
float[] total = new float[6];
float[] maxi = {0,0,0,0,0,0};
float[] moy = new float[6];
int[] colors = {#b0d02e, #e94366, #51a5cb,#f08f33,#333333,#777777};
void setup () {
  output = createWriter("../../../log/"+timestamp+"data.txt");
  size(1200, 600, OPENGL);    
  background(0);
  smooth();
  police = loadFont("Ubuntu.vlw");  
  ecriture();

  myPort = new Serial(this, Serial.list()[0], 9600);
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
  
}
void draw()
{
  if (c.length >=10) {
    
    speed+=abs(c[9]/250);
    stroke(r+10,g,b+10);
    fill(r,g,b); 
    lights();
    translate(width/2+width/4,height/2);
    rotateX(-radians(speed));
    rotateZ(radians(90));
    sphere(180);
    rotateZ(-radians(90));
    rotateX(radians(speed));
  
    translate(-width/2-width/4,-height/2);
  
    for(int j = 0; j < 6; j++)
        {
          //x[j] = c[j]/30;
          stroke(colors[j]);
          line(xPos, (600-(5-j)*100), xPos, (600-(5-j)*100) - x[j]);
                
        }
    if(xPos >= width/2+100)
    {
      background(0);
      ecriture();  
    }
  }    
}
   
  
 
void serialEvent(Serial myPort) { 
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');
 
  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);
    
    c = float(split(inString, ","));
    
    i++;
    if (c.length >=9) {
    
      for(int j = 0; j < 6; j++)
      {
        x[j] = c[j]/30;
        total[j]=+x[j];
        moy[j]=total[j]/i;
        if(maxi[j]<-c[j]){maxi[j]=-c[j];}

        
      }
      
        
      r=c[6];
      g=c[7];
      b=c[8];

      
      output.println(c[0]+","+c[1]+","+c[2]+","+c[3]+","+c[4]+","+c[5]+","+c[6]+","+c[7]+","+c[8]+","+c[9]);
      
      
      
      
      if (xPos >= width/2+100) {
        xPos = 0;
          
      } 
      else {
        xPos++;
        xPos++;
   
      }
   }
   }
}

void ecriture()
 {

fill(255); 
   textFont(police,48);
   text("X", 50, 70);
   text("Y", 50, 170);
   text("Z", 50, 270);
   text("deltaX", 50, 370);
   text("deltaY", 50, 470);
   text("deltaZ", 50, 570);
   
 
 }
 
 void keyPressed()
 {
  println("X. moyenne : "+moy[0]*50+" valeur max : "+maxi[0]*50);
  println("Y. moyenne : "+moy[1]*50+" valeur max : "+maxi[1]*50);
  println("Z. moyenne : "+moy[2]*50+" valeur max : "+maxi[2]*50);
  println("deltaX. moyenne : "+moy[3]*50+" valeur max : "+maxi[3]*50);
  println("deltaY. moyenne : "+moy[4]*50+" valeur max : "+maxi[4]*50);
  println("deltaZ. moyenne : "+moy[5]*50+" valeur max : "+maxi[5]*50);
  print('\n');
    output.flush(); // Writes the remaining data to the file
    output.close(); // Finishes the file  
    saveFrame(timestamp+"graphs.png");  
    exit(); // Stops the program
 }
 
