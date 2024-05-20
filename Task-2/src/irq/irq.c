#include "irq.h"
#include "../uart/uart1.h"
void enable_irq(){  //enable for timer 1
    // arm cpu
    uart1_puts("Enabling interrupt\n");
    ENABLE_IRQS_1 |= (1 << SYS_TIMER_MATCH_1_INT);
    ENABLE_BASIC_IRQS |= (1 << 0);
    while (!(FIQ_CONTROL & (1<<7))){
        asm volatile("nop");
    }
    
    uart1_puts("basic enable\n");
    FIQ_CONTROL = 0b1000000<<0;
    uart1_puts("FIQ source\n");

    ENABLE_IRQS_1 = (1 << SYS_TIMER_MATCH_1_INT);
    uart1_puts("enable 1\n");
}

void disable_irq() {
#ifdef RPI3
    DISABLE_IRQS_1 = (1 << SYS_TIMER_MATCH_1_INT);
#else
    DISABLE_IRQS_1 = (1<<SYS_TIMER_MATCH_1_INT);
#endif

}

void handle_irq(){
    uart1_puts("Handling interrupt\n");
    // check if timer 1 interrupt
    if (IRQ_PENDING_1 & (1 << SYS_TIMER_MATCH_1_INT)){
        // clear the interrupt
        IRQ_BASIC_PENDING &= ~(1 << SYS_TIMER_MATCH_1_INT);
        // do something
        uart1_puts("Timer 1 interrupt\n");
    } else {
        uart1_puts("failed interrupt\n");
    }

}