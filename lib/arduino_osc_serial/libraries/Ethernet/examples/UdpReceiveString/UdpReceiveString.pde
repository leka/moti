#include <Ethernet.h>
#include <UdpString.h>
#include <WString.h>
/* UdpReceiveString.pde: Example how to receive packets over UDP using the UdpString library
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

String packet(32); //packet can be max 32 bytes long
byte remoteIp[4]; // holds recvieved packet's originating IP
unsigned int remotePort[1]; // holds received packet's originating port

int i;

/* SETUP: init Ethernet shield, start UDP listening, open serial port */
void setup() {
  Ethernet.begin(mac,ip,gw);
  UdpString.begin(localPort);
  Serial.begin(38400); 
}

/* LOOP: wait for incoming packets and print each packet to the serial port */
void loop() {  

  // if there's data available, read a packet
  if(UdpString.available()) {
    int packetSize = UdpString.readPacket(packet,remoteIp,remotePort);

    Serial.print("Received packet of size ");
    Serial.println(packetSize);

    Serial.print("From IP ");
    for(i=0; i<3; i++) {
      Serial.print(remoteIp[i],DEC);
      Serial.print(".");
    }
    Serial.print(remoteIp[3],DEC);

    Serial.print(" Port ");
    Serial.println(remotePort[0]); 

    Serial.println("Contents:");
    Serial.println(packet);


  }
  //wait a bit
  delay(10);  
}
