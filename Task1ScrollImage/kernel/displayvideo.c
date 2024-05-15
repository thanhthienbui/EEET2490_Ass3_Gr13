#include "displayvideo.h" 
#include "../uart/uart1.h"
#include "utils.h"
#include "video.h"


void displayVideo(int x, int y) {
    // Add message to prompt the user how to use
    uart_puts("Video is playing ...\n");
    uart_puts("Press s to stop ");
    char character = uart_get_char();
    // Keep displaying the video until the user press s
    while (character != 's') {
        // // loop through all the frame image video
        for (int i = 0; i < 15; i++) {
            // display each frame image
            display_frame_image(video[i], x, y, video_width,
                                video_height + y);
            video_wait_ms(100000);
        }
        character = uart_get_char();
    }

    // Add message to announce the user
    uart_puts("\nStopping video ...");
}
