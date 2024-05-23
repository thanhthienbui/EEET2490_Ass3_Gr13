#include "./uart/mini_uart1.h"
#include "./irq/irq.h"
#include "./Sys_timer/sys_timer.h"
#include "./mbox/mbox.h"

#define COUNT 4000  //count value for 1 seconds

void main() {
    uart1_init();
    uart1_puts("\nProgram Begin\n");
    
    // irq_init_vectors();
    // enable_interrupt_controller();
    // irq_enable();
    enable_irq();
    handle

    
    while (1) {
        // handle_timer_1();
        
        // uart1_puts("\nGot into While loop\n");
        // handle_timer_1();
        // handle_irq();
        // char c = uart1_getc();
        // uart1_sendc(c);
    }
}
