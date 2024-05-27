#include "./uart/mini_uart1.h"
#include "./irq/irq.h"
#include "./Sys_timer/sys_timer.h"
#include "./mbox/mbox.h"

#define COUNT 4000  //count value for 1 seconds
void main() {
    GPFSEL0 |= 1<<9; // set GPIO 3 as output
    uart1_init();
    uart1_puts("\nProgram Begin\n");
//enable IRQ and Timer
    enable_irq();
    timer_init();

//Testing delay function (timer)
    // uart1_puts("\ndelay 5s\n");
    // timer_sleep(5000);  //ms

    // uart1_puts("\ndelay 10s\n");
    // timer_sleep(10000);

    // uart1_puts("\nDone.\n");
    // handle_irq();

    while (1) {
        handle_irq();
        // uart1_sendc(uart1_getc());
    }
}
