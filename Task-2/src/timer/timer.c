#include "timer.h"
#include "common.h"

const u32 interval_1 = ClockHz
u32 cur_val_l=0;
void timer_ini(){
    cur_val_1 = TIMER_BASE-> TIMER_LOW;
    cur_val_1 += interval_1;
    TIMER_BASE->TIMER_COMPARE_0 = cur_val_1;
}

void handle_timer_1() {
    cur_val_1 += interval_1;
    TIMER_BASE->TIMER_COMPARE_0 = cur_val_1;
    TIMER_BASE->TIMER_STATUS |= SYS_TIMER_IRQ_1;
    printf("Timer 1 received.\n")
}