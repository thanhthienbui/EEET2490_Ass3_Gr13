#include "mbox.h"
#include "../uart/uart0.h"
#include "../uart/uart1.h"
#include "frame.h" 
#include "utils.h" 
#include "image.h" 
#include "video.h"
// 'sample', 564x564px
void playVideo(int x, int y);
void drawImage();
void playFont();
void clearScreen();
void displayOptions();
void execute();


void main() {
    uart_init();
    uart_puts("\n\nHello World!\n");
    framebf_init(1024, 768);
    while (1) {
        execute();
    }
}

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

void displayOptions() {
    uart_puts(
        "\n\n\tEnter a command:\n"
        "\t1.\tDisplay text on screen\n"
        "\t2.\tDisplay image on screen\n"
        "\t3.\tDisplay a video\n"
    );
}

void execute(){
    while (1) {
        displayOptions();
        uart_puts("MyOS>>> ");

        char command = uart_getc();


        uart_sendc(command);
        uart_sendc('\n');

        if (command == '1') {
            clearScreen();
            playFont();
        }
        else if (command == '2') {
            clearScreen();
            drawImage();
        }
        else if (command == '3')
        {
            clearScreen();
            playVideo(320, 240);
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
    uart_puts("Press s to stop ");
    char c = uart_get_char();
    // Keep displaying the video until the user press s
    while (c != 's') {
        // // loop through all the frame image video
        for (int i = 0; i < 15; i++) {
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


            //draw image at a section given y coordinate and image size and frame size
            drawImageARGB32(0, yi, 564, 564, 512, 384, epd_bitmap_sample);
            yf = yi; // get the previous coordinate
            wait_msec(500);
        }

    }
}


