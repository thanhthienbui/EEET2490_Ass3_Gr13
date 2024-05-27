// ----------------------------------- framebf.c ------------------------------------- 
#include "mbox.h" 
#include "../uart/uart0.h"
#include "utils.h"
//Use RGBA32 (32 bits for each pixel) 
#define COLOR_DEPTH 32 
//Pixel Order: BGR in memory order (little endian --> RGB in byte order) 
#define PIXEL_ORDER 0 
//Screen info 
unsigned int width, height, pitch; 
/* Frame buffer address 
* (declare as pointer of unsigned char to access each byte) */ 
unsigned char *fb; 
/** 
* Set screen resolution to 1024x768 
*/ 
// 'test', 40x40px

void framebf_init(int f_width, int f_height) 
{ 
    mBuf[0] = 35*4; // Length of message in bytes 
    mBuf[1] = MBOX_REQUEST; 
    mBuf[2] = MBOX_TAG_SETPHYWH; //Set physical width-height 
    mBuf[3] = 8; // Value size in bytes 
    mBuf[4] = 0; // REQUEST CODE = 0 
    mBuf[5] = f_width; // Value(width) 
    mBuf[6] = f_height; // Value(height) 
    mBuf[7] = MBOX_TAG_SETVIRTWH; //Set virtual width-height 

    mBuf[8] = 8; 
    mBuf[9] = 0; 
    mBuf[10] = f_width; 
    mBuf[11] = f_height; 
 
    mBuf[12] = MBOX_TAG_SETVIRTOFF; //Set virtual offset 
    mBuf[13] = 8; 
    mBuf[14] = 0; 
    mBuf[15] = 0; // x offset 
    mBuf[16] = 0; // y offset 
 
    mBuf[17] = MBOX_TAG_SETDEPTH; //Set color depth 
    mBuf[18] = 4; 
    mBuf[19] = 0; 
    mBuf[20] = COLOR_DEPTH; //Bits per pixel 
 
    mBuf[21] = MBOX_TAG_SETPXLORDR; //Set pixel order 
    mBuf[22] = 4; 
    mBuf[23] = 0; 
    mBuf[24] = PIXEL_ORDER; 
 
    mBuf[25] = MBOX_TAG_GETFB; //Get frame buffer 
    mBuf[26] = 8; 
    mBuf[27] = 0; 
    mBuf[28] = 16; //alignment in 16 bytes 
    mBuf[29] = 0;  //will return Frame Buffer size in bytes 
 
    mBuf[30] = MBOX_TAG_GETPITCH; //Get pitch 
    mBuf[31] = 4; 
    mBuf[32] = 0; 
    mBuf[33] = 0; //Will get pitch value here 
 
    mBuf[34] = MBOX_TAG_LAST; 
 
    // Call Mailbox 
    if (mbox_call(ADDR(mBuf), MBOX_CH_PROP) //mailbox call is successful ? 
    && mBuf[20] == COLOR_DEPTH //got correct color depth ? 
    && mBuf[24] == PIXEL_ORDER //got correct pixel order ? 
    && mBuf[28] != 0 //got a valid address for frame buffer ? 
    ) { 
 
     /* Convert GPU address to ARM address (clear higher address bits) 
      * Frame Buffer is located in RAM memory, which VideoCore MMU 
      * maps it to bus address space starting at 0xC0000000. 
      * Software accessing RAM directly use physical addresses 
      * (based at 0x00000000) 
     */ 
     mBuf[28] &= 0x3FFFFFFF; 
 
        // Access frame buffer as 1 byte per each address 
        fb = (unsigned char *)((unsigned long)mBuf[28]); 
        uart_puts("Got allocated Frame Buffer at RAM physical address: "); 
        uart_hex(mBuf[28]); 
        uart_puts("\n"); 
 
        uart_puts("Frame Buffer Size (bytes): "); 
        uart_dec(mBuf[29]); 
        uart_puts("\n"); 
 
        width = mBuf[5];      // Actual physical width 
        height = mBuf[6];      // Actual physical height 
        pitch = mBuf[33];       // Number of bytes per line 
 
    } else { 
        uart_puts("Unable to get a frame buffer with provided setting\n"); 
    };
} 
 
void drawPixelARGB32(int x, int y, unsigned int attr) 
{ 
    int offs = (y * pitch) + (COLOR_DEPTH/8 * x); 
 
/* //Access and assign each byte 
    *(fb + offs    ) = (attr >> 0 ) & 0xFF; //BLUE  (get the least significant byte) 
    *(fb + offs + 1) = (attr >> 8 ) & 0xFF; //GREEN 
    *(fb + offs + 2) = (attr >> 16) & 0xFF; //RED 
    *(fb + offs + 3) = (attr >> 24) & 0xFF; //ALPHA
*/ 
 
 //Access 32-bit together 
    *((unsigned int*)(fb + offs)) = attr; 
} 
 
void drawRectARGB32(int x1, int y1, int x2, int y2, unsigned int attr, int fill) { 
    for (int y = y1; y <= y2; y++ ) 
        for (int x = x1; x <= x2; x++) { 
            if ((x == x1 || x == x2) || (y == y1 || y == y2)) {
                drawPixelARGB32(x, y, attr); 
            }else if (fill) {
                drawPixelARGB32(x, y, attr); 
            }
  } 
}

void drawImageARGB32(int cur_x, int cur_y, int i_width, int i_height,int f_width, int f_height, const unsigned long* image_bit){ //x, y for image position, width height for frame & image size
    // TODO: modify it so that move image with through the frame, displlayed selection of image within the frame
    // by set frame origin point to a position in image and get the attributes in that index ()
    int xlim = i_width < f_width? i_width : f_width; // check which ever size is smaller, image or frame and take the smaller one
    int ylim = i_height < f_height? i_height : f_height;
    int index = (cur_y * i_width) + cur_x;// for the image, does not concern the limit of frame
    
    drawRectARGB32(0,0, xlim, ylim, 0x00000000, 1); // erase entire frame

    for(int y = 0; y < ylim; y++ ){ // iterate through width and height of image to draw
        for(int x = 0;  x < xlim; x++){
            drawPixelARGB32(x, y,image_bit[index + y*i_width + x]);
        }
    }
}

void display_frame_image(unsigned int frame_image[], int x, int y, int width, int height) {
    int num = 0;

    while (y < height) {
        for (x = 0; x < width; x++) {
            int offs = (y * pitch) + (x * 4);
            *((unsigned int*)(fb + offs)) = frame_image[num];
            num++;
        }
        y++;
        x = 0;
    }
}

/*void playVideoARGB32(int numframe, int cur_x, int cur_y, int video_width, int video_height, int frame_width, int frame_height, const unsigned long** vid_frame) {
    for (index = 0, index < numframe, index++) {
        drawImageARGB32(cur_x, cur_y, frame_width, frame_height, video_width, video_height, vid_frame[index]);
        wait_msec(1000);
    }
    wait_msec(1000);
}*/
