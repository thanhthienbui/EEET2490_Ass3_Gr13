
#include "../uart/uart0.h"
#include "../uart/uart1.h"
#include "frame.h" 
#include "utils.h" 
#include "cmd.h"
/*#define RED 0xFFFF0000 // COLOR IN HEXA
#define WHITE 0xFFFFFFFF
#define BLUE 0xFF0000FF
#define CYAN 0xFF00FFFF
#define YELLOW 0xFFFFFF00
#define BLACK 0xFF000000*/
//#define XLIM 3 // MAP LIMIT
//#define YLIM 3
//draw welcome screen --- done
/*void drawWelcomeScreen(int screen_w, int screen_h){
	drawString(32, 320, "AWSD to move left, right, up and down", BLUE, 2);
	drawString(32, 360, "J to scan ahead", BLUE, 2);
	drawImageARGB32(0,0, 640, 240, screen_w, screen_h, epd_bitmap_wall_eye_welcome_screen);
}
//draw end game screen  --- done
void drawWinGameScreen(int screen_w, int screen_h){
	drawString(160, 200, "YOU FINISH THE MAZE", BLUE, 2);
}

void main(){
	int maze_map[XLIM][YLIM] = {{0,1,0}, {0,0,0}, {0,2,0}}; // can be put into another header file
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
	c = getUart();// get uart C
	if(c != 0){
		drawRectARGB32(0, 0, screen_w, screen_h, BLACK, 1);
		drawRectARGB32(x1, y1, x2, y2, char_col, 1);
	}

	while(1){
		//read each char
		c = getUart();// get uart C

		drawRectARGB32(x1, y1, x2, y2, BLACK, 1);
		if(c == 's'){
			if(y1 < 2 * steps){
				y1 += steps;
				y2 += steps;
			}

		}
		else if(c == 'w'){ // w == scroll up
			if(y1 >= steps){
				y1 -= steps;
				y2 -= steps;
			}
		}
		else if(c == 'd'){
			if(x1 < 2 * steps){
				x1 += steps;
				x2 += steps;
			}
		}
		else if(c == 'a'){ // w == scroll up
			if(x1 >= steps){
				x1 -= steps; // real steps
				x2 -= steps;
			}
		}


		int value = maze_map[x1/steps][y1/steps]; // get the value in maze_map
		uart_puts("Tile positions: "); // debugging
		uart_dec(x1/steps);
		uart_puts(", ");
		uart_dec(y1/steps);
		uart_puts(", ");
		uart_dec(value);
		uart_puts("\n");

		if(value == 2){ // testing check value of tile location, if value == 2 then it is walls
			drawWinGameScreen(screen_w, screen_h);
			break;
		}
		drawRectARGB32(x1, y1, x2, y2, char_col, 1);
		wait_msec(100);
	}
}*/
void main() {
	// set up serial console 
	uart_init();
	framebf_init(1024, 768);

	while (1) {
		execute();
	}
}

/*void main() {
	// set up serial console 
	uart_init();
	framebf_init(1024, 768);

	while (1) {
		drawMaze(0,40,30);
	}
}*/

