#include "timer.h"
#include "../gpio.h"
#include "interrupt.h"
const uint32_t interval_1 = ClockHz;
uint32_t cur_val_1 = 0; 
void timer_init() {
    cur_val_1 = TIMER_LOW;
    cur_val_1 += interval_1;
    TIMER_COMPARE_0 = cur_val_1;
}

void handle_timer_1() {
    cur_val_1 += interval_1;
    TIMER_COMPARE_0 = cur_val_1;
    TIMER_STATUS |= SYS_TIMER_IRQ_1;
    //printf("Timer 1 received.\n")
}