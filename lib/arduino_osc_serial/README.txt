This package contains two Firmwares (arduino_osc_serial and arduino_osc_udp) that enable sending and receiving of OSC messages on Arduino using either the serial port or UDP with the Arduino Ethernet shield. The protocol is described in the header of each file.

To enable UDP communication, this package also contains additions to Arduino's Ethernet library that enable sending and receiving of UDP packets (as of Arduino0012, the library only supports TCP natively).

There are three different UDP libraries included:

UdpBytewise mimics byte-by-byte reading and writing of packets as used in the Serial and Wire libraries of Arduino. This library has a small footprint and offers continuity with existing programming models, but it has some limitations as packet boundaries are ignored by the read function. While assembling packets, when the maximum packet buffer length is exceeded, users can choose to either truncate the packet or auto-split into multiple packets.

UdpString uses Tom Igoe/Hernando Barragan's WString library for packets. This library offers high-level abstractions that preserve packet boundaries. However, it is currently rather large and does not leave much space for the user's sketch on ATmega168. The library also doesn't lend itself to dealing with binary strings as many underlying functions depend on strcpy/strcmp/etc which all assume zero-terminated strings. A nice feature: if incoming messages exceed String capacity, the String is automatically resized to prevent overflow. The package contains a redistribution of WString for this library.

UdpRaw is a thin wrapper around the UDP functions offered by the socket.c file in the Ethernet library - it uses raw byte buffers to send/receive packets. This library has the smallest footprint but is most challenging to use for novices. If incoming packets exceed buffer capacity, the packets are truncated to fit into the buffer and an error code is returned to alert the application.

Examples for sending/receiving packets for each of these three libraries are included in /libraries/Ethernet/examples/.

Finally, there are examples to test arduino_osc communication in PureData and Python. These examples may need additional modules/extensions to run on a fresh system. Consult the comments in the files themselves.

===============================================================================
Files:
arduino_osc_serial.pde - Firmware for sending and receiving OSC packages over the Arduino serial port

arduino_osc_udp.pde - Firmware for sending and receiving OSC packages over UDP using the Arduino ethernet shield. Relies on UDP library in files /libraries/Ethernet/UdpRaw.h/.cpp

./examples/pd: - PureData (pd) example patches to test arduino_osc firmwares
arduino_osc.pd - Patch that communicates with arduino_osc_serial.pde firmware
arduino_osc_udp.pd - Patch that communicates with arduino_osc_udp.pde firmware
arduino_osc_udp_widgets.pd - Subpatch containing UI widgets for arduino_osc_udp.pd. Don't open.
arduino_osc_widgets.pd - Subpatch containing UI widgets for arduino_osc.pd. Don't open.

./examples/python: - Python scripts to test arduino_osc firmwares
test_udp_latency.py - Run repeated message echoing loops to test roundtrip latency
test_udp_throughput.py - Receive analog sensor data from Arduino to test throughput

./libraries/Ethernet: - Augmentations to Arduino's Ethernet library that enable UDP communication
UdpBytewise.cpp - Library for reading/writing UDP packets byte-by-byte (like Serial) 
UdpBytewise.h
UdpRaw.cpp - Library for reading/writing UDP packets using char[] buffers
UdpRaw.h
UdpString.cpp - Library for reading/writing UDP packets using Tom Igoe/Hernando Barragan's WString objects
UdpString.h


./libraries/Ethernet/examples: - Arduino firmware examples to send/receive UDP packets for each of the three library approaches
UdpReceiveBytewise
UdpReceiveRaw
UdpReceiveString
UdpSendBytewise
UdpSendRaw
UdpSendString

./libraries/String: re-distribution of Igoe/Barragan's WString library needed by UdpString.h/.cpp
WString.cpp
WString.h
===============================================================================
bjoern@cs.stanford.edu 12/30/2008

