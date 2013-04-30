import processing.opengl.*;

PFont police;
String typing = "";
String saved = "";
float r=255, g=255, b=255, speed=0; 
int i=1,xPos = 1,l=0,f=0,quit;   
String lines[];      

float[] c = {0,0,0,0,0,0,0,0,0,1};
float[] x = new float[6];
float[] total = new float[6];
float[] maxi = {0,0,0,0,0,0};
float[] moy = new float[6];
int[] colors = {#b0d02e, #e94366, #51a5cb,#f08f33,#333333,#777777};

void setup () {
  size(1200, 600, OPENGL);    
  background(0);
  police = loadFont("Ubuntu.vlw");  
  if(saved!="")
  {
   
    lines = loadStrings(saved+".txt") ;
   
  
  smooth();
  
  ecriture();}
  
}

void draw()
{
  if(saved=="")
  {  background(255);
     fill(0); 
  text("Click in this applet and type. \nHit return to save what you typed.\nEnter the name of the file you want to open, without the \".txt\"  ", 25, 40);
  text(typing,25,130);
  text(saved,35,170);
  }
   if(saved!="")
  {
     ecriture();
  lecture(l);
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
l++;
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
 
 void lecture(int nbr)
 {
   
   if (nbr < lines.length ) {
     println(l);
     lines[nbr]=trim(lines[nbr]);
     c=float(split(lines[nbr], ","));
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

      
      
      
      
      if (xPos >= width/2+100) {
        xPos = 0;
          
      } 
      else {
        xPos++;
        xPos++;
   
      }
      
   }
 }
 }}
 
 void keyPressed()
 {
    quit = 0;
   if (key == BACKSPACE){
     
     typing=typing.substring(0,typing.length()-1);
   
   } 
   else if (key == ENTER || key == RETURN ) {
    saved = typing;
    typing = "";
     quit=1; 
     setup();
  } else {
    typing = typing + key; 
  }
   
   if(saved!="" && quit== 0)
  {
   println("X. moyenne : "+moy[0]*50+" valeur max : "+maxi[0]*50);
  println("Y. moyenne : "+moy[1]*50+" valeur max : "+maxi[1]*50);
  println("Z. moyenne : "+moy[2]*50+" valeur max : "+maxi[2]*50);
  println("deltaX. moyenne : "+moy[3]*50+" valeur max : "+maxi[3]*50);
  println("deltaY. moyenne : "+moy[4]*50+" valeur max : "+maxi[4]*50);
  println("deltaZ. moyenne : "+moy[5]*50+" valeur max : "+maxi[5]*50);
  print('\n');
    exit(); // Stops the program
  }
  quit=0;
 }
   
 
