/**
 * @file at45db161d.h
 * @brief AT45DB161D module
 **/
#ifndef AT45DB161D_H
#define AT45DB161D_H
#if ARDUINO >= 100
 #include "Arduino.h"
 #include "Print.h"
#else
 #include "WProgram.h"
#endif
extern "C" {

#include <avr/pgmspace.h>
#include <inttypes.h>

};

#include "at45db161d_commands.h"

/**
 * @defgroup AT45DB161D AT45DB161D module
 * @{
 **/

/**
 * @defgroup SPI SPI pinout and transfert function
 * @{
 **/
#ifndef SPI
/**
 * @defgroup SPI_Pinout SPI pinout
 * @{
 **/
/** Serial input (SI) **/
#define DATAOUT 16//MOSI
#define DATAIN  14//MISO 
#define SPICLOCK  15//sck
#define SLAVESELECT 8//ss

/**
 * @} 
 **/

/**
 * @fn inline uint8_t spi_transfer(uint8_t data)
 * @brief Transfer a byte via spi
 * @param data Data to transfer via SPI
 * @return The content of the SPI data register (SPDR)
 **/
inline uint8_t spi_transfer(uint8_t data)
{
	SPDR = data;
	while(!(SPSR & (1 << SPIF))) ;
	return SPDR;
}

/** De-assert CS **/
#define DF_CS_inactive digitalWrite(SLAVESELECT,HIGH)
/** Assert CS **/
#define DF_CS_active digitalWrite(SLAVESELECT,LOW)

#endif /* SPI */
/**
 * @}
 **/

/**
 * @defgroup STATUS_REGISTER_FORMAT Status register format
 * @{
 **/
/**
 * Ready/busy status is indicated using bit 7 of the status register.
 * If bit 7 is a 1, then the device is not busy and is ready to accept
 * the next command. If bit 7 is a 0, then the device is in a busy 
 * state.
 **/
#define READY_BUSY 0x80
/**
 * Result of the most recent Memory Page to Buffer Compare operation.
 * If this bit is equal to 0, then the data in the main memory page
 * matches the data in the buffer. If it's 1 then at least 1 byte in 
 * the main memory page does not match the data in the buffer.
 **/
#define COMPARE 0x40
/**
 * Bit 1 in the Status Register is used to provide information to the
 * user whether or not the sector protection has been enabled or
 * disabled, either by software-controlled method or 
 * hardware-controlled method. 1 means that the sector protection has
 * been enabled and 0 that it has been disabled.
 **/
#define PROTECT 0x02
/**
 * Bit 0 indicates wether the page size of the main memory array is
 * configured for "power of 2" binary page size (512 bytes) (bit=1) or 
 * standard DataFlash page size (528 bytes) (bit=0).
 **/
#define PAGE_SIZE 0x01
/**
 * Bits 5, 4, 3 and 2 indicates the device density. The decimal value
 * of these four binary bits does not equate to the device density; the
 * four bits represent a combinational code relating to differing
 * densities of DataFlash devices. The device density is not the same
 * as the density code indicated in the JEDEC device ID information.
 * The device density is provided only for backward compatibility.
 **/
#define DEVICE_DENSITY 0x2C 
/**
 * @}
 **/

/**
 * @brief at45db161d module
 * @todo
 *     - TESTS!
 *     - Protection and Security Commands
 *     - Auto Page Rewrite through Buffer 1
 *     - Auto Page Rewrite through Buffer 2
 **/
class ATD45DB161D
{
	public:
		/** 
		 * @brief ID structure 
		 * This structure contains various informations about the
		 * dataflash chip being used.
		 **/
		struct ID
		{
			uint8_t manufacturer;       /**< Manufacturer id                           **/
			uint8_t device[2];          /**< Device id                                 **/
			uint8_t extendedInfoLength; /**< Extended device information string length **/
		};

	public:
		/** CTOR **/
		ATD45DB161D();
		/** DTOR **/
		~ATD45DB161D();

		/** Setup SPI and pinout **/
		void Init();

		/** 
		 * Read status register 
		 * @return The content of the status register
		 * **/
		uint8_t ReadStatusRegister();

		/** 
		 * Read Manufacturer and Device ID 
		 * @note if id.extendedInfoLength is not equal to zero,
		 *       successive calls to spi_transfer(0xff) will return
		 *       the extended device information string bytes.
		 * @param id Pointer to the ID structure to initialize
		 **/
		void ReadManufacturerAndDeviceID(struct ATD45DB161D::ID *id);
		
		/** 
		 * A main memory page read allows the user to read data directly from
		 * any one of the 4096 pages in the main memory, bypassing both of the
		 * data buffers and leaving the contents of the buffers unchanged.
		 * @param page Page of the main memory to read
		 * @param offset Starting byte address within the page
		 **/
		void ReadMainMemoryPage(uint16_t page, uint16_t offset);

		/** 
		 * Sequentially read a continuous stream of data.
		 * @param page Page of the main memory where the sequential read will start
		 * @param offset Starting byte address within the page
		 * @param low If true the read operation will be performed in low speed mode (and in high speed mode if it's false).
		 * @note The legacy mode is not currently supported
		 * @warning UNTESTED
		 **/
		void ContinuousArrayRead(uint16_t page, uint16_t offset, uint8_t low);

		/** 
		 * Read the content of one of the SRAM data buffers (in low or high speed mode).
		 * @param bufferNum Buffer to read (1 or 2)
		 * @param offset Starting byte within the buffer
		 * @param low If true the read operation will be performed in low speed mode (and in high speed mode if it's false).
		 **/
		void BufferRead(uint8_t bufferNum, uint16_t offset, uint8_t low);

		/** 
		 * Write data to one of the SRAM data buffers. Any further call to
		 * spi_tranfer will return bytes contained in the data buffer until
		 * a low-to-high transition is detected on the CS pin. If the end of
		 * the data buffer is reached, the device will wrap around back to the
		 * beginning of the buffer. 
		 * @param bufferNum Buffer to read (1 or 2)
		 * @param offset Starting byte within the buffer
		 **/
		void BufferWrite(uint8_t bufferNum, uint16_t offset);
		
		/**
		 * Transfer data from buffer 1 or 2 to main memory page.
		 * @param bufferNum Buffer to use (1 or 2)
		 * @param page Page where the content of the buffer will transfered
		 * @param erase If set the page will be first erased before the buffer transfer.
		 * @note If erase is equal to zero, the page must have been previously erased using one of the erase command (Page or Block Erase).
		 **/
		void BufferToPage(uint8_t bufferNum, uint16_t page, uint8_t erase);		

		/**
		 * Transfer a page of data from main memory to buffer 1 or 2.
		 * @param page Main memory page to transfer
		 * @param buffer Buffer (1 or 2) where the data will be written
		 **/
		void PageToBuffer(uint16_t page, uint8_t bufferNum);

		/** 
		 * Erase a page in the main memory array.
		 * @param page Page to erase
		 * @warning UNTESTED
		 **/
		void PageErase(uint16_t page);
		
		/**
		 * Erase a block of eight pages at one time.
		 * @param block Index of the block to erase
		 * @warning UNTESTED
		 **/
		void BlockErase(uint16_t block);

		/** 
		 * Erase a sector in main memory. There are 16 sector on the
		 * at45db161d and only one can be erased at one time.
		 * @param sector Sector to erase
		 * @warning UNTESTED
		 **/
		void SectoreErase(uint8_t sector);

		/** 
		 * Erase the entire chip memory. Sectors proteced or locked down will
		 * not be erased.
		 * @warning UNTESTED
		 **/
		void ChipErase();

		/**
		 * This a combination of Buffer Write and Buffer to Page with
		 * Built-in Erase.
		 * @note You must call EndAndWait in order to start transfering data from buffer to page
		 * @param page Page where the content of the buffer will transfered
		 * @param offset Starting byte address within the buffer
		 * @param bufferNum Buffer to use (1 or 2)
		 * @warning UNTESTED
		 **/
		void BeginPageWriteThroughBuffer(uint16_t page, uint16_t offset, uint8_t bufferNum);
		
		/**
		 * Perform a low-to-high transition on the CS pin and then poll
		 * the status register to check if the dataflash is busy.
		 **/
		void EndAndWait();

		/**
		 * Compare a page of data in main memory to the data in buffer 1 or 2.
		 * @param page Page to test
		 * @param bufferNum Buffer number
		 * @return
		 *		- 1 if the page and the buffer contains the same data
		 * 		- 0 else
		 * @warning UNTESTED
		 **/
		int8_t ComparePageToBuffer(uint16_t page, uint8_t bufferNum);

		/**
		 * Put the device into the lowest power consumption mode.
		 * Once the device has entered the Deep Power-down mode, all
		 * instructions are ignored except the Resume from Deep
		 * Power-down command.
		 * @warning UNTESTED
		 **/
		void DeepPowerDown();

		/**
		 * Takes the device out of Deep Power-down mode.
		 * @warning UNTESTED
		 **/
		void ResumeFromDeepPowerDown();

	private:
		/* Nothing atm but who knows... */
};

/**
 * @}
 **/

#endif /* AT45DB161D_H */
