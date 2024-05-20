#include "./uart/uart1.h"
#include "./irq/irq.h"
#include "./timer/timer.h"
// #include "./mbox/mbox.h"
// #include "./framebf/framebf.h"
// #include "./timer/timer.h"
// #include "./timer/interrupt.h"


void main() {
    // set up serial console
    uart1_init();

    uart1_puts("\nProgram Begin\n");
    
    timer_1_init(100000);//count value
    enable_irq();
    // handle_timer_1();

    
    // handle_irq();
    // say hello
    // uart0_puts("\n\nTimer 1 received: .\n");
    // framebf_init();
    // timer_init();
    // handle_timer_1();
    while (1) {
        // uart1_puts("\nGot into While loop\n");
        // char c = uart1_getc();
        // uart1_sendc(c);
        handle_timer_1();
        handle_irq();
    }
}