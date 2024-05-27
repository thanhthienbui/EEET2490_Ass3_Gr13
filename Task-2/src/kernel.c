//----------------------------------kernel.c----------------------------------//
#include "./uart/mini_uart1.h"
#include "./irq/irq.h"
#include "./Sys_timer/sys_timer.h"
#include "./mbox/mbox.h"

void main() {
    uart1_init();
    uart1_puts("\nProgram Begin\n");

    //enable IRQ and Timer
    enable_irq();
    timer_init();

    while (1) {
        handle_irq();
    }
}
