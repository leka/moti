#include <dataflash.h>

int lastpage=0; //last page written to
int pages=25; //total pages that will be used
Dataflash dflash; 

void setup()
{
  Serial.begin(115200);
  Serial.print('h',BYTE);
  Serial.print('i',BYTE);
  Serial.print('\n',BYTE);//debug
  dflash.init(); //initialize the memory (pins are defined in dataflash.cpp
}

void loop()
{
  int j = 0;
  int i = 0;
  char messageline[] = "this is only a test on page: ";
  char lpstring[] = "lastpage: ";
  char int_string[10];

  itoa(lastpage, int_string, 10); // make string of the pagenumber
  strcat(messageline, int_string); //append to the messagline string
  //for (int i=0; messageline[i] != '\0'; i++)
  while (messageline[i] != '\0')
  {
    Serial.print(messageline[i], BYTE); //just a check to see if the loop is working
    dflash.Buffer_Write_Byte(1, i, messageline[i]);  //write to buffer 1, 1 byte at the time
    j = i;
    i++;
  }
  i=0;
  dflash.Buffer_Write_Byte(1, j+1, '\0'); //terminate the string in the buffer
  Serial.print('\t');
  dflash.Buffer_To_Page(1, lastpage); //write the buffer to the memory on page: lastpage

  strcat(lpstring, int_string);
  for(int i=0; lpstring[i] != '\0';i++)
  {
    dflash.Buffer_Write_Byte(2, 20, lpstring[i]); //write to buffer 2 the lastpage number that was used

    Serial.print(lpstring[i]); //write to serial port the lastpage number written to
  }
  Serial.println();
  lastpage++;
  if (lastpage > pages) //if we reach the end of the range of pages
  {
    lastpage = 0;
    for (int i=0;i<=pages;i++)
    {
      dflash.Page_To_Buffer(i, 1);//copy page i to the buffer

      for(int j=0;j<32;j++) //32 depends on the amount of data on the page
                            // testing for a specific charater is also possible
      {
        Serial.print(dflash.Buffer_Read_Byte(1, j)); //print the buffer data to the serial port
      }
      Serial.print("  page: "); 
      Serial.println(i); //print the last read page number
    }
  }
  delay(200); //slow it down a bit, just for easier reading
}
