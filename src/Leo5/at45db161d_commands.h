/**
 * @file at45db161d_commands.h
 * @brief AT45DB161D commands opcodes
 **/
#ifndef AT45DB161D_COMMANDS_H
#define AT45DB161D_COMMANDS_H
#if ARDUINO >= 100
 #include "Arduino.h"
 #include "Print.h"
#else
 #include "WProgram.h"
#endif
/**
 * @defgroup AT45DB161D_commands AT45DB161D commands opcodes
 * @{
 **/

/**
 * @defgroup Read_commands Read commands
 * @{
 **/
/** Main Memory Page Read */
#define AT45DB161D_PAGE_READ 0xD2
/** Continuous Array Read (Low Frequency) **/
#define AT45DB161D_CONTINUOUS_READ_LOW_FREQ 0x03
/** Continuous Array Read (High Frequency) **/ 
#define AT45DB161D_CONTINUOUS_READ_HIGH_FREQ 0x0B
/** Buffer 1 Read (Low Frequency) **/
#define AT45DB161D_BUFFER_1_READ_LOW_FREQ 0xD1
/** Buffer 2 Read (Low Frequency) **/
#define AT45DB161D_BUFFER_2_READ_LOW_FREQ 0xD3
/** Buffer 1 Read **/
#define AT45DB161D_BUFFER_1_READ 0xD4
/** Buffer 2 Read **/
#define AT45DB161D_BUFFER_2_READ 0xD6
/**
 * @}
 **/

/**
 * @defgroup Program_Erase_commands Program and Erase commands
 * @{
 **/
/** Buffer 1 Write **/
#define AT45DB161D_BUFFER_1_WRITE 0x84
/** Buffer 2 Write **/
#define AT45DB161D_BUFFER_2_WRITE 0x87
/** Buffer 1 to Main Memory Page Program with Built-in Erase **/
#define AT45DB161D_BUFFER_1_TO_PAGE_WITH_ERASE 0x83
/** Buffer 2 to Main Memory Page Program with Built-in Erase **/
#define AT45DB161D_BUFFER_2_TO_PAGE_WITH_ERASE 0x86
/** Buffer 1 to Main Memory Page Program without Built-in Erase **/
#define AT45DB161D_BUFFER_1_TO_PAGE_WITHOUT_ERASE 0x88
/** Buffer 2 to Main Memory Page Program without Built-in Erase **/
#define AT45DB161D_BUFFER_2_TO_PAGE_WITHOUT_ERASE 0x89
/** Page Erase **/
#define AT45DB161D_PAGE_ERASE 0x81
/** Block Erase **/
#define AT45DB161D_BLOCK_ERASE 0x50
/** Sector Erase **/
#define AT45DB161D_SECTOR_ERASE 0x7C
/** Chip Erase Sequence **/
#define AT45DB161D_CHIP_ERASE_0 0xC7
#define AT45DB161D_CHIP_ERASE_1 0x94
#define AT45DB161D_CHIP_ERASE_2 0x80
#define AT45DB161D_CHIP_ERASE_3 0x9A
/** Main Memory Page Program Through Buffer 1 **/
#define AT45DB161D_PAGE_THROUGH_BUFFER_1 0x82
/** Main Memory Page Program Through Buffer 2 **/
#define AT45DB161D_PAGE_THROUGH_BUFFER_2 0x85
/**
 * @}
 **/

/**
 * @defgroup ProtectionSecurity_Commands Protection and Security Commands
 * @warning UNIMPLEMENTED
 * @{
 **/
#ifdef AT45DB161D_EXPERT_MODE
/* Use the following commands at your own risk ! */
/** Enable Sector Protection **/
#define AT45DB161D_ENABLE_SECTOR_PROTECTION_0 0x3D
#define AT45DB161D_ENABLE_SECTOR_PROTECTION_1 0x2A
#define AT45DB161D_ENABLE_SECTOR_PROTECTION_2 0x7F
#define AT45DB161D_ENABLE_SECTOR_PROTECTION_3 0xA9
/** Disable Sector Protection **/
#define AT45DB161D_DISABLE_SECTOR_PROTECTION_0 0x3D
#define AT45DB161D_DISABLE_SECTOR_PROTECTION_1 0x2A
#define AT45DB161D_DISABLE_SECTOR_PROTECTION_2 0x7F
#define AT45DB161D_DISABLE_SECTOR_PROTECTION_3 0x9A
/** Erase Sector Protection Register **/
#define AT45DB161D_ERASE_SECTOR_PROTECTION_REGISTER_0 0x3D
#define AT45DB161D_ERASE_SECTOR_PROTECTION_REGISTER_0 0x2A
#define AT45DB161D_ERASE_SECTOR_PROTECTION_REGISTER_0 0x7F
#define AT45DB161D_ERASE_SECTOR_PROTECTION_REGISTER_0 0xCF
/** Program Sector Protection Register **/
#define AT45DB161D_PROGRAM_SECTOR_PROTECTION_REGISTER_0 0x3D
#define AT45DB161D_PROGRAM_SECTOR_PROTECTION_REGISTER_1 0x2A
#define AT45DB161D_PROGRAM_SECTOR_PROTECTION_REGISTER_2 0x7F
#define AT45DB161D_PROGRAM_SECTOR_PROTECTION_REGISTER_3 0xFC
/** Sector Lockdown **/
#define AT45DB161D_SECTOR_LOCKDOWN_0 0X3D
#define AT45DB161D_SECTOR_LOCKDOWN_1 0x2A
#define AT45DB161D_SECTOR_LOCKDOWN_2 0x7F
#define AT45DB161D_SECTOR_LOCKDOWN_3 0x30
/** Program Security Register **/
#define AT45DB161D_PROGRAM_SECURITY_REGISTER_0 0x9B
#define AT45DB161D_PROGRAM_SECURITY_REGISTER_1 0x00
#define AT45DB161D_PROGRAM_SECURITY_REGISTER_2 0x00
#define AT45DB161D_PROGRAM_SECURITY_REGISTER_3 0x00
#endif /* AT45DB161D_EXPERT_MODE */

/** Read Sector Protection Register **/
#define AT45DB161D_READ_SECTOR_PROTECTION_REGISTER 0x32
/** Read Sector Lockdown Register **/
#define AT45DB161D_READ_SECTOR_LOCKDOWN_REGISTER 35H
/** Read Security Register **/
#define AT45DB161D_READ_SECURITY_REGISTER 0x77
/**
 * @}
 **/

/**
 * @defgroup Additional_commands Additional Commands
 * @{
 **/
/** Main Memory Page to Buffer 1 Transfer **/
#define AT45DB161D_TRANSFER_PAGE_TO_BUFFER_1 0x53
/** Main Memory Page to Buffer 2 Transfer **/
#define AT45DB161D_TRANSFER_PAGE_TO_BUFFER_2 0x55
/** Main Memory Page to Buffer 1 Compare **/
#define AT45DB161D_COMPARE_PAGE_TO_BUFFER_1 0x60
/** Main Memory Page to Buffer 2 Compare **/
#define AT45DB161D_COMPARE_PAGE_TO_BUFFER_2 0x61
/** Auto Page Rewrite through Buffer 1 **/
#define AT45DB161D_AUTO_PAGE_REWRITE_THROUGH_BUFFER_1 0x58
/** Auto Page Rewrite through Buffer 2 **/
#define AT45DB161D_AUTO_PAGE_REWRITE_THROUGH_BUFFER_2 0x59
/** Deep Power-down **/
#define AT45DB161D_DEEP_POWER_DOWN 0xB9
/** Resume from Deep Power-down **/
#define AT45DB161D_RESUME_FROM_DEEP_POWER_DOWN 0xAB
/** Status Register Read **/
#define AT45DB161D_STATUS_REGISTER_READ 0xD7
/** Manufacturer and Device ID Read **/
#define AT45DB161D_READ_MANUFACTURER_AND_DEVICE_ID 0x9F
/**
 * @}
 **/

/**
 * @defgroup Legacy_commands Legacy Commands
 * @{
 **/
/** Buffer 1 Read **/
#define AT45DB161D_BUFFER_1_READ_LEGACY 0X54
/** Buffer 2 Read **/
#define AT45DB161D_BUFFER_2_READ_LEGACY 0x56
/** Main Memory Page Read **/
#define AT45DB161D_PAGE_READ_LEGACY 0x52
/** Continuous Array Read **/
#define AT45DB161D_CONTINUOUS_READ_LEGACY 0x68
/** Status Register Read **/
#define AT45DB161D_STATUS_REGISTER_READ_LEGACY 0x57
/**
 * @}
 **/

/**
 * @}
 **/

#endif /* AT45DB161D_COMMANDS_H */
