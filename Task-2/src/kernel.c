#include "./uart/uart1.h"
#include "./mbox/mbox.h"
#include "./framebf/framebf.h"
#include "./timer/timer.h"
#include "./timer/interrupt.h"


void main() {
    // set up serial console
    uart1_init();
    // say hello
    uart1_puts("\n\nTimer 1 received: .\n");
    framebf_init();
    timer_init();
    handle_timer_1();
    while (1) {

    }
}