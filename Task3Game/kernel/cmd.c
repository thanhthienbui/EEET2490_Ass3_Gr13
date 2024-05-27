#include "cmd.h"
#include "mbox.h"
#include "utils.h"
#include "video.h"
#include "string.h"
#include "../uart/uart0.h"
#include "../uart/uart1.h"
#include "game.h"
#include "frame.h"





// Game state variables
int command_count = 0;
char uart_config[100] = "Default UART Config"; // Placeholder for actual UART config
void displayOptions() {
    uart_puts(
        "\n\n\tEnter a command:\n"
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
        if (command == '4')
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


