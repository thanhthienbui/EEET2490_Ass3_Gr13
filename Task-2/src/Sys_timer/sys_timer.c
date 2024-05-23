#include "sys_timer.h"
#include "../uart/mini_uart1.h"
#include "../gpio.h"
// const uint32_t interval_1 = ClockHz;
// uint32_t count_val;
void timer_1_init(uint32_t c_val) {
    uart1_puts("Before Set status: ");
    uart1_hex(TIMER_CONTROL_STATUS);
    uart1_puts("After Set status: ");
    TIMER_CONTROL_STATUS &= ~(0xF<<0);  //clear status of timer 
    
    uart1_puts("\nBefore setting compare value\n");
    uart1_hex(TIMER_COMPARE_1);
    uart1_puts("\nSet compare value\n");
    TIMER_COMPARE_1 = 0b111110100000<<0;

    uart1_puts("Timer 1 compare value: ");
    uart1_dec(TIMER_COMPARE_1);

    // concat counter high and low
    // uint64_t count_value = TIMER_COUNTER_HIGH;
    // count_value |= (count_value << 32) | TIMER_COUNTER_LOW;

    // uint32_t count_val = TIMER_COUNTER_LOW;
    // uart1_puts("\n\nCount value: ");
    // uart1_hex(count_val);
}

void handle_timer_1() {
    uart1_puts("\n\nHandling timer 1\n");
    uint32_t count_val = TIMER_COUNTER_LOW;
    uart1_puts("\n\nCount value: ");
    uart1_hex(count_val);

    while (TIMER_CONTROL_STATUS & (1<<1)){
        uart1_puts("\n\nTimer 1 received: ");
        TIMER_CONTROL_STATUS &= ~(1<<1);
    }
}