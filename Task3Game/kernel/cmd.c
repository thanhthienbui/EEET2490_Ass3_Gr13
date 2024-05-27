#include "cmd.h"
#include "mbox.h"
#include "utils.h"
#include "video.h"
#include "string.h"
#include "../uart/uart0.h"
#include "../uart/uart1.h"
#include "frame.h"
#include "game.h"


/*#define RED 0xFFFF0000 // COLOR IN HEXA
#define WHITE 0xFFFFFFFF
#define BLUE 0xFF0000FF
#define CYAN 0xFF00FFFF
#define YELLOW 0xFFFFFF00
#define BLACK 0xFF000000
#define XLIM 40 // MAP LIMIT
#define YLIM 30*/

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

     // Display the confirmation message with the received command
    uart_puts("Press '");
    uart_sendc(command);
    uart_puts("' again to confirm your command\n");
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
        for (int i = 0; i < 15; i++) {
            // display each frame image
            display_frame_image(video_frame[i], x, y, 320,
                240 + y);
            wait_msec(100);
        }

        c = uart_get_char();
    }

    // Add message to announce the user
    uart_puts("\nStopping video ...\n");
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
            uart_puts("ACK\n"); // Acknowledge the command
            playFont();
            
        }
        else if (command == '2') {
            clearScreen();
            uart_puts("ACK\n"); // Acknowledge the command
            drawImage();
            
        }
        else if (command == '3')
        {
            clearScreen();
            uart_puts("ACK\n"); // Acknowledge the command
            playVideo(320, 240);
            
        }
        else if (command == '4')
        {
            clearScreen();
            uart_puts("ACK\n"); // Acknowledge the command
            playGame();
            
        }
        else if (command == '5')
        {
            uart_puts("ACK\n"); // Acknowledge the command
            clearScreen();
            
        }
        else
        {
            uart_puts("NAK\n"); // Negative acknowledgment for invalid command
            uart_puts("Invalid command. Please enter a command:");
        }
    }

}


