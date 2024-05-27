#include "maze_layout.h"
#include "game.h"
#include "image.h"
#include "frame.h"
#include "../uart/uart0.h"
#include "../uart/uart1.h"
#include "utils.h"

#define RED 0xFFFF0000 // COLOR IN HEXA
#define WHITE 0xFFFFFFFF
#define BLUE 0xFF0000FF
#define CYAN 0xFF00FFFF
#define YELLOW 0xFFFFFF00
#define BLACK 0xFF000000
#define XLIM 40 // MAP LIMIT
#define YLIM 30


void drawMazeScreen(int screen_w, int screen_h, int steps){
	for(int y = 0; y < screen_h; y += steps){
		for(int x = 0; x < screen_w; x += steps){
			if(maze_map[0][(y/steps)*XLIM + (x/steps)] == 1){
				drawRectARGB32(x , y, x + steps, y + steps, BLUE, 1);
			}
			else if(maze_map[0][(y/steps)*XLIM + (x/steps)] == 4){
				drawRectARGB32(x , y, x + steps, y + steps, RED, 1);
			}
			else if(maze_map[0][(y/steps)*XLIM + (x/steps)] == 3){
				drawRectARGB32(x, y, x + steps, y + steps, YELLOW, 1);
			}
		}
	}
}
void drawWelcomeScreen(int screen_w, int screen_h) {
    drawString(32, 320, "AWSD to move left, right, up and down", BLUE, 2);
    drawString(32, 360, "J to scan ahead", BLUE, 2);
    drawImageARGB32(0, 0, 640, 240, screen_w, screen_h, epd_bitmap_wall_eye_welcome_screen);
}
//draw end game screen  --- done
void drawWinGameScreen(int screen_w, int screen_h) {
    drawRectARGB32(0,0, screen_w, screen_h, BLACK, 1);
	drawString(160, 200, "YOU FINISH THE MAZE", BLUE, 2);
}

void playGame(){
    int current_level = 0;
    int screen_w = 640;
    int screen_h = 480;
    int steps = 16;
    int x1 = 0;
    int y1 = 0;
    int x2 = steps;
    int y2 = steps;
    int char_col = WHITE;

    int spawn_x = 0;
    int spawn_y = 0;
    int goal_x = 0;
    int goal_y = 0;

    // Function to get value from maze map
    int getMazeValue(int level, int x, int y) {
        return maze_map[level][y * XLIM + x];
    }

    // Function to set value in maze map
    void setMazeValue(int level, int x, int y, int value) {
        maze_map[level][y * XLIM + x] = value;
    }

    // Find spawn and goal positions
    for (int i = 0; i < XLIM; i++) {
        for (int j = 0; j < YLIM; j++) {
            if (getMazeValue(current_level, i, j) == 1) {
                spawn_x = i * steps;
                spawn_y = j * steps;
            }
            if (getMazeValue(current_level, i, j) == 3) {
                goal_x = i * steps;
                goal_y = j * steps;
            }
        }
    }

    x1 = spawn_x;
    y1 = spawn_y;
    x2 = x1 + steps;
    y2 = y1 + steps;

    char c = ' ';
    uart_init();
    uart_puts("\n\nHello World!\n");
    uart_puts("Game is playing ...\n");
    uart_puts("Press q to stop ");
    framebf_init(screen_w, screen_h);
    drawWelcomeScreen(screen_w, screen_h);
    c = getUart();
    if (c != 0) {
        drawRectARGB32(0, 0, screen_w, screen_h, BLACK, 1);
        drawMazeScreen(screen_w, screen_h, steps);
        drawRectARGB32(x1, y1, x2, y2, char_col, 1);
    }

    while (1) {
        c = getUart();
        drawRectARGB32(x1, y1, x2, y2, BLACK, 1);
        int new_x1 = x1, new_y1 = y1, new_x2 = x2, new_y2 = y2;

        if (c == 's' && y1 < (YLIM - 1) * steps) {
            new_y1 += steps;
            new_y2 += steps;
        } else if (c == 'w' && y1 >= steps) {
            new_y1 -= steps;
            new_y2 -= steps;
        } else if (c == 'd' && x1 < (XLIM - 1) * steps) {
            new_x1 += steps;
            new_x2 += steps;
        } else if (c == 'a' && x1 >= steps) {
            new_x1 -= steps;
            new_x2 -= steps;
        } else if (c == 'q') {
            break;
        }

        int grid_x = new_x1 / steps;
        int grid_y = new_y1 / steps;
        int value = getMazeValue(current_level, grid_x, grid_y);

        uart_puts("Tile positions: ");
        uart_dec(grid_x);
        uart_puts(", ");
        uart_dec(grid_y);
        uart_puts(", ");
        uart_dec(value);
        uart_puts("\n");

        if (value == 2 || value == 4) {
            setMazeValue(current_level, grid_x, grid_y, 4); // Highlight wall
            x1 = spawn_x;
            y1 = spawn_y;
            x2 = x1 + steps;
            y2 = y1 + steps;
            drawMazeScreen(screen_w, screen_h, steps);
        }else {
            x1 = new_x1;
            y1 = new_y1;
            x2 = new_x2;
            y2 = new_y2;
        }


        if (value == 3) {
            drawWinGameScreen(screen_w, screen_h);
            current_level++;
            if (current_level >= 3) {
                break; // Game completed
            }
            // Update spawn and goal positions for the new level
            for (int i = 0; i < XLIM; i++) {
                for (int j = 0; j < YLIM; j++) {
                    if (getMazeValue(current_level, i, j) == 1) {
                        spawn_x = i * steps;
                        spawn_y = j * steps;
                    }
                    if (getMazeValue(current_level, i, j) == 3) {
                        goal_x = i * steps;
                        goal_y = j * steps;
                    }
                }
            }
            x1 = spawn_x;
            y1 = spawn_y;
            x2 = x1 + steps;
            y2 = y1 + steps;
        }

        // Draw the maze
        for (int i = 0; i < XLIM; i++) {
            for (int j = 0; j < YLIM; j++) {
                int tile_value = getMazeValue(current_level, i, j);
                int color = BLACK;
                if (tile_value == 1) color = WHITE;
                if (tile_value == 2) color = BLACK;
                if (tile_value == 3) color = WHITE;
                if (tile_value == 4) color = RED;
                drawRectARGB32(i * steps, j * steps, (i + 1) * steps, (j + 1) * steps, color, 1);
            }
        }

        drawRectARGB32(x1, y1, x2, y2, char_col, 1);
        wait_msec(100);
    }
}

void drawImage() {
    int yi = 0; // initial y coordinate
    int yf = 0; // final y coordinate after getting input and move it
    char c = ' ';
    // set up serial console 
    uart_init();
    framebf_init(512, 384);
    drawImageARGB32(0, yi, 564, 564, 512, 384, epd_bitmap_sample);// initialize the image for TASK 1a
    //read each char
    uart_puts("Image is playing ...\n");
    uart_puts("Press q to stop ");
    //draw scrolling image
     //read each char
    while (1) {
        c = getUart();// get uart C
        if (c == 's') {
            if (yi >= 180) { // enabling scrolling only when correct keys is inputted or when the top corrdinated has not reach the edge of the image --- s = sccroll down
                yi = 180;
            }
            else {
                yi += 10;// change the coordinate, thus moving the image through the frame
            }
        }
        else if (c == 'w') { // w == scroll up 
            if (yi <= 0) {
                yi = 0;
            }
            else {
                yi -= 10;
            }
        }
        else if (c == 'q') { // exit condition
            break;
        }

        if (yf != yi) { // make sure either the input is valid to draw image, if nothing change then do not draw again


            //draw image at a section given y coordinate and image size and frame size
            drawImageARGB32(0, yi, 564, 564, 512, 384, epd_bitmap_sample);
            wait_msec(500);
            yf = yi; // get the previous coordinate
        }

        if (yf != yi) { // make sure either the input is valid to draw image, if nothing change then do not draw again

            //draw image at a section given y coordinate and image size and frame size
            drawImageARGB32(0, yi, 564, 564, 512, 384, epd_bitmap_sample);
            wait_msec(500);
            yf = yi; // get the previous coordinate
        }
    }
}
