/*
  WString.cpp - String library for Wiring & Arduino
  version 0.4
  
  Based on Tom Igoe's TextString original C++ implementation
  Copyright (c) 2006-08 Hernando Barragan.  All right reserved.

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

#include <stdlib.h>
#include "WProgram.h"
#include "WString.h"

   


String::String(const int length)
{
  _array = (char*)malloc(length+1);
  _capacity = length;
  _length = 0;   

  clear();  
}


String::String(const char* bytes)
{
  if(bytes == NULL)
    bytes= "";
  _length = strlen(bytes);
  //if (_capacity < _length) {
  _capacity = _length;
  //  free(_array);
  _array = (char*)malloc(_length+1);
  //}
     
  clear();  
  setArray(bytes);
}


String::String(const String &str)
{
  _length = _capacity = str._length;
  _array = (char*)malloc(_length + 1);
  clear();
  setArray(str._array);
}


// Public Methods
// Functions available in Wiring sketches, and other libraries


const String & String::operator=( const String &rightStr )
{
  if ( this == &rightStr )
    return *this;

  if ( rightStr._length > _capacity )
  {
    free(_array);
    _capacity = rightStr._length;
    _array = (char*)malloc(_capacity+1);
  }

  _length = rightStr._length;
  clear();
  setArray( rightStr._array );

  return *this;
}


const String & String::operator=(const char* bytes) {
  //return *this = String(bytes);
  if(bytes == NULL)
    bytes = ""; 
  _length = strlen(bytes);
  if (_length > _capacity) {
    _capacity = _length;
    free(_array);
    _array = (char*)malloc(_length+1);
  }
  clear();
  setArray(bytes);
  
  return *this;
} 


const String & String::operator+=( const char* bytes) {
  if(bytes == NULL)
    bytes = "";
  _length += strlen(bytes);
  if ( _length > _capacity )
  {
    char *tmp = _array;
    _capacity = _length;
    _array = (char *) malloc (_length + 1);
    setArray(tmp);
    //strcpy( _array, tmp );
    free(tmp);
  }
  strcat( _array, bytes );
  _array[_length] = '\0';

  return *this;
} 


const String & String::operator+=( const char ch )
{
  if ( _length == _capacity ) {
    char *tmp = _array;
    _capacity = ++_capacity*2;
    _array = (char*)malloc(_capacity + 1);
    setArray(tmp);
    free(tmp);
  } 

  _array[ _length++ ] = ch;
  _array[ _length ] = '\0';

  return *this;
}



const String & String::operator+=(int n) 
{
  append((long)n, 10);

  //char *t = valueOf((long)n, 10);
  //*this+=t; 
  //free(t);

  return *this;

}



const String & String::operator+=(long n)
{
  append(n, 10);
 
  //char *t = valueOf(n, 10);
  //*this+=t; 
  //free(t);

  return *this;
}


const String & String::operator+=( const String &str )
{
  _length += str._length;
  if ( _length > _capacity )
  {
    char *tmp = _array;
    _capacity = _length;
    _array = (char *) malloc (_length + 1);
    setArray(tmp);
    //strcpy( _array, tmp );
    free(tmp);
  }
  strcat( _array, str._array );
  _array[_length] = '\0';

  return *this;
}



const String & String::append(char c)
{
  return (*this)+=c;
}

const String & String::append(char *str)
{
  return (*this)+=str;
}

const String & String::append(const String &s1)
{
  return (*this)+=s1;
}

const String & String::append(int n, int base)
{
  append((long)n, base);

  //char *t = valueOf((long)n, base);
  //*this+=t;
  //free(t);

  return *this;
}

const String & String::append(long n, int base)
{
  char *t = valueOf(n, base);
  *this+=t;
  free(t);

  return *this;
}

const String & String::append(int n)
{
  append((long)n, 10);
  return *this;

  //return (*this)+=n;
}

const String & String::append(long n)
{
  append(n, 10);
  return *this;

  //return (*this)+=n;
}


// the library uses the append versions instead 
// of the ones below, sometimes odd things happen :)
/*
String operator+(const String &s1, int n)
{
  String result(s1);
  result+=n;
  return result;
}


String operator+(const String &s1, char c2)
{
  String result(s1);
  result+=c2;
  return result;
}


String operator+(const String &s1, long n)
{
  String result(s1);
  result+=n;
  return result;
}


String operator+(int n, const String &s1)
{
  String result;
  result+=n;
  result+=s1;
  return result;
}


String operator+(long n, const String &s1)
{
  String result;
  result+=n;
  result+=s1;
  return result;
}


String operator+(const String &s1, const String &s2)
{
  String result(s1);
  result+=s2;
  return result;
}


String operator+(const String &s1, const char *s2)
{
  String result(s1);
  result += s2;
  return result;
}


String operator+(const char *s1, const String &s2)
{
  String result(s1);
  result += s2;
  return result;
}


String operator+(char c1, const String &s2)
{
  String result;
  result += c1;
  result += s2;
  return result;
}
*/

char String::charAt(int index)
{
  char thisChar;  // the character to return
  //int length = strlen(_array); // the length of the string (not the whole array)
  // as long as charNum isn't negative or bigger than the string length:
  if (index >= 0 && _length > index) {
    // get the character
    thisChar =  _array[index];
  } else {
    // if charNum is higher than the string length, return 0:
    thisChar = 0;
  }
  return thisChar;
}


void String::setCharAt(int charNum, char thisChar)
{
  if (_length > charNum) {	
    _array[charNum] = thisChar;
  }
}

// Not needed, use append(String) instead
/*
const String & String::concat(const String &str)
{
  return (*this) += str;
}
*/


boolean String::equals(char* str)
{
  char match = 0;  // whether or not the strings match
  // strcmp() returns the comparison value of two strings.  0 means they're the same:
  int comparison = strcmp(_array, str);
  
  // if the comparison returns 0, you have a match:
  match = (comparison == 0);
  return match;
}

boolean String::equals(const String &str) 
{
  return equals(str.cstr());
}


boolean String::contains(char* subString)
{
  char * subStringPointer;
  subStringPointer = strstr(_array,subString);
  return (subStringPointer != 0);
}


byte* String::getBytes(void)
{
  return (byte*) _array;
}


void String::setArray(const char* bytes) {
  //clear();
  strncpy(_array,bytes,_length+1);
  _array[_length] = '\0';
}


int String::indexOf(int ch)
{
  return indexOf(ch, 0);
}


int String::indexOf(const String &str)
{
  return indexOf(str, 0);
}


int String::indexOf(char ch, int fromIndex)
{
  if(fromIndex >= _length)
    return -1;
  char* tmp = strchr( &_array[fromIndex], ch);
  if(tmp == NULL)
    return -1;

  return tmp - _array;
}


int String::indexOf(const String &str, int fromIndex)
{
  if(fromIndex >= _length)
    return -1;

  char *result = strstr(&_array[fromIndex], str.cstr());
  if(result == NULL)
    return -1;

  return result - _array; 
}


boolean String::startsWith(const String &prefix)
{
  if(_length < prefix._length)
    return false;
  return startsWith( prefix, 0);
}


boolean String::startsWith( const String &prefix, int offset )
{
  if ( offset > _length - prefix._length )
    return 0;

  return strncmp( &_array[offset], prefix.cstr(), prefix._length ) == 0;
}


String String::substring(int beginIndex)
{
  return substring(beginIndex, _length);
}


String String::substring(int beginIndex, int endIndex)
{
  if ( beginIndex > endIndex )
  {
    int tmp = endIndex;
    endIndex = beginIndex;
    beginIndex = tmp;
  }
  if ( endIndex > _length )
  {
    exit(1);
  }
  char ch = _array[ endIndex ];   
  _array[ endIndex ] = '\0';	  
  String str = String( _array + beginIndex ); 
  _array[ endIndex ] = ch;	  
  return str;
}


char* String::valueOf(int n, int base)
{
  return valueOf((long) n, base);
}


char* String::valueOf(long n, int base)
{
  char *buf;
  buf = (char*)malloc(8*sizeof(long)+1);
  ltoa(n, buf, base);
  return buf;
}
 
// The ones below are String version, not used in the actual library
 
/*String String::valueOf(int n, int base) 
{
  return valueOf((long) n, base);
}


String String::valueOf(long n, int base) 
{
  String str(8*sizeof(long)+1);
  uint8_t buf[8*sizeof(long)+1];

  int i = 0;

  if(n < 0) {
    str+='-';
    n = -n;
  }
  if(n == 0) {
    str+='0';
    return str;
  }

  while(n > 0) {
    buf[i++] = n%base;
    n /= base;
  }
  for (i--; i >= 0; i--){
    str+=(char)(buf[i] < 10 ? '0' + buf[i] : 'A' + buf[i] - 10);
  }
  return str;
}
*/

char* String::toCharArray(void)
{
// it should return a new array but it might end up
// being a memory leak in user's programs so it just returns a pointer
// to the internal array
/*
  char *str = (char *)malloc(_length + 1);
  strcpy(str, _array);
  return str;
*/

  return _array;
}


void String::trim(void)
{
  // get the position of the last non-zero byte:
  int stringIndex = 0;
	
  // trim from the end of the string:
  while  (_array[stringIndex] == '\t' || // tab
    _array[stringIndex] == '\r' || 	 // carriage return
    _array[stringIndex] == '\n' || 	 // newline
    _array[stringIndex] == ' ' || 	 // space
    _array[stringIndex] == 0x11) 	 // vertical tab
    {
    	stringIndex++;
    }
	
    memmove(_array, _array+stringIndex, strlen(_array));

    // get the position of the last non-zero byte:
    stringIndex = strlen(_array) - 1;
	
    // trim from the end of the string:
    while(_array[stringIndex] == '\t' || // tab
      _array[stringIndex] == '\r' || 	// carriage return
      _array[stringIndex] == '\n' || 	// newline
      _array[stringIndex] == ' ' || 	// space
      _array[stringIndex] == 0x11) 	// vertical tab
    {
    	_array[stringIndex] = '\0';
    	stringIndex--;
    }
}


boolean String::endsWith(const String &suffix)
{
  if ( _length < suffix._length )
    return 0;

  return strcmp(&_array[_length-suffix._length], suffix.cstr()) == 0;
}


void String::replace(char oldChar, char newChar)
{
  char* tmp = _array;
  while( tmp = strchr( tmp, oldChar ) )
    *tmp = newChar;
}


void String::toLowerCase(void)
{
  for(int i = 0; i < _length; i++) {
    _array[i] = tolower( _array[i]);
  }
}


void String::toUpperCase(void)
{
  for(int i = 0; i < _length; i++) {
    _array[i] = toupper( _array[i]);
  }
}


void String::clear(void) {
  //int length = strlen(_array);
  for (int  c = 0; c < _capacity; c++) {
    _array[c] = '\0'; 
  }

}


/*
	version() returns the version of the library:
*/
String String::version(void) {
	return "0.4";
}

