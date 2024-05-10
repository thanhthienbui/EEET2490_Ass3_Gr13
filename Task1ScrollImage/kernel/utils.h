void drawChar(unsigned char ch, int x, int y, unsigned int attr, int zoom);
void drawString(int x, int y, char *str, unsigned int attr, int zoom);
/* New function for Uart: Check and return if no new character, don't wait */
unsigned int uart_isReadByteReady();
unsigned char getUart();
/* Functions to delay, set/wait timer */
void wait_msec(unsigned int n);
void set_wait_timer(int set, unsigned int msVal);
