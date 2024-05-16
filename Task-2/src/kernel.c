#include "./uart/uart0.h"
#include "./irq/irq.h"
#include "./timer/timer.h"
// #include "./mbox/mbox.h"
// #include "./framebf/framebf.h"
// #include "./timer/timer.h"
// #include "./timer/interrupt.h"


void main() {
    // set up serial console
    uart0_init();
    uart0_puts("\nProgram begin\n");
    
    timer_1_init(4000000);
    handle_timer_1();

    // enable_irq();
    // handle_irq();
    // say hello
    // uart0_puts("\n\nTimer 1 received: .\n");
    // framebf_init();
    // timer_init();
    // handle_timer_1();
    while (1) {
        char c = uart0_getc();
        uart0_sendc(c);
        // handle_timer_1();
    }
}