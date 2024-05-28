#include "game.h"
#include "maze_layout.h"
#include "utils.h"
#include "image.h"
#include "../uart/uart0.h"
#include "../uart/uart1.h"
#include "frame.h"
#include "cmd.h"
#include "sys_timer.h"



#define RED 0xFFFF0000 // COLOR IN HEXA
#define WHITE 0xFFFFFFFF
#define BLUE 0xFF0000FF
#define CYAN 0xFF00FFFF
#define YELLOW 0xFFFFFF00
#define BLACK 0xFF000000
#define XLIM 40 // MAP LIMIT
#define YLIM 30

void drawWelcomeScreen(int screen_w, int screen_h) {
    drawString(32, 320, "AWSD to move left, right, up and down", BLUE, 2);
    drawString(32, 360, "J to scan ahead", BLUE, 2);
    drawImageARGB32(0, 0, 640, 240, screen_w, screen_h, epd_bitmap_wall_eye_welcome_screen);
}
//draw end game screen  --- done
void drawWinGameScreen(int screen_w, int screen_h) {
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


    // Initialize the timer
    timer_init();
    // Define the tick frequency (e.g., 1 tick per microsecond)
    uint64_t tick_frequency = 1000000;
    // Function to get value from maze map
    int getMazeValue(int level, int x, int y){
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
        drawRectARGB32(x1, y1, x2, y2, char_col, 1);
    }

    uint64_t start_tick = 0;
    uint64_t end_tick = 0;

    while (1) {
        c = getUart();
        drawRectARGB32(x1, y1, x2, y2, BLACK, 1);
        int new_x1 = x1, new_y1 = y1, new_x2 = x2, new_y2 = y2;

        if (c == 's' && y1 < (YLIM - 1) * steps) {
            new_y1 += steps;
            new_y2 += steps;
            logCommand(c);
        } else if (c == 'w' && y1 >= steps) {
            new_y1 -= steps;
            new_y2 -= steps;
            logCommand(c);
        } else if (c == 'd' && x1 < (XLIM - 1) * steps) {
            new_x1 += steps;
            new_x2 += steps;
            logCommand(c);
        } else if (c == 'a' && x1 >= steps) {
            new_x1 -= steps;
            new_x2 -= steps;
            logCommand(c);
        } else if (c == 'q') {
            break;
        }

        // Record the start time before movement
        start_tick = timer_get_tick();

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
                if (tile_value == 3) color = CYAN;
                if (tile_value == 4) color = RED;
                drawRectARGB32(i * steps, j * steps, (i + 1) * steps, (j + 1) * steps, color, 1);
            }
        }

        drawRectARGB32(x1, y1, x2, y2, char_col, 1);

        // Record the end time after movement
        end_tick = timer_get_tick();

        // Calculate elapsed time
        uint64_t elapsed_ticks = end_tick - start_tick;
        uint64_t elapsed_time = (elapsed_ticks * 1000) / tick_frequency;
        uart_puts("Elapsed time: ");
        uart_dec(elapsed_time);
        uart_puts(" m/s\n");


        wait_msec(100);
    }
}

