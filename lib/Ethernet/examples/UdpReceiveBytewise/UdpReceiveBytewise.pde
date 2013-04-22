#include <Ethernet.h>
#include <UdpBytewise.h>

/* UdpReceiveBytewise.pde: Example how to receive packets over UDP using UdpBytewise library
 * prints received packet to serial port
 * bjoern@cs.stanford.edu 12/30/2008
 */

/* ETHERNET SHIELD CONFIGURATION  
 * set MAC, IP address of Ethernet shield, its gateway,
 * and local port to listen on for incoming packets 
 */
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // MAC address to use
byte ip[] = { 192, 168, 11, 200 }; // Arduino's IP address
byte gw[] = { 192, 168, 11, 1 };   // Gateway IP address
unsigned int localPort = 8888; // local port to listen on

#define MAX_SIZE 32 // maximum packet size
byte packetBuffer[MAX_SIZE]; //buffer to hold incoming packet
int packetSize; // holds received packet size
byte remoteIp[4]; // holds recieved packet's originating IP
unsigned int remotePort; // holds received packet's originating port

int i;

/* SETUP: init Ethernet shield, start UDP listening, open serial port */
void setup() {
  Ethernet.begin(mac,ip,gw);
  UdpBytewise.begin(localPort);
  Serial.begin(38400); 
}
/* LOOP: wait for incoming packets and print each packet to the serial port */
void loop() {  
  // if there's data available, read a packet
  if(packetSize = UdpBytewise.available()) {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    
    UdpBytewise.getSenderIp(remoteIp);
    Serial.print("From IP ");
    for(i=0; i<4; i++) {
      Serial.print(remoteIp[i],DEC);
      if(i<3) Serial.print(".");
    }
    
    remotePort = UdpBytewise.getSenderPort();
    Serial.print(" Port ");
    Serial.println(remotePort); 
    
    Serial.println("Contents:");
    while(UdpBytewise.available()) {
      Serial.print(UdpBytewise.read(),BYTE);
    }
  }
  //wait a bit
  delay(10);  
}
