#include "mbox.h"
#include "../uart/uart0.h"
#include "../uart/uart1.h"
#include "frame.h" 
#include "utils.h" 
#include "image.h"
#include "video.h"
#define RED 0xFFFF0000
#define WHITE 0xFFFFFFFF
#define BLUE 0xFF0000FF
#define CYAN 0xFF00FFFF
#define YELLOW 0xFFFFFF00

void drawWelcomeScreen(int screen_w, int screen_h){
	drawString(32, 320, "Presss A W D S", 0x00ffFF, 5);
	drawString(32, 360, "to start", 0x00ffff, 5);
	drawImageARGB32(0,0, 640, 240, screen_w, screen_h, epd_bitmap_wall_eye_welcome_screen);
}

void main(){
	//int BIT_MAP[3][3] = {{0,1,0}, {0,0,0}, {0,2,0}};
	int screen_w = 640;
    int screen_h = 480;
	int steps = 16;
    int x1 = 0;
    int y1 = 0;
	int x2 = steps;
	int y2 = steps;
	int char_col = WHITE;

	char c = ' ';
    // set up serial console 
    uart_init(); 
    // say hello 
    uart_puts("\n\nHello World!\n"); 
    // Initialize frame buffer with set frame size 
    framebf_init(screen_w, screen_h); 
	drawWelcomeScreen(screen_w, screen_h);
    while(1){
        //read each char
		c = getUart();// get uart C
		
		drawRectARGB32(x1, y1, x2, y2, 0xFF000000, 1);
		if(c == 's'){
			y1 += steps;
			y2 += steps;
		}
		else if(c == 'w'){ // w == scroll up 
           	y1 -= steps;
			y2 -= steps;
		}
		else if(c == 'd'){
			x1 += steps;
			x2 += steps;
		}
		else if(c == 'a'){ // w == scroll up 
			x1 -= steps;
			x2 -= steps;
		}	
		uart_puts("Tile positions: ");
		uart_dec(x1/steps);
		uart_puts(", ");
		uart_dec(y1/steps);
		uart_puts("\n");

		if(x1/steps == 1 && y1/steps == 1){
			char_col = RED;
		}
		else{
			char_col = WHITE;
		}
		drawRectARGB32(x1, y1, x2, y2, char_col, 1);
		wait_msec(100);
		
    }
}
