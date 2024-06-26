// -----------------------------------uart.c -------------------------------------
#include "mini_uart1.h"
#include "../gpio.h"
/**
* Set baud rate and characteristics (115200 8N1) and map to GPIO
*/
void uart1_init() {
    unsigned int r;
    /* initialize UART */
    AUX_ENABLE = 1;    //enable mini UART (UART1)
    AUX_MU_CNTL = 0;    //stop transmitter and receiver
    AUX_MU_LCR = 3;     //8-bit mode (also enable bit 1 to be used for RBP3)
    AUX_MU_MCR = 0;     //clear RTS (request to send)
    AUX_MU_IER = 0xD;   //enable receive interrupt
    // AUX_MU_IIR = 0xC6;  //enable and clear receive and transmit FIFOs (0xC6 = 0b11000110)
    AUX_MU_IIR = 0xC4;
    // system clock frequency = 250 MHz = 250*10^6 Hz
    AUX_MU_BAUD = 270;  //configure 115200 baud [system_clk_freq/(baud_rate*8) - 1]
    /* map UART1 to GPIO pins 14 and 15 */
    r = GPFSEL1;
    r &= ~( (7 << 12)|(7 << 15) ); //clear bits 17-12 (FSEL15, FSEL14)
    r |= (2 << 12)|(2 << 15); //set value 2 (select ALT5: TXD1/RXD1)
    GPFSEL1 = r;
    /* enable GPIO 14, 15 */
    GPPUD = 0; //No pull up/down control
    r = 150; 
    while(r--) { 
        asm volatile("nop"); 
    } //waiting 150 cycles
    GPPUDCLK0 = (1 << 14)|(1 << 15); //enable clock for GPIO 14, 15
    r = 150; 
    while(r--) { 
        asm volatile("nop"); 
    } //waiting 150 cycles
    GPPUDCLK0 = 0; //flush GPIO setup
    AUX_MU_CNTL = 3; //enable transmitter and receiver (Tx, Rx)
}
/**
* Send a character
*/
void uart1_sendc(char c) {
    // wait until transmitter is empty
    do {
        asm volatile("nop");
    } while ( !(AUX_MU_LSR & 0x20) );
    // write the character to the buffer
    AUX_MU_IO = c;
}
/**
* Receive a character
*/
char uart1_getc() {
    char c;
    // wait until data is ready (one symbol)
    do {
        asm volatile("nop");
    } while ( !(AUX_MU_LSR & 0x01) );
    // read it and return
    c = (unsigned char)(AUX_MU_IO);
    // convert carriage return to newline character
    return (c == '\r' ? '\n' : c);
}
/**
* Display a string
*/
void uart1_puts(char *s) {
    while (*s) {
    // convert newline to carriage return + newline
        if (*s == '\n') { 
            uart1_sendc('\r');
        }
        uart1_sendc(*s++);
    }
}

void uart1_hex(unsigned int num) {
	uart1_puts("0x");
	for (int pos = 28; pos >= 0; pos = pos - 4) {
		// Get highest 4-bit nibble
		char digit = (num >> pos) & 0xF;
		/* Convert to ASCII code */
		// 0-9 => '0'-'9', 10-15 => 'A'-'F'
		digit += (digit > 9) ? (-10 + 'A') : '0';
		uart1_sendc(digit);
	}
}
/**
 * Display a value in decimal format
 */
void uart1_dec(int num) {
	// A string to store the digit characters
	char str[33] = "";
	// Calculate the number of digits
	int len = 1;
	int temp = num;
	while (temp >= 10) {
		len++;
		temp = temp / 10;
	}
	// Store into the string and print out
	for (int i = 0; i < len; i++) {
		int digit = num % 10; // get last digit
		num = num / 10;		  // remove last digit from the number
		str[len - (i + 1)] = digit + '0';
	}
	str[len] = '\0';
	uart1_puts(str);
}

void uart1_bi(unsigned int num) {
    int count = 0;
    uart1_puts("0b ");
    for (int pos = 31; pos >= 0; pos--) {
        // Get highest 4-bit nibble
        char digit = (num >> pos) & 0x1;
        /* Convert to ASCII code */
        // 0-1 => '0'-'1'
        digit += '0';
        uart1_sendc(digit);
        count++;
        if (count >= 4) {
            uart1_sendc(' ');
            count = 0;
        }
    }
}
void get_add() {
    uart1_puts("\nAddress AUX_MU_IO: ");
    uart1_hex((unsigned int)(AUX_MU_IO));
    uart1_puts("\n");
    // uart1_hex((unsigned int)&ENABLE_IRQS_1);
}