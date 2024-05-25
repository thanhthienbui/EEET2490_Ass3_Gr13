#include "sys_timer.h"
#include "../uart/mini_uart1.h"
#include "../gpio.h"
#include "../irq/irq.h"

const uint32_t interval_1 = CLK_HZ;
uint32_t cur_val_1 = 0;

void timer_1_init() {
    // Timer status
    /*
    uart1_puts("Before Set status: ");
    uart1_bi(TIMER_CONTROL_STATUS);

    uart1_puts("\nAfter Set status: ");
    */
    TIMER_CONTROL_STATUS &= ~(0xF<<0);  //clear status of timer 
    
    cur_val_1 = TIMER_COUNTER_LOW;
    cur_val_1 += interval_1;
    TIMER_COMPARE_1 += cur_val_1;

    uart1_puts("\nTimer 1 compare reg: ");
    uart1_bi(TIMER_COMPARE_1);
}

void handle_timer_1() {
    uart1_puts("\n\nHandling timer 1\n");
    cur_val_1 += interval_1;
    TIMER_COMPARE_1 = cur_val_1;
    TIMER_CONTROL_STATUS |= (1 << SYS_TIMER_MATCH_1_INT);
    uart1_puts("\nHandle timer 1 completed\n");

    // uint32_t count_val = TIMER_COUNTER_LOW;
    // uart1_puts("\n\nCount value: ");
    // uart1_hex(count_val);

    // while (TIMER_CONTROL_STATUS & (1<<1)){
    //     uart1_puts("\n\nTimer 1 received: ");
    //     TIMER_CONTROL_STATUS &= ~(1<<1);
    // }
}