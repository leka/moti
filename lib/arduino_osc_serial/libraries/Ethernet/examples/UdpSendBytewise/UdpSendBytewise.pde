#include <Ethernet.h>
#include <UdpBytewise.h>
/* UdpSendBytewise.pde: Example how to send packets over UDP using the UdpBytewise library
 * by assembling packets byte-by-byte
 * to check for received packets on Unix-ish setup, execute:
 * sudo tcpdump -A -ien0 "udp port 8000"
 * bjoern@cs.stanford.edu 12/29/2008 */

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

int i=0;

void setup() {
  Ethernet.begin(mac,ip,gw);
  UdpBytewise.begin(localPort);
}

void loop() {
  // this version of sendPacket sends a zero-terminated string.
  UdpBytewise.beginPacket(targetIp,targetPort);
  UdpBytewise.print("Hello, World! ");
  UdpBytewise.print(i++);
  UdpBytewise.endPacket();
  delay(1000);
}
