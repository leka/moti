#include <Ethernet.h>
#include <UdpRaw.h>
/* UdpSendRaw.pde: Example how to send packets over UDP using the UdpRaw library 
 * to check for received packets on Unix-ish setup, execute:
 * sudo tcpdump -ien0 "udp port 8000"
 * bjoern@cs.stanford.edu 12/30/2008 */

/* ETHERNET CONFIGURATION 
 * ARDUINO: set MAC, IP address of Ethernet shield, its gateway,
 * and local port to listen on for incoming packets */
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //MAC address to use
byte ip[] = { 192, 168, 11, 200 }; // Arduino's IP address
byte gw[] = { 192, 168, 11, 1 };   // Gateway IP address
int localPort = 8888; //local port to listen on

/* TARGET: set this to IP/Port of computer that will receive
 * UDP messages from Arduino */
byte targetIp[] = { 192, 168, 11, 15};
int targetPort = 8000;

/* A binary packet we'll send to our target - can contain 0x00 */
byte packet[] = { 'h','e','l','l','o','\0','w','o','r','l','d','\0' };
int packetLen = 12;


void setup() {
  Ethernet.begin(mac,ip,gw);
  UdpRaw.begin(localPort);
}

void loop() {
  // this version of sendPacket sends a zero-terminated string.
  UdpRaw.sendPacket("hello, world.",targetIp,targetPort);
  delay(1000);
  
  // this version sends an arbitrary buffer with specified length;
  // buffer can contain '\0'
  UdpRaw.sendPacket(packet,packetLen,targetIp,targetPort);
  delay(1000);
}
