/*
THIS IS ADDRESS AND COMMAND BYTES FOR CONTROLLING 
THE AVAGO APDS-9301 MINIATURE AMBIENT LIGHT SENSOR I2C OUTPUT
SENSOR IS ADDRESS SELECTABLE WITH EXTERNAL ADDR PIN
ADDR = GND =   0101001x
ADDR = FLOAT = 0111001x
ADDR = VDD =   1001001x  i'm using this address!
SENSOR SUPPORTS I2C WORD READ AND WORD WRITE COMMANDS
*/

#define  ADPS       0x39  //7 BIT address of ADPS-9301 with ADDR pin tied to Vdd
#define  CNTRL      0x80  //control register. write 0x03=power up, 0h00=power down
#define  TIMNG      0x81  //4=GAIN; 3=MANUAL; 1:0=INTEGRATION TIMING
#define  THRESH_LL  0x82  //these are interrupt threshold registers
#define  THRESH_LH  Ox83  //there is a low light level interrupt
#define  THRESH_HL  Ox84  //and a high level interrupt.
#define  THRESH_HH  0x85  //write values here to use them.
#define  I_CNTRL    0x86  //5:4=INT CONTROL; 3:0=INT PERSISTENCE 
#define  ID_REVNO   0x8A  //7:4=PART NUMBER; 3:0=REVISION NUMBER
#define  D0_LOW     0x8C  //Data Channel 0 low byte
#define  D0_HIGH    0x8D  //Data Channel 0 high byte
#define  D1_LOW     0x8E  //Data Channel 1 low byte
#define  D1_HIGH    0x8F  //Data Channel 1 high byte
#define  DC0        0xAC  //used to read entire word of Data Channel 0
#define  DC1        0xAE  //used to read entire word of Data Channel 1