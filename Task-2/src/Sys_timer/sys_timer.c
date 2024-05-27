#include "sys_timer.h"
#include "../uart/mini_uart1.h"
#include "../gpio.h"
#include "../irq/irq.h"

const uint32_t interval_1 = CLK_HZ;
uint32_t cur_val_1 = 0;

const uint32_t interval_3 = CLK_HZ/4;
uint32_t cur_val_3 = 0;

void timer_init() {
    //timer status
    TIMER_CONTROL_STATUS &= ~(0xF<<0);  //clear status of timer 
    
    cur_val_1 = TIMER_COUNTER_LOW; 
    cur_val_1 += interval_1;
    TIMER_COMPARE_1 += cur_val_1;

    cur_val_3 = TIMER_COUNTER_LOW; 
    cur_val_3 += interval_3;
    TIMER_COMPARE_3 += cur_val_3;
}

void handle_timer_1() {
    cur_val_1 += interval_1;
    TIMER_COMPARE_1 = cur_val_1;
    TIMER_CONTROL_STATUS |= (1 << SYS_TIMER_MATCH_1_INT);
    uart1_puts("Timer 1 Received.\n");
}
void handle_timer_3() {
    cur_val_3 += interval_3;
    TIMER_COMPARE_3 = cur_val_3;
    TIMER_CONTROL_STATUS |= (1 << SYS_TIMER_MATCH_3_INT);
    uart1_puts("Timer 3 Received.\n");
}