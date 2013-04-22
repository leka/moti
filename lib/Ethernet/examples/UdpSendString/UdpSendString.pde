#include <Ethernet.h>
#include <UdpString.h>
#include <WString.h>

/* UdpSendString.pde: Example how to send packets over UDP using the String library 
 * to check for received packets on Unix-ish setup, execute:
 * sudo tcpdump -A -ien0 "udp port 8000"
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

/* Strings hold the packets we want to send */
String asciiString;
String binaryString(4); // if we want to send non-ASCII, we have to provide a capacity for the String

void setup() {
  Ethernet.begin(mac,ip,gw);
  UdpString.begin(localPort);
  
  asciiString = "Hello, World";
  
  binaryString.getBytes()[0]=0x00;
  binaryString.getBytes()[1]=0x01;
  binaryString.getBytes()[2]=0x02;
  binaryString.getBytes()[3]=0x03;
}

void loop() {
  // send a normal, zero-terminated string.
  UdpString.sendPacket(asciiString,targetIp,targetPort);
  delay(1000);
  
  // sends a binary string that can contain 0x00 in the middle
  // you have to specify the length;
  UdpString.sendPacket(binaryString,binaryString.capacity(),targetIp,targetPort);
  delay(1000);
}
