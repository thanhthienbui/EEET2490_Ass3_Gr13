// -----------------------------------mbox.h -------------------------------------
#include "../gpio.h"
/* a properly aligned buffer */
extern volatile unsigned int mBuf[36];
extern volatile unsigned int mBuf_2[36];

#define ADDR(X) (unsigned int)((unsigned long)X)

/* Registers */
#define VIDEOCORE_MBOX (MMIO_BASE + 0x0000B880)
// Mbox0 = VC -> ARM
#define MBOX0_READ (*(volatile unsigned int *)(VIDEOCORE_MBOX + 0x00))
#define MBOX0_PEEK (*(volatile unsigned int *)(VIDEOCORE_MBOX + 0x10))
#define MBOX0_SENDER (*(volatile unsigned int *)(VIDEOCORE_MBOX + 0x14))
#define MBOX0_STATUS (*(volatile unsigned int *)(VIDEOCORE_MBOX + 0x18))
#define MBOX0_CONFIG (*(volatile unsigned int *)(VIDEOCORE_MBOX + 0x1C))
// Mbox1 = ARM -> VC
#define MBOX1_WRITE (*(volatile unsigned int *)(VIDEOCORE_MBOX + 0x20))
#define MBOX1_PEEK (*(volatile unsigned int *)(VIDEOCORE_MBOX + 0x30))
#define MBOX1_SENDER (*(volatile unsigned int *)(VIDEOCORE_MBOX + 0x34))
#define MBOX1_STATUS (*(volatile unsigned int *)(VIDEOCORE_MBOX + 0x38))
#define MBOX1_CONFIG (*(volatile unsigned int *)(VIDEOCORE_MBOX + 0x3C))

// Request/Response code in Buffer content
#define MBOX_RESPONSE 0x80000000
#define MBOX_REQUEST 0

// Status Value (from Status Register)
#define MBOX_FULL 0x80000000
#define MBOX_EMPTY 0x40000000

/* channels */
#define MBOX_CH_POWER 0 // Power management
#define MBOX_CH_FB 1    // Frame buffer
#define MBOX_CH_VUART 2 // Virtual UART
#define MBOX_CH_VCHIQ 3 // VCHIQ
#define MBOX_CH_LEDS 4  // LEDs
#define MBOX_CH_BTNS 5  // Buttons
#define MBOX_CH_TOUCH 6 // Touch screen
#define MBOX_CH_PROP 8  // Property tags (ARM -> VC)
#define MBOX_CH_PROP_VC_ARM 9 // Property tags (VC -> ARM) (new)

/* tags */
#define MBOX_TAG_GETSERIAL 0x00010004 // Get board serial
#define MBOX_TAG_GETMODEL 0x00010001  // Get board model
#define MBOX_TAG_SETCLKRATE 0x00038002
#define MBOX_TAG_LAST 0

// additional tag
#define MBOX_TAG_FIRMWARE_REVISION 0x00000001
#define MBOX_TAG_BOARDMODEL 0x00010001
#define MBOX_TAG_BOARD_REVISION 0x00010002
#define MBOX_TAG_MAC_ADDRESS 0x00000001
#define MBOX_TAG_BOARD_SERIAL 0x00010004
#define MBOX_TAG_ARM_MEMORY 0x00010005
#define MBOX_TAG_GETCLKRATE 0x00030002
// Clock IDs
#define CLK_ID_UART 0x000000002
#define CLK_ID_ARM 0x000000003
#define CLK_ID_CORE 0x000000004


// display tags
#define MBOX_TAG_SETPHYWH   0x00048003
#define MBOX_TAG_SETVIRTWH  0x00048004
#define MBOX_TAG_SETVIRTOFF 0x00048009
#define MBOX_TAG_SETDEPTH   0x00048005
#define MBOX_TAG_SETPXLORDR 0x00048006
#define MBOX_TAG_GETFB      0x00040001
#define MBOX_TAG_GETPITCH   0x00040008

/* Function Prototypes */
int mbox_call(unsigned int buffer_addr, unsigned char channel);
uint32_t mailbox_read(unsigned char channel);
void mailbox_send(uint32_t msg, unsigned char channel);
