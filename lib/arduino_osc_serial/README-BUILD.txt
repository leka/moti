Unfortunately, you cannot currently build all three UDP libraries simultaneously because of their different #includes. Specifically, if UdpString.cpp exists in your $ARDUINO/hardware/libraries/Ethernet directory, the examples for UdpRaw and UdpBytewise will not build, because their PDE files don't #include<WString.h>. 

Yes, this is confusing.

You know you are having this problem when the following error message appears during compilation:
"Couldn't determine program size: hardware/tools/avr/bin/avr-size: '/tmp/build50334.tmp/UdpReceiveBytewise.hex': No such file"

The workaround for now: Only copy one of the set of Udp*.h/.cpp files into $ARDUINO/hardware/libraries/Ethernet at a time and compile its examples. All example .pde files can co-exist in $ARDUINO/hardware/libraries/Ethernet/examples. You just can't compile them when all libraries are co-present in the /Ethernet directory.

This is also true for compiling arduino_osc_udp - you cannot have UdpString.h/.cpp in the Ethernet folder since arduino_osc_udp.pde uses UdpRaw.
