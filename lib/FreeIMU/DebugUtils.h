/*
DebugUtils.h - Simple debugging utilities.
Copyright (C) 2011 Fabio Varesano <fabio at varesano dot net>

Ideas taken from:
http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1271517197

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "Serial.hpp"

#ifndef DEBUGUTILS_H
#define DEBUGUTILS_H

#ifdef DEBUG_V
  #include <WProgram.h>
  #define DEBUG_PRINT(str)    \
    serial.print(millis());     \
    serial.print(": ");    \
    serial.print(__PRETTY_FUNCTION__); \
    serial.print(' ');      \
    serial.print(__FILE__);     \
    serial.print(':');      \
    serial.print(__LINE__);     \
    serial.print(' ');      \
    serial.println(str);
#endif

#ifdef DEBUG
  #define DEBUG_PRINT(str) \
    serial.println(str);
#endif

#ifndef DEBUG_PRINT
  #define DEBUG_PRINT(str)
#endif

/*
int availableMemory() {
  int size = 2048; // Use 2048 with ATmega328
  byte *buf;

  while ((buf = (byte *) malloc(--size)) == NULL)
    ;

  free(buf);

  return size;
}
*/


#endif
