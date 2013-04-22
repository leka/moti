//*****************************************************************************
//
//      COPYRIGHT (c) ATMEL Norway, 1996-2001
//
//      The copyright to the document(s) herein is the property of
//      ATMEL Norway, Norway.
//
//      The document(s) may be used  and/or copied only with the written
//      permission from ATMEL Norway or in accordance with the terms and
//      conditions stipulated in the agreement/contract under which the
//      document(s) have been supplied.
//
//*****************************************************************************
//
//  File........: DATAFLASH.C
//
//  Author(s)...: ATMEL Norway
//
//  Target(s)...: All AVRs with built-in HW SPI
//
//  Description.: Functions to access the Atmel AT45Dxxx Dataflash series
//                Supports 512Kbit - 64Mbit
//
//  Revisions...:
//
//  YYYYMMDD - VER. - COMMENT                                       - SIGN.
//
//  20011017 - 1.00 - Beta release                                  -  RM
//  20011017 - 0.10 - Generated file                                -  RM
//  20031009          port to avr-gcc/avr-libc                      - M.Thomas
//  20040121          added compare and erase function              - M.Thomas
//
//*****************************************************************************
/* 
   remark mthomas: If you plan to use the Dataflash functions in own code
   for (battery powered) devices: disable the "chip select" after accessing
   the Dataflash. The current draw with cs enabled is "very" high. You can
   simply use the macro DF_CS_inactive already defined by Atmel after every
   DF access

   The coin-cell battery on the Butterfly is not a reliable power-source if data
   in the flash-array should be changed (write/erase).
   See the Dataflash datasheet for the current needed during write-accesses.
*/
//*****************************************************************************
/*
  Dirk Spaanderman: changed the dataflash code to a c++ library for arduino
*/

#include "Dataflash.h"

#define DATAOUT 11//MOSI
#define DATAIN  12//MISO 
#define SPICLOCK  13//sck
#define SLAVESELECT 10//ss

//opcodes
#define WREN  6
#define WRDI  4
#define RDSR  5
#define WRSR  1
#define READ  3
#define WRITE 2

unsigned char PageBits = 0;
unsigned int  PageSize = 0;

Dataflash::Dataflash(void)
{
}

void Dataflash::init(void)
{
  char clr;
  pinMode(DATAOUT, OUTPUT);
  pinMode(DATAIN, INPUT);
  pinMode(SPICLOCK,OUTPUT);
  pinMode(SLAVESELECT,OUTPUT);
  digitalWrite(SLAVESELECT,HIGH); //disable device
  // SPCR = 01010000
  //interrupt disabled,spi enabled,msb 1st,master,clk low when idle,
  //sample on leading edge of clk,system clock/4 rate (fastest)
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<CPHA)|(1<<CPOL);
  SPSR = (1<<SPI2X); //double speed??
  clr=SPSR;
  clr=SPDR;
  //delay(100); //FIXME
}
// *****************************[ Start Of DATAFLASH.C ]*************************
unsigned char Dataflash::DF_SPI_RW(unsigned char output)
{
  SPDR = output;                    // Start the transmission
  while (!(SPSR & (1<<SPIF)))     // Wait the end of the transmission
  {
  };
  return SPDR; 
}

unsigned char Dataflash::Read_DF_status (void)
{
  unsigned char result,index_copy;
  DF_CS_inactive();				//make sure to toggle CS signal in order
  DF_CS_active();				//to reset Dataflash command decoder
  result = DF_SPI_RW(StatusReg);		//send status register read op-code
  result = DF_SPI_RW(0x00);			//dummy write to get result
  index_copy = ((result & 0x38) >> 3);	//get the size info from status register
  // mtA
  /// if (!PageBits) { // mt 200401
  // PageBits   = DF_pagebits[index_copy];	//get number of internal page address bits from look-up table
  // PageSize   = DF_pagesize[index_copy];   //get the size of the page (in bytes)
  //pagesize lijkt nergens gebruikt te worden
  PageBits   = pgm_read_byte(&DF_pagebits[index_copy]);	//get number of internal page address bits from look-up table
  PageSize   = pgm_read_word(&DF_pagesize[index_copy]);   //get the size of the page (in bytes)
  /// }
  // mtE
  return result;				//return the read status register value
}
/*****************************************************************************
 * 
 *	Function name : Page_To_Buffer
 *  
 *	Returns :		None
 *  
 *	Parameters :	BufferNo	->	Decides usage of either buffer 1 or 2
 * 
 *			PageAdr		->	Address of page to be transferred to buffer
 * 
 *	Purpose :	Transfers a page from flash to Dataflash SRAM buffer
 * 					
 * 
 ******************************************************************************/
void Dataflash::Page_To_Buffer (unsigned int PageAdr, unsigned char BufferNo)
{
  DF_CS_inactive();				//make sure to toggle CS signal in order
  DF_CS_active();				//to reset Dataflash command decoder
  if (1 == BufferNo)				//transfer flash page to buffer 1
  {
    DF_SPI_RW(FlashToBuf1Transfer);				//transfer to buffer 1 op-code
    DF_SPI_RW((unsigned char)(PageAdr >> (16 - PageBits)));	//upper part of page address
    DF_SPI_RW((unsigned char)(PageAdr << (PageBits - 8)));	//lower part of page address
    DF_SPI_RW(0x00);						//don't cares
  }
#ifdef USE_BUFFER2
  else	
    if (2 == BufferNo)						//transfer flash page to buffer 2
  {
    DF_SPI_RW(FlashToBuf2Transfer);				//transfer to buffer 2 op-code
    DF_SPI_RW((unsigned char)(PageAdr >> (16 - PageBits)));	//upper part of page address
    DF_SPI_RW((unsigned char)(PageAdr << (PageBits - 8)));	//lower part of page address
    DF_SPI_RW(0x00);						//don't cares
  }
#endif
  DF_CS_inactive();						//initiate the transfer
  DF_CS_active();
  while(!(Read_DF_status() & 0x80));				//monitor the status register, wait until busy-flag is high
}
/*****************************************************************************
 *  
 *	Function name : Buffer_Read_Byte
 *  
 *	Returns :		One read byte (any value)
 *
 *	Parameters :	BufferNo	->	Decides usage of either buffer 1 or 2
 * 
 *					IntPageAdr	->	Internal page address
 *  
 *	Purpose :		Reads one byte from one of the Dataflash
 * 
 *					internal SRAM buffers
 * 
 ******************************************************************************/
unsigned char Dataflash::Buffer_Read_Byte (unsigned char BufferNo, unsigned int IntPageAdr)
{
  unsigned char data;
  data='0'; // mt 
  DF_CS_inactive();				//make sure to toggle CS signal in order
  DF_CS_active();				//to reset Dataflash command decoder
  if (1 == BufferNo)				//read byte from buffer 1
  {
    DF_SPI_RW(Buf1Read);			//buffer 1 read op-code
    DF_SPI_RW(0x00);				//don't cares
    DF_SPI_RW((unsigned char)(IntPageAdr>>8));//upper part of internal buffer address
    DF_SPI_RW((unsigned char)(IntPageAdr));	//lower part of internal buffer address
    DF_SPI_RW(0x00);				//don't cares
    data = DF_SPI_RW(0x00);			//read byte
  }
#ifdef USE_BUFFER2
  else
    if (2 == BufferNo)				//read byte from buffer 2
    {
      DF_SPI_RW(Buf2Read);					//buffer 2 read op-code
      DF_SPI_RW(0x00);						//don't cares
      DF_SPI_RW((unsigned char)(IntPageAdr>>8));//upper part of internal buffer address
      DF_SPI_RW((unsigned char)(IntPageAdr));	//lower part of internal buffer address
      DF_SPI_RW(0x00);						//don't cares
      data = DF_SPI_RW(0x00);					//read byte
    }
#endif
  return data;							//return the read data byte
}
/*****************************************************************************
 *  
 *	Function name : Buffer_Read_Str
 * 
 *	Returns :		None
 *  
 *	Parameters :	BufferNo	->	Decides usage of either buffer 1 or 2
 * 
 *					IntPageAdr	->	Internal page address
 * 
 *					No_of_bytes	->	Number of bytes to be read
 * 
 *					*BufferPtr	->	address of buffer to be used for read bytes
 * 
 *	Purpose :		Reads one or more bytes from one of the Dataflash
 * 
 *					internal SRAM buffers, and puts read bytes into
 * 
 *					buffer pointed to by *BufferPtr
 * 
 * 
 ******************************************************************************/
void Dataflash::Buffer_Read_Str (unsigned char BufferNo, unsigned int IntPageAdr, unsigned int No_of_bytes, unsigned char *BufferPtr)
{
  unsigned int i;
  DF_CS_inactive();						//make sure to toggle CS signal in order
  DF_CS_active();							//to reset Dataflash command decoder
  if (1 == BufferNo)						//read byte(s) from buffer 1
  {
    DF_SPI_RW(Buf1Read);				//buffer 1 read op-code
    DF_SPI_RW(0x00);					//don't cares
    DF_SPI_RW((unsigned char)(IntPageAdr>>8));//upper part of internal buffer address
    DF_SPI_RW((unsigned char)(IntPageAdr));	//lower part of internal buffer address
    DF_SPI_RW(0x00);					//don't cares
    for( i=0; i<No_of_bytes; i++)
    {
      *(BufferPtr) = DF_SPI_RW(0x00);		//read byte and put it in AVR buffer pointed to by *BufferPtr
      BufferPtr++;					//point to next element in AVR buffer
    }
  }
#ifdef USE_BUFFER2
  else
    if (2 == BufferNo)					//read byte(s) from buffer 2
    {
      DF_SPI_RW(Buf2Read);				//buffer 2 read op-code
      DF_SPI_RW(0x00);					//don't cares
      DF_SPI_RW((unsigned char)(IntPageAdr>>8));//upper part of internal buffer address
      DF_SPI_RW((unsigned char)(IntPageAdr));	//lower part of internal buffer address
      DF_SPI_RW(0x00);					//don't cares
      for( i=0; i<No_of_bytes; i++)
      {
        *(BufferPtr) = DF_SPI_RW(0x00);		//read byte and put it in AVR buffer pointed to by *BufferPtr
        BufferPtr++;					//point to next element in AVR buffer
      }
    }
#endif
}
//NB : Sjekk at (IntAdr + No_of_bytes) < buffersize, hvis ikke blir det bare ball..
//mtA 
// translation of the Norwegian comments (thanks to Eirik Tveiten):
// NB : Check that (IntAdr + No_of_bytes) < buffersize, if not there will be problems
//mtE

/*****************************************************************************
 * 
 * 
 *	Function name : Buffer_Write_Enable
 * 
 *	Returns :		None
 *  
 *	Parameters :	IntPageAdr	->	Internal page address to start writing from
 * 
 *			BufferAdr	->	Decides usage of either buffer 1 or 2
 *  
 *	Purpose :	Enables continous write functionality to one of the Dataflash buffers
 * 
 *			buffers. NOTE : User must ensure that CS goes high to terminate
 * 
 *			this mode before accessing other Dataflash functionalities 
 * 
 ******************************************************************************/
void Dataflash::Buffer_Write_Enable (unsigned char BufferNo, unsigned int IntPageAdr)
{
  DF_CS_inactive();				//make sure to toggle CS signal in order
  DF_CS_active();				//to reset Dataflash command decoder
  if (1 == BufferNo)				//write enable to buffer 1
  {
    DF_SPI_RW(Buf1Write);			//buffer 1 write op-code
    DF_SPI_RW(0x00);				//don't cares
    DF_SPI_RW((unsigned char)(IntPageAdr>>8));//upper part of internal buffer address
    DF_SPI_RW((unsigned char)(IntPageAdr));	//lower part of internal buffer address
  }
#ifdef USE_BUFFER2
  else
    if (2 == BufferNo)				//write enable to buffer 2
    {
      DF_SPI_RW(Buf2Write);			//buffer 2 write op-code
      DF_SPI_RW(0x00);				//don't cares
      DF_SPI_RW((unsigned char)(IntPageAdr>>8));//upper part of internal buffer address
      DF_SPI_RW((unsigned char)(IntPageAdr));	//lower part of internal buffer address
    }
#endif
}
/*****************************************************************************
 *  
 *	Function name : Buffer_Write_Byte
 * 
 *	Returns :		None
 *  
 *	Parameters :	IntPageAdr	->	Internal page address to write byte to
 * 
 *			BufferAdr	->	Decides usage of either buffer 1 or 2
 * 
 *			Data		->	Data byte to be written
 *  
 *	Purpose :		Writes one byte to one of the Dataflash
 * 
 *					internal SRAM buffers
 *
 ******************************************************************************/
void Dataflash::Buffer_Write_Byte (unsigned char BufferNo, unsigned int IntPageAdr, unsigned char Data)
{
  DF_CS_inactive();				//make sure to toggle CS signal in order
  DF_CS_active();				//to reset Dataflash command decoder
  if (1 == BufferNo)				//write byte to buffer 1
  {
    DF_SPI_RW(Buf1Write);			//buffer 1 write op-code
    DF_SPI_RW(0x00);				//don't cares
    DF_SPI_RW((unsigned char)(IntPageAdr>>8));//upper part of internal buffer address
    DF_SPI_RW((unsigned char)(IntPageAdr));	//lower part of internal buffer address
    DF_SPI_RW(Data);				//write data byte
  }
#ifdef USE_BUFFER2
  else
    if (2 == BufferNo)				//write byte to buffer 2
    {
      DF_SPI_RW(Buf2Write);			//buffer 2 write op-code
      DF_SPI_RW(0x00);				//don't cares
      DF_SPI_RW((unsigned char)(IntPageAdr>>8));//upper part of internal buffer address
      DF_SPI_RW((unsigned char)(IntPageAdr));	//lower part of internal buffer address
      DF_SPI_RW(Data);				//write data byte
    }		
#endif
}
/*****************************************************************************
 * 
 * 
 *	Function name : Buffer_Write_Str
 *  
 *	Returns :		None
 * 
 *	Parameters :	BufferNo	->	Decides usage of either buffer 1 or 2
 * 
 *			IntPageAdr	->	Internal page address
 * 
 *			No_of_bytes	->	Number of bytes to be written
 * 
 *			*BufferPtr	->	address of buffer to be used for copy of bytes
 * 
 *			from AVR buffer to Dataflash buffer 1 (or 2)
 * 
 *	Purpose :		Copies one or more bytes to one of the Dataflash
 * 
 *				internal SRAM buffers from AVR SRAM buffer
 * 
 *			pointed to by *BufferPtr
 * 
 ******************************************************************************/
void Dataflash::Buffer_Write_Str (unsigned char BufferNo, unsigned int IntPageAdr, unsigned int No_of_bytes, unsigned char *BufferPtr)
{
  unsigned int i;
  DF_CS_inactive();				//make sure to toggle CS signal in order
  DF_CS_active();				//to reset Dataflash command decoder
  if (1 == BufferNo)				//write byte(s) to buffer 1
  {
    DF_SPI_RW(Buf1Write);			//buffer 1 write op-code
    DF_SPI_RW(0x00);				//don't cares
    DF_SPI_RW((unsigned char)(IntPageAdr>>8));//upper part of internal buffer address
    DF_SPI_RW((unsigned char)(IntPageAdr));	//lower part of internal buffer address
    for( i=0; i<No_of_bytes; i++)
    {
      DF_SPI_RW(*(BufferPtr));			//write byte pointed at by *BufferPtr to Dataflash buffer 1 location
      BufferPtr++;				//point to next element in AVR buffer
    }
  }
#ifdef USE_BUFFER2
  else
    if (2 == BufferNo)				//write byte(s) to buffer 2
    {
      DF_SPI_RW(Buf2Write);			//buffer 2 write op-code
      DF_SPI_RW(0x00);				//don't cares
      DF_SPI_RW((unsigned char)(IntPageAdr>>8));//upper part of internal buffer address
      DF_SPI_RW((unsigned char)(IntPageAdr));	//lower part of internal buffer address
      for( i=0; i<No_of_bytes; i++)
      {
        DF_SPI_RW(*(BufferPtr));		//write byte pointed at by *BufferPtr to Dataflash buffer 2 location
        BufferPtr++;				//point to next element in AVR buffer
      }
    }
#endif
}
//NB : Monitorer busy-flag i status-reg.
//NB : Sjekk at (IntAdr + No_of_bytes) < buffersize, hvis ikke blir det bare ball..
//mtA 
// translation of the Norwegian comments (thanks to Eirik Tveiten):
// NB : Monitors busy-flag in status-reg
// NB : Check that (IntAdr + No_of_bytes) < buffersize, if not there will be problems
//mtE
/*****************************************************************************
 * 
 * 
 *	Function name : Buffer_To_Page
 * 
 *	Returns :		None
 *  
 *	Parameters :	BufferAdr	->	Decides usage of either buffer 1 or 2
 * 
 *			PageAdr		->	Address of flash page to be programmed
 *  
 *	Purpose :	Transfers a page from Dataflash SRAM buffer to flash
 * 
 *			 
 ******************************************************************************/
void Dataflash::Buffer_To_Page (unsigned char BufferNo, unsigned int PageAdr)
{
  DF_CS_inactive();						//make sure to toggle CS signal in order
  DF_CS_active();						//to reset Dataflash command decoder
  if (1 == BufferNo)						//program flash page from buffer 1
  {
    DF_SPI_RW(Buf1ToFlashWE);					//buffer 1 to flash with erase op-code
    DF_SPI_RW((unsigned char)(PageAdr >> (16 - PageBits)));	//upper part of page address
    DF_SPI_RW((unsigned char)(PageAdr << (PageBits - 8)));	//lower part of page address
    DF_SPI_RW(0x00);										//don't cares
  }
#ifdef USE_BUFFER2
  else	
    if (2 == BufferNo)						//program flash page from buffer 2
  {
    DF_SPI_RW(Buf2ToFlashWE);					//buffer 2 to flash with erase op-code
    DF_SPI_RW((unsigned char)(PageAdr >> (16 - pPageBits)));	//upper part of page address
    DF_SPI_RW((unsigned char)(PageAdr << (pPageBits - 8)));	//lower part of page address
    DF_SPI_RW(0x00);						//don't cares
  }
#endif
  DF_CS_inactive();						//initiate flash page programming
  DF_CS_active();												
  while(!(Read_DF_status() & 0x80));				//monitor the status register, wait until busy-flag is high
}
/*****************************************************************************
 * 
 * 
 *	Function name : Cont_Flash_Read_Enable
 * 
 *	Returns :		None
 * 
 *	Parameters :	PageAdr		->	Address of flash page where cont.read starts from
 * 
 *			IntPageAdr	->	Internal page address where cont.read starts from
 *
 *	Purpose :	Initiates a continuous read from a location in the DataFlash
 * 
 ******************************************************************************/
void Dataflash::Cont_Flash_Read_Enable (unsigned int PageAdr, unsigned int IntPageAdr)
{
  DF_CS_inactive();																//make sure to toggle CS signal in order
  DF_CS_active();																//to reset Dataflash command decoder
  DF_SPI_RW(ContArrayRead);													//Continuous Array Read op-code
  DF_SPI_RW((unsigned char)(PageAdr >> (16 - PageBits)));			//upper part of page address
  DF_SPI_RW((unsigned char)((PageAdr << (PageBits - 8))+ (IntPageAdr>>8)));	//lower part of page address and MSB of int.page adr.
  DF_SPI_RW((unsigned char)(IntPageAdr));										//LSB byte of internal page address
  DF_SPI_RW(0x00);															//perform 4 dummy writes
  DF_SPI_RW(0x00);															//in order to intiate DataFlash
  DF_SPI_RW(0x00);															//address pointers
  DF_SPI_RW(0x00);
}

//#ifdef MTEXTRAS
/*****************************************************************************
 *  
 *	Function name : Page_Buffer_Compare
 *  
 *	Returns :		0 match, 1 if mismatch
 *  
 *	Parameters :	BufferAdr	->	Decides usage of either buffer 1 or 2
 * 
 *			PageAdr		->	Address of flash page to be compared with buffer
 * 
 *	Purpose :	comparte Buffer with Flash-Page
 *  
 *   added by Martin Thomas, Kaiserslautern, Germany. This routine was not 
 * 
 *   included by ATMEL
 * 
 ******************************************************************************/
unsigned char Dataflash::Page_Buffer_Compare(unsigned char BufferNo, unsigned int PageAdr)
{
  unsigned char stat;
  DF_CS_inactive();					//make sure to toggle CS signal in order
  DF_CS_active();					//to reset Dataflash command decoder
  if (1 == BufferNo)									
  {
    DF_SPI_RW(FlashToBuf1Compare);	
    DF_SPI_RW((unsigned char)(PageAdr >> (16 - PageBits)));	//upper part of page address
    DF_SPI_RW((unsigned char)(PageAdr << (PageBits - 8)));	//lower part of page address and MSB of int.page adr.
    DF_SPI_RW(0x00);	// "dont cares"
  }
#ifdef USE_BUFFER2
  else if (2 == BufferNo)											
  {
    DF_SPI_RW(FlashToBuf2Compare);						
    DF_SPI_RW((unsigned char)(PageAdr >> (16 - PageBits)));	//upper part of page address
    DF_SPI_RW((unsigned char)(PageAdr << (PageBits - 8)));	//lower part of page address
    DF_SPI_RW(0x00);						//don't cares
  }
#endif
  DF_CS_inactive();												
  DF_CS_active();		
  do {
    stat=Read_DF_status();
  } 
  while(!(stat & 0x80));					//monitor the status register, wait until busy-flag is high
  return (stat & 0x40);
}
/*****************************************************************************
 * 
 * 
 *	Function name : Page_Erase
 * 
 *	Returns :		None
 * 
 *	Parameters :	PageAdr		->	Address of flash page to be erased
 * 
 *	Purpose :		Sets all bits in the given page (all bytes are 0xff)
 * 
 *	function added by mthomas. 
 *
 ******************************************************************************/
void Dataflash::Page_Erase (unsigned int PageAdr)
{
  DF_CS_inactive();																//make sure to toggle CS signal in order
  DF_CS_active();																//to reset Dataflash command decoder
  DF_SPI_RW(PageErase);						//Page erase op-code
  DF_SPI_RW((unsigned char)(PageAdr >> (16 - PageBits)));	//upper part of page address
  DF_SPI_RW((unsigned char)(PageAdr << (PageBits - 8)));	//lower part of page address and MSB of int.page adr.
  DF_SPI_RW(0x00);	// "dont cares"
  DF_CS_inactive();						//initiate flash page erase
  DF_CS_active();
  while(!(Read_DF_status() & 0x80));				//monitor the status register, wait until busy-flag is high
}
// MTEXTRAS
//#endif
// *****************************[ End Of DATAFLASH.C ]*************************

void Dataflash::DF_CS_inactive()
{
  digitalWrite(SLAVESELECT,HIGH);
}
void Dataflash::DF_CS_active()
{
  digitalWrite(SLAVESELECT,LOW);
}
