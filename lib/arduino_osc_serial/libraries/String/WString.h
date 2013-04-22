/*
  WString.h - String library for Wiring & Arduino
  Based on Tom Igoe's TextString original C++ implementation
  Copyright (c) 2006-07 Hernando Barragan.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef String_h
#define String_h

#include "WProgram.h"
#include <string.h>
#include <ctype.h>

class String
{
  public:
    String(const int length = 16);
    String(const char* bytes);
    String(const String &str);

    const String & operator = ( const String &rightStr );
    const String & operator = ( const char*);

    const String & operator +=( const String &rightStr );
    const String & operator +=( const char );
    const String & operator +=( const char* bytes);
    const String & operator +=( long n );
    const String & operator +=( int n );
    
    const String & append(char);
    const String & append(char *str);
    const String & append(int n, int base);
    const String & append(long n, int base);
    const String & append(int n);
    const String & append(long n);
    const String & append(const String &str);

    //friend String operator +(const String &s1, char c2);
    //friend String operator +(const String &s1, const String &s2);
    //friend String operator +(const String &s1, const char *s2);
    //friend String operator +(const char *s1, const String &s2);
    //friend String operator +(char c1, const String &s2);
    //friend String operator +(const String &s1, int n);
    //friend String operator +(int n, const String &s1);
    //friend String operator +(const String &s1, long n);
    //friend String operator +(long n, const String &s1);

    char charAt(int index);
    void setCharAt(int index, char ch);

    //const String & concat(const String &str);

    boolean equals(char* str);
    boolean equals(const String &str);
    boolean contains(char* str);
    byte* getBytes();
    void setArray(const char* bytes);
    int indexOf(int ch);
    int indexOf(const String &str);
    int indexOf(char ch, int fromIndex);
    int indexOf(const String &str, int fromIndex);
    int length() {return _length;}
    int capacity() {return _capacity;}
    boolean startsWith(const String &prefix);
    boolean startsWith(const String &prefix, int offset);
    String substring(int beginIndex);
    String substring(int beginIndex, int endIndex);

    //static String valueOf(int n, int base);
    //static String valueOf(long n, int base);

    static char* valueOf(int n, int base);
    static char* valueOf(long n, int base);

    const char*	cstr() const { return _array; }
    operator char*() { return _array; }

    char* toCharArray();
    void trim(void);
    boolean endsWith(const String &suffix);
    void replace(char oldChar, char newChar);
    void toLowerCase();
    void toUpperCase();
    void clear(void);


    char *_array;       // the actual char array
    uint16_t _length;   // the string length
    uint16_t _capacity; // the array length 

	String version(void);	// the version number


  private:

};

#endif
