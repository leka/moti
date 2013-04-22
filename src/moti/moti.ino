// Attention, toute nouvelle carte doit au préalable se voir chargé le bootloader adapté sinon mauvaise config des fuse !


#include <ADXL345.h>
ADXL345 accel;

// TO DEFINE :
#define delaidodo 600 // delai avant que le robot ne s'endorme
#define ReveilEteint 100  // valeur 0 < 250; seuil de reveil de la carte Eteint -> Reveil
#define AllMax 200   // seuil max d'éclairage des led
#define bleuMax 180  
#define DeltaSignalInact 2   // seuil min pour detection inact
#define filter 150   // ralentir ou rendre plus rapide le robot, plus c'est grand moins il se calme vite
int CrazyActivity = 4;    // Diminuer pour que le robot s'exsite plus vite ! 

// Don't touch

#define mot_IN4 11
#define mot_IN2 10
#define mot_IN3 9
#define mot_IN1 13
#define DATAOUT 16//MOSI
#define DATAIN  14//MISO 
#define SPICLOCK  15//sck
#define SLAVESELECT 8//ss

#define RGB_1 5
#define RGB_2 6
#define RGB_3 12
#define RGB_2_EN 7
#define BUZZ 4

#define MicAnalog 1 //analog

int i, Micro, xyz[3], RGB[3], RGB_A[3], Moteur[2], Moteur_A[2];
int mic;
int debugson = 0;
unsigned long SampleTime=0;
 unsigned long savingbyte=0;      // 
byte flagSession=0;
byte SavedSession=0;
 unsigned long savingpage=0;      //  Saving
int last_xyz, last_micro;
 int Sleepy;
boolean remote_ctrl = false;
char buffer[4];
int direction_cmd = 0;
int speed_cmd=0;
int motor_nb_cmd=0;
int RGB_num=0;

uint8_t payload[] = { 'H', 'i' };// Create an array for holding the data you want to send.

// with Series 1 you can use either 16-bit or 64-bit addressing

// 16-bit addressing: Enter address of remote XBee, typically the coordinator
Tx16Request tx = Tx16Request(0x1874, payload, sizeof(payload));

// 64-bit addressing: This is the SH + SL address of remote XBee
//XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x4008b490);
// unless you have MY on the receiving radio set to FFFF, this will be received as a RX16 packet
//Tx64Request tx = Tx64Request(addr64, payload, sizeof(payload));

TxStatusResponse txStatus = TxStatusResponse();

// serial high
uint8_t shCmd[] = {'S','H'};
// serial low
uint8_t slCmd[] = {'S','L'};
// association status
uint8_t assocCmd[] = {'A','I'};

AtCommandRequest atRequest = AtCommandRequest(shCmd);

AtCommandResponse atResponse = AtCommandResponse();


// ----------------------------------------------------------------------
// ----------------------- SETUP ----------------------------------------
// ----------------------------------------------------------------------
void setup(){
  remote_ctrl= false;
  flagSession=0;
  savingbyte=0;
  SampleTime=0;
  Moteur[0]=0;
  Moteur[1]=0;
  Moteur_A[0]=0;
  Moteur_A[1]=0;
 	/* Initialize pinout */
  pinMode(mot_IN1, OUTPUT);
  pinMode(mot_IN2, OUTPUT);
  pinMode(mot_IN3, OUTPUT);
  pinMode(mot_IN4, OUTPUT);
  pinMode(RGB_1, OUTPUT);
  pinMode(RGB_2, OUTPUT);
  pinMode(RGB_3, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  pinMode(RGB_2_EN, OUTPUT);
  pinMode(DATAOUT, OUTPUT);
  pinMode(DATAIN, INPUT);
  pinMode(SPICLOCK, OUTPUT);
  pinMode(SLAVESELECT, OUTPUT);
    
      digitalWrite(mot_IN1,0);
  digitalWrite(mot_IN2,0);
digitalWrite(mot_IN3,0);
digitalWrite(mot_IN4,0);
digitalWrite(BUZZ,0);
digitalWrite(RGB_1,0);
digitalWrite(RGB_2,0);
digitalWrite(RGB_3,0);
digitalWrite(RGB_2_EN,0);
 Serial.begin(115200);
  Serial1.begin(9600);
  //xbee.setSerial(Serial1);
  xbee.begin(Serial1);
 delay(3);
 


  
CheckAccelero();

 accel.readAccel(xyz);
 CheckMem();
 
 
 

analogWrite(RGB_1,50);



    // Allumage led bleu : Reveil du robot en douceur avec un jolie fade 
    
    Serial.println(F("Reveil douceur"));
      for(int fadeValue = 0 ; fadeValue < bleuMax; fadeValue +=3) { 
      // sets the value (range from 0 to 255):
      analogWrite(RGB_1, fadeValue);  
      delay(10);                            
      } 
    

dataflash.BufferWrite(1, 0);
Serial.println(F("Debut comportement"));

Blinki(4);  // On excite un peu la boule en flashant les led à fond !

   RGB[0]=0;  // moins rouge
   RGB[1]=0;   // pas de changement du vert
   RGB[2]=bleuMax;   //plus bleu
       



}







// -------------- MAIN ------ -----------------//
void loop() {
  
  
    CheckConsole();
    
    // relevé des capteurs
    mic = analogRead(MicAnalog);   // micro
    accel.readAccel(xyz);          // accelerometre
     
    if(remote_ctrl == true)
    {
      // partie concernant la commande du robot par la Raspberry PI (RPI)
      
       
      

      
    }
    else
    {
       
      if(debugson)
      {
        
        Serial.println(mic);
      }
      
      
      // On check les variations des capteurs
      
       if (last_xyz == xyz[0])
       { // pas du tout de mouvement sur axe X
      // Serial.print(F("No Accel activity-Sleep"));
      // Serial.println(Sleepy);
         Sleepy++;
       }
       
       int DeltaSignal = xyz[0] - last_xyz;
       if (abs(DeltaSignal) < DeltaSignalInact ) 
       {
         //Serial.print(F("So small movement -Sleep"));
        // Serial.println(Sleepy);
          Sleepy++;
          RGB[0]-=5;  // moins rouge
          RGB[1]-=10;
          RGB[2]+=5;   //plus bleu
          
          
          Moteur[0]-=10;
          Moteur[1]-=10;
          
          
       }
       else
       {
         
           if (abs(DeltaSignal) > CrazyActivity ) 
           {
            // Serial.print(F("So crazy movement - Mad"));
            // Serial.println(Sleepy);
              Sleepy=0;
           RGB[0]+=30;  // moins rouge
          RGB[1]-=10;    // pas de changement du vert
          RGB[2]-=30;   //plus bleu
           }
          
           
       
       }
      
      // Déclencher roulement si le robot est exité
      if (Sleepy < 400)
      { // Si le robot etait trop au repos alors on ajoute un délai avant de le reveiller
          if(RGB[0]>(bleuMax-20))
          {
            Moteur[0]+=20;
            Moteur[1]+=20;
            
          }
      
      }
      
      if(Sleepy > delaidodo)
      { // Shut down the robot !
      Blinki(2);
      Serial.println(F("Bye bye "));
      delay(500);
      Shutdown();
      }
      /*
      if(mic < 739)
      {
      RGB[1]+=50;
      }
      */
       if(mic > 10)
      {
      RGB[1]+=50;
      }
      
      
      
      
      
      
  Serial.print(F(" RGB : "));
  Serial.print(RGB[0]);
  Serial.print(F(" - "));
  Serial.print(RGB[1]);
  Serial.print(F(" - "));
  
  Serial.print(RGB[2]);
  Serial.print(F(" Moteurs : "));
  Serial.print(Moteur[0]);
  Serial.print(F(" - "));
  
  Serial.print(Moteur[1]);
  Serial.print(F("  Sleepy : "));
  Serial.print(Sleepy);
  Serial.print(F("  AccX : "));
  Serial.print(xyz[0]);
  Serial.print(F("  Mic : "));
  Serial.print(mic);
  Serial.println(F("."));
  }
RGB_A[0] = constrain(RGB[0], 0, AllMax);  // evite de monter trop fort
RGB_A[1] = constrain(RGB[1], 0, AllMax);
RGB_A[2] = constrain(RGB[2], 0, AllMax);
RGB[0] = RGB_A[0];
RGB[1] = RGB_A[1];
RGB[2] = RGB_A[2];
analogWrite(RGB_2, RGB_A[0]); // met à jour les led
analogWrite(RGB_3, RGB_A[1]); 
analogWrite(RGB_1, RGB_A[2]);

Moteur_A[0] = constrain(Moteur[0], -255, 255);  
Moteur_A[1] = constrain(Moteur[1], -255, 255);  
Moteur[0]=Moteur_A[0];
Moteur[1]=Moteur_A[1];
if(Moteur[0]<0)
{ // recule
  analogWrite(mot_IN1,Moteur_A[0]); 
  analogWrite(mot_IN2,0);
}
else
{// avance
  analogWrite(mot_IN1,0); 
  analogWrite(mot_IN2,Moteur_A[0]);
}

if(Moteur[1]<0)
{ // recule
  analogWrite(mot_IN3,Moteur_A[1]); 
  analogWrite(mot_IN4,0);
}
else
{// avance
  analogWrite(mot_IN3,0); 
  analogWrite(mot_IN4,Moteur_A[1]);
}




delay(filter);  // filter
last_micro = mic;
last_xyz=xyz[0];

}


















// ------------------- Fonction ---------------------------------














void CheckRTC()
{
  

  
}




void PowerDown()
{
//I2C_Write(ADPS,TIMNG,0x01);
Serial.println(accel.getInterruptSource(),BIN);
}



void Blinki(byte valuer)
{
  for(int gro=0;gro<valuer;gro++)
  {
  digitalWrite(RGB_1,1);
  digitalWrite(RGB_2,1);
  digitalWrite(RGB_3,1);
     delay(50);
   digitalWrite(RGB_1,0);
   digitalWrite(RGB_2,0);
   digitalWrite(RGB_3,0);


    delay(50);
    
    

  }
}
int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}



















void EEPROM_writeLong(int ee, unsigned long value)
{
    byte* p = (byte*)(void*)&value;
    for (int i = 0; i < sizeof(value); i++)
	  EEPROM.write(ee++, *p++);
}

void writeLong(unsigned long value)
{
    byte* p = (byte*)(void*)&value;
    for (int i = 0; i < sizeof(value); i++)
	  spi_transfer(*p++);
}

void writeInt(int value)
{
    byte* p = (byte*)(void*)&value;
    for (int i = 0; i < sizeof(value); i++)
	  spi_transfer(*p++);
}

void writeByte(byte value)
{
    byte* p = (byte*)(void*)&value;
    for (int i = 0; i < sizeof(value); i++)
	  spi_transfer(*p++);
}

int ReadByte()
{
    byte value = 0;
    byte* p = (byte*)(void*)&value;
    for (int i = 0; i < sizeof(value); i++)
	  *p++ = spi_transfer(0xff);

    return value;
} 

int ReadInt()
{
    int value = 0;
    byte* p = (byte*)(void*)&value;
    for (int i = 0; i < sizeof(value); i++)
	  *p++ = spi_transfer(0xff);

    return value;
} 

unsigned long ReadLong()
{
    unsigned long value = 0;
    byte* p = (byte*)(void*)&value;
    for (int i = 0; i < sizeof(value); i++)
	  *p++ = spi_transfer(0xff);

    return value;
} 

unsigned long EEPROM_readLong(int ee)
{
    unsigned long value = 0;
    byte* p = (byte*)(void*)&value;
    for (int i = 0; i < sizeof(value); i++)
	  *p++ = EEPROM.read(ee++);
    return value;
} 

void Shutdown()
{
//I2C_Write(ADPS,TIMNG,0x01);
Serial.println(accel.getInterruptSource(),BIN);
}




