//Main function in piloting the device from a third party device

#include <Arduino.h>
#include <Wire.h>

#include "Moti.h"
#include "Sensors.h"

//#include "Stabilization.h"

//#include "Communication.h"

#include "DriveSystem.h"
#include "Motion.h"

#include "Adafruit_NeoPixel.h"
#define PIN            46
#define NUMPIXELS      20

#define	serialPort Serial1


// void changeLights(void){

// 	int i = 0;

// 	for (i=0; i<=3; i++){
// 		pixelStrip.setPixelColor(i,pixelStrip.Color(getValues(8),getValues(9),getValues(10)));
// 		pixelStrip.show();

// 	}
		
// 		for (i=4; i<=9; i++){
// 			pixelStrip.setPixelColor(i,pixelStrip.Color(getValues(14),getValues(15),getValues(16)));
// 		pixelStrip.show();

// 		}
	
// 		for (i=10; i<=15; i++){
// 			pixelStrip.setPixelColor(i,pixelStrip.Color(getValues(11),getValues(12),getValues(13)));
// 		pixelStrip.show();

// 		}

// 		for (i=16; i<=20; i++){
// 			pixelStrip.setPixelColor(i,pixelStrip.Color(getValues(5),getValues(6),getValues(7)));
// 		pixelStrip.show();
// 		}
// }

// void getValuesFromBluetooth(String _command)
// {
	
// 	//substring(from,to), from value is inclusive, to value is exclusive
// 	//serialPort.println("GVFB");
// 	//serialPort.print(_command);
// 	int k = 9;
	
// 	_values[0]=_command.substring(1,5).toInt();
// 	//serialPort.println(_values[0]);
// 	_values[1]=_command.substring(5,9).toInt();
// 	//serialPort.println(_values[1]);

// 	for(int i = 2; i < 17; i ++){
// 		_values[i]=_command.substring(k,k+3).toInt();
// 		k += 3;
// 		//serialPort.println(_values[i]);
// 	}
	
	


//}



void sendData(){


		serialPort.print(millis());
		serialPort.print(", ");

		serialPort.print(Sensors::getAccX());
		serialPort.print(", ");
		//serialPort.print(F("  Y: "));
		serialPort.print(Sensors::getAccY());
		serialPort.print(", ");
		//serialPort.print(F("  Z: "));
		serialPort.print(Sensors::getAccZ());
		serialPort.print(", ");

		//serialPort.print(F("  Yaw: "));
		serialPort.print(Sensors::getGyrY());
		serialPort.print(", ");
		//serialPort.print(F("  Pitch: "));
		serialPort.print(Sensors::getGyrP());
		serialPort.print(", ");
		//serialPort.print(F("  Roll: "));
		serialPort.print(Sensors::getGyrR());
		serialPort.print(", ");

		//serialPort.print(F("  Yaw deg: "));
		serialPort.print(Sensors::getGyrYDeg());
		serialPort.print(", ");
		//serialPort.print(F("  Pitch deg: "));
		serialPort.print(Sensors::getGyrPDeg());
		serialPort.print(", ");
		//serialPort.print(F("  Roll deg: "));
		serialPort.print(Sensors::getGyrRDeg());
		serialPort.print(", ");

		//serialPort.print(F("  Phi: "));
		serialPort.print(Sensors::getEulerPhi());
		serialPort.print(", ");
		//serialPort.print(F("  Theta: "));
		serialPort.print(Sensors::getEulerTheta());
		serialPort.print(", ");
		//serialPort.print(F("  Psi: "));
		serialPort.print(Sensors::getEulerPsi());

		serialPort.println();

}


void mainThread(){

	//Moti::init();
	Sensors::init();

	//Stabilization::init();

	//Bluetooth::init();
	//Moti::start();
	Sensors::start();
	//Bluetooth::start();

	//halInit();
	//chSysInit();



	//Stabilization::start();
	Adafruit_NeoPixel pixelStrip = Adafruit_NeoPixel(NUMPIXELS, PIN);
	pixelStrip.begin();

	// Bluetooth comInterface;

	// int i = 0;

	String command = "command";

	command.reserve(100);

	uint8_t _values[17] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	bool _GVFB = false;
	bool _changeLights = false;

	int k = 9;
	int i = 0;

	while (TRUE) {

		
		while(serialPort.available()){
			char caracter= (char)serialPort.read();
	       //chMtxLock(&_bluetoothComMutex);
	       //serialPort.print(caracter);
	       // ******* Be sure that what we get is the right value (especially because of noise)
	       if (caracter=='['){
	         command = "";
	         command += caracter; 
	       }
	       else if (caracter=='-'){
	         command += caracter;
	       }  
	       else if (caracter=='+'){
	         command += caracter;
	       }  
	       else if (caracter==','){
	         //command += caracter; 
	       }
	       else if (isdigit(caracter)) {
	         command += caracter;
	       }
	       else if (caracter==']'){
	         command += caracter;
	         if (command.charAt(0)=='[' && command.length()==55){
	         //if (command.charAt(0)=='['){
	           //command = command;
	           //getValuesFromBluetooth(command);
	         	_GVFB = TRUE;
	           //_command = "";
	           break;
	         	//serialPort.print(command);
	         }
	         else{
   	           
   	           serialPort.println("ErrorCommandLength");
	           command = "";
	           //serialPort.print(command);
	           break;
	         }
	        }
   		}



   	if(_GVFB){
		_values[0]=command.substring(1,5).toInt();
		serialPort.println(_values[0]);
		_values[1]=command.substring(5,9).toInt();
		serialPort.println(_values[1]);

		for(int i = 2; i < 17; i ++){
			_values[i]=command.substring(k,k+3).toInt();
			k += 3;
			serialPort.println(_values[i]);
		}

		k = 9;
		_GVFB = false;

		_changeLights = TRUE;
   	}


   	if(_changeLights = TRUE){

   		for (i=0; i<=3; i++){
		pixelStrip.setPixelColor(i,pixelStrip.Color(_values[8],_values[9],_values[10]));
		pixelStrip.show();

		}
		
		for (i=4; i<=9; i++){
			pixelStrip.setPixelColor(i,pixelStrip.Color(_values[14],_values[15],_values[16]));
		pixelStrip.show();

		}
	
		for (i=10; i<=15; i++){
			pixelStrip.setPixelColor(i,pixelStrip.Color(_values[11],_values[12],_values[13]));
		pixelStrip.show();

		}

		for (i=16; i<=20; i++){
			pixelStrip.setPixelColor(i,pixelStrip.Color(_values[5],_values[6],_values[7]));
		pixelStrip.show();
		}

		_changeLights = FALSE;

   		}
	


   		//sendData();


		waitMs(25);


	}

}




void loop(){}

int main(void){

	init();

	serialPort.begin(115200);

	Wire.begin();
	delay(500);

	chBegin(mainThread);

	while(1);

	return 0;
}