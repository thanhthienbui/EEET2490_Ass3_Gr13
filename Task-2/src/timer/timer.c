#include "timer.h"
#include "../uart/uart1.h"
#include "../gpio.h"
#include "interrupt.h"
const uint32_t interval_1 = ClockHz;
// uint32_t count_val;
void timer_1_init(uint32_t c_val) {
    uart1_puts("Clear status\n");
    // clear status
    TIMER_STATUS &= ~(0xF<<0);  //clear status of timer 
    uart1_puts("clear compare\n");
    // set compare value
    TIMER_COMPARE_1 = c_val;

    // concat counter high and low
    // uint64_t count_value = TIMER_COUNTER_HIGH;
    // count_value |= (count_value << 32) | TIMER_COUNTER_LOW;
    uint32_t count_val = TIMER_COUNTER_LOW;
    uart1_puts("\n\nCount value: ");
    uart1_hex(count_val);
}

void handle_timer_1() {
    uart1_puts("\n\nHandling timer 1\n");
    while (TIMER_STATUS & (1<<1)){
        uart1_puts("\n\nTimer 1 received: ");
        // uart0_hex(TIMER_STATUS);
        TIMER_STATUS &= ~(1<<1);
    }
    // check for timer flag
    // action within loop
    // reset flag
}