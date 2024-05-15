#include "mbox.h"
#include "../uart/uart0.h"
#include "../uart/uart1.h"
#include "frame.h" 
#include "utils.h" 
#include "image.h" 
// 'sample', 564x564px

void main() { 
    int yi = 0; // initial y coordinate
	int yf = 0; // final y coordinate after getting input and move it
	
	char c = ' ';
    // set up serial console 
    uart_init(); 
    // say hello 
    uart_puts("\n\nHello World!\n"); 
    // Initialize frame buffer with set frame size 
    framebf_init(512, 384); 
    drawImageARGB32(0, yi, 564, 564, 512, 384, epd_bitmap_sample);// initialize the image for TASK 1a

    while(1){ //draw scrolling image
        //read each char
		c = getUart();// get uart C
		if(c == 's'){
			if(yi >= 180 ){ // limit of the picture
				yi = 180;
			}
			else{
				yi += 10;
			}
		}
		else if(c == 'w'){
			if(yi <= 0 ){
				yi = 0;
			}
            else{
				yi -= 10;
			}
		}

		if(yf != yi){ // make sure either the input is valid or there is space in the image to move down
			 //draw Image in new scan
			uart_puts("y: "); // get Y coordinate of the image
			uart_dec(yi);
			uart_sendc('\n');

			//draw image at a section given y coordinate and image size and frame size
			drawImageARGB32(0, yi, 564, 564, 512, 384, epd_bitmap_sample);
			wait_msec(500);
			yf = yi;
		}
       
    } 
}

void video()
{
	uart_init();
	framebf_init(VID_WIDTH, VID_HEIGH);

	int frame = 0;
	int cycle = 0;
	while (1)
	{
		// Sketch each frame
		for (int y = 0; y < VID_HEIGH; y++)
		{ // height
			for (int x = 0; x < VID_WIDTH; x++)
			{ // width
				drawPixelARGB32(x, y, video_frame[frame][y * VID_WIDTH + x]);
			}
		}

		// Move to the next frame
		frame++;

		// Display again all the frames
		if (frame == 1)
		{
			frame = 0;
			cycle++;
		}

		// Display video 5 times
		if (cycle == 3)
		{
			break;
		}
		wait_msec(100000);
	}
}

/*
void main(){// displaying character
	char c = ' ';
    // set up serial console 
    uart_init(); 
    // say hello 
    uart_puts("\n\nHello World!\n"); 
    // Initialize frame buffer with set frame size 
    framebf_init(1024, 768); 
    drawString(100, 100, "Nguyen Quang Nhat", 0x00FFFFFF, 3);
	drawString(100, 200, "Pham Quang Huy", 0x00FFFF00, 3);
	drawString(100, 300, "Do Manh Huy Hoang", 0x00FF00FF, 3);
	drawString(100, 400, "Bui Hong Thanh Thien", 0x0000FFFF, 3);
	while (1)
	{
	}
}
*/

