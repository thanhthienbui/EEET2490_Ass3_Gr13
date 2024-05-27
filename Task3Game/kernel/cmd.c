#include "cmd.h"
#include "mbox.h"
#include "image.h"
#include "utils.h"
#include "video.h"
#include "string.h"
#include "../uart/uart0.h"
#include "../uart/uart1.h"
#include "frame.h"


#define RED 0xFFFF0000 // COLOR IN HEXA
#define WHITE 0xFFFFFFFF
#define BLUE 0xFF0000FF
#define CYAN 0xFF00FFFF
#define YELLOW 0xFFFFFF00
#define BLACK 0xFF000000
#define XLIM 3 // MAP LIMIT
#define YLIM 3

// Game state variables
int command_count = 0;
char uart_config[100] = "Default UART Config"; // Placeholder for actual UART config
void displayOptions() {
    uart_puts(
        "\n\n\tEnter a command:\n"
        "\t1.\tDisplay text on screen\n"
        "\t2.\tDisplay image on screen\n"
        "\t3.\tDisplay a video\n"
        "\t4.\tPlay game\n"
        "\t5.\tClear the screen\n"
    );
}

void logCommand(char command) {
    // Increment the command count
    command_count++;

    // Log the received command to the UART terminal
    uart_puts("Command received: ");
    uart_sendc(command);
    uart_puts("\n");

    // Display the total number of commands received so far
    uart_puts("Total commands received: ");
    uart_dec(command_count);
    uart_puts("\n");

    // Display the current UART configuration
    uart_puts("Current UART config: ");
    uart_puts(uart_config);
    uart_puts("\n");
}

// Clear screen (monitor)
void clearScreen()
{
    framebf_init(1024, 768);
    for (int i = 0; i < 1024; i++)
    {
        for (int j = 0; j < 768; j++)
        {
            drawPixelARGB32(i, j, 0x00000000);
        }
    }
}

void playFont() {
    // set up serial console 
    // say hello 
    framebf_init(1024, 768);
    drawString(100, 100, "Nguyen Quang Nhat", 0x00FFFFFF, 3);
    drawString(100, 200, "Pham Quang Huy", 0x00FFFF00, 3);
    drawString(100, 300, "Do Manh Huy Hoang", 0x00FF00FF, 3);
    drawString(100, 400, "Bui Hong Thanh Thien", 0x0000FFFF, 3);

}

void drawImage() {
    int yi = 0; // initial y coordinate
    int yf = 0; // final y coordinate after getting input and move it
    char c = ' ';
    // set up serial console 
    uart_init();
    // say hello
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
            //output getUART results for trouble shooting
            //uart_puts("y: "); // get Y coordinate of the image
            //uart_dec(yi); 
            //uart_sendc('\n');

            //draw image at a section given y coordinate and image size and frame size
            drawImageARGB32(0, yi, 564, 564, 512, 384, epd_bitmap_sample);
            wait_msec(500);
            yf = yi; // get the previous coordinate
        }

        if (yf != yi) { // make sure either the input is valid to draw image, if nothing change then do not draw again
            //output getUART results for trouble shooting
            //uart_puts("y: "); // get Y coordinate of the image
            //uart_dec(yi); 
            //uart_sendc('\n');
            //draw image at a section given y coordinate and image size and frame size
            drawImageARGB32(0, yi, 564, 564, 512, 384, epd_bitmap_sample);
            wait_msec(500);
            yf = yi; // get the previous coordinate
        }
    }
}



void playVideo(int x, int y) {
    // set up serial console  
    framebf_init(1024, 768);
    // Add message to prompt the user how to use
    uart_puts("Video is playing ...\n");
    uart_puts("Enter any letter for the video to play\n");
    uart_puts("Press s to stop ");
    char c = uart_get_char();
    // Keep displaying the video until the user press s
    while (c != 's') {
        // // loop through all the frame image video
        for (int i = 0; i < 5; i++) {
            // display each frame image
            display_frame_image(video_frame[i], x, y, 320,
                240 + y);
            wait_msec(1000);
        }
        c = uart_get_char();
    }

    // Add message to announce the user
    uart_puts("\nStopping video ...\n");
}
void drawWelcomeScreen(int screen_w, int screen_h) {
    drawString(32, 320, "AWSD to move left, right, up and down", BLUE, 2);
    drawString(32, 360, "J to scan ahead", BLUE, 2);
    drawImageARGB32(0, 0, 640, 240, screen_w, screen_h, epd_bitmap_wall_eye_welcome_screen);
}
//draw end game screen  --- done
void drawWinGameScreen(int screen_w, int screen_h) {
    drawString(160, 200, "YOU FINISH THE MAZE", BLUE, 2);
}


void playGame() {
    int maze_map[XLIM][YLIM] = { {0,1,0}, {0,0,0}, {0,2,0} }; // can be put into another header file
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
    uart_puts("Game is playing ...\n");
    uart_puts("Press q to stop ");
    framebf_init(screen_w, screen_h);
    drawWelcomeScreen(screen_w, screen_h);
    c = getUart();// get uart C
    if (c != 0) {
        drawRectARGB32(0, 0, screen_w, screen_h, BLACK, 1);
        drawRectARGB32(x1, y1, x2, y2, char_col, 1);
    }

    while (1) {
        //read each char
        c = getUart();// get uart C

        drawRectARGB32(x1, y1, x2, y2, BLACK, 1);
        if (c == 's') {
            if (y1 < 2 * steps) {
                y1 += steps;
                y2 += steps;
            }

        }
        else if (c == 'w') { // w == scroll up 
            if (y1 >= steps) {
                y1 -= steps;
                y2 -= steps;
            }
        }
        else if (c == 'd') {
            if (x1 < 2 * steps) {
                x1 += steps;
                x2 += steps;
            }
        }
        else if (c == 'a') { // w == scroll up 
            if (x1 >= steps) {
                x1 -= steps; // real steps
                x2 -= steps;
            }
        }
        else if (c == 'q') { // exit condition
            break;
        }

        int value = maze_map[x1 / steps][y1 / steps]; // get the value in maze_map		
        uart_puts("Tile positions: "); // debugging
        uart_dec(x1 / steps);
        uart_puts(", ");
        uart_dec(y1 / steps);
        uart_puts(", ");
        uart_dec(value);
        uart_puts("\n");

        if (value == 2) { // testing check value of tile location, if value == 2 then it is walls
            drawWinGameScreen(screen_w, screen_h);
            break;
        }
        drawRectARGB32(x1, y1, x2, y2, char_col, 1);
        wait_msec(100);
    }
}




void execute() {
    clearScreen();

    while (1) {
        displayOptions();
        uart_puts("MyOS>>> ");

        char command = uart_getc();
        logCommand(command); // Log the command

        command = uart_getc();

        uart_sendc(command);
        uart_sendc('\n');

        if (command == '1') {
            clearScreen();
            playFont();
            uart_puts("ACK\n"); // Acknowledge the command
        }
        else if (command == '2') {
            clearScreen();
            drawImage();
            uart_puts("ACK\n"); // Acknowledge the command
        }
        else if (command == '3')
        {
            clearScreen();
            playVideo(320, 240);
            uart_puts("ACK\n"); // Acknowledge the command
        }
        else if (command == '4')
        {
            clearScreen();
            playGame();
            uart_puts("ACK\n"); // Acknowledge the command
        }
        else if (command == '5')
        {
            clearScreen();
            uart_puts("ACK\n"); // Acknowledge the command
        }
        else
        {
            uart_puts("NAK\n"); // Negative acknowledgment for invalid command
            uart_puts("Invalid command. Please enter a command:");
        }
    }

}


