#include "irq.h"
#include "../uart/mini_uart1.h"
#include "../entry.h"
#include "../gpio.h"
#include "../Sys_timer/sys_timer.h"

// /*
void enable_irq(){  //enable for timer 1
    // arm cpu
    uart1_puts("Enabling SYS_TIMER_1 interrupt\n");
    ENABLE_IRQS_1 |= (1 << SYS_TIMER_MATCH_1_INT); //interrupt for timer 1
    // print out register value
    uint32_t irq = ENABLE_IRQS_1;
    uart1_puts("\nENABLE_IRQ_1 reg: ");
    uart1_bi(irq);
    uart1_puts("\nCompleted\n");
}

void disable_irq() {
    DISABLE_IRQS_1 |= (1 << SYS_TIMER_MATCH_1_INT);
    uint32_t irq = DISABLE_IRQS_1;
    uart1_puts("DISABLE_IRQ_1: ");
    uart1_bi(irq);
    uart1_puts("Completed\n");
}

uint64_t timer_get_tick(){
    uint32_t high = TIMER_COUNTER_HIGH;
    uint32_t low = TIMER_COUNTER_LOW;
// double check if value is updated
    if (high != TIMER_COUNTER_HIGH){
        high = TIMER_COUNTER_HIGH;
        low = TIMER_COUNTER_LOW;
    }
    return ((uint64_t)high << 32) | low;
}

void timer_sleep(uint32_t ms){  //ms
    uint64_t start = timer_get_tick();
    // uart1_dec(start);
    while(timer_get_tick() < start + (ms*1000)){
        asm volatile("nop");
    }
}

void handle_irq(){
    uint32_t irq = IRQ_PENDING_1;    //read from pending interrupt register
    uart1_bi((unsigned int)irq);
    while(irq){
        if (irq & (1 << SYS_TIMER_MATCH_1_INT)){
            irq &= ~(1<< SYS_TIMER_MATCH_1_INT);    //clear interrupt bit
            handle_timer_1();
            // uart1_puts("Timer 1 interrupt\n");
        }
    }
}