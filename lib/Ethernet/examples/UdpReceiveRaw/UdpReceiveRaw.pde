#include <Ethernet.h>
#include <UdpRaw.h>

/* UdpReceiveRaw.pde: Example how to receive packets over UDP using UdpRaw library
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
int localPort = 8888; // local port to listen on

#define MAX_SIZE 32 // maximum packet size
byte packetBuffer[MAX_SIZE]; //buffer to hold incoming packet
int packetSize; // holds received packet size
byte remoteIp[4]; // holds recvieved packet's originating IP
unsigned int remotePort; // holds received packet's originating port

int i;

/* SETUP: init Ethernet shield, start UDP listening, open serial port */
void setup() {
  Ethernet.begin(mac,ip,gw);
  UdpRaw.begin(localPort);
  Serial.begin(38400); 
}
/* LOOP: wait for incoming packets and print each packet to the serial port */
void loop() {  
  
  // if there's data available, read a packet
  if(UdpRaw.available()) {
    packetSize = UdpRaw.readPacket(packetBuffer,MAX_SIZE,remoteIp,(uint16_t *)&remotePort);
      
      Serial.print("Received packet of size ");
      Serial.println(abs(packetSize));

      Serial.print("From IP ");
      for(i=0; i<3; i++) {
        Serial.print(remoteIp[i],DEC);
        Serial.print(".");
      }
      Serial.print(remoteIp[3],DEC);
      
      Serial.print(" Port ");
      Serial.println(remotePort); 
      
      if(packetSize < 0) {
        // if return value <0 the packet was truncated to fit into our buffer
        Serial.print("ERROR: Packet was truncated from ");
        Serial.print(packetSize*-1);
        Serial.print(" to ");
        Serial.print(MAX_SIZE);
        Serial.println(" bytes.");
      }
      
      Serial.println("Contents:");
      for(i=0; i<min(MAX_SIZE,abs(packetSize)); i++) {
        Serial.print(packetBuffer[i],BYTE);
      }
      Serial.println("");
      
  }
  //wait a bit
  delay(10);  
}
