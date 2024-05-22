#include "arm_timer.h"
#include "../uart/uart1.h"
// sys_clock = 250MHz
void arm_timer_init(uint32_t load_val){
    ARM_TIMER_CONTROL = (0b11111010<<16)|   //250
                        ARM_TIMER_CONTROL_FREE_RUNNING_ENABLE|
                        ARM_TIMER_CONTROL_TIMER_ENABLE|
                        ARM_TIMER_CONTROL_INTERRUPT_ENABLE|
                        ARM_TIMER_CONTROL_PRESCALE_1|
                        ARM_TIMER_CONTROL_32BIT_COUNTER;
    uart1_puts("\nComplete setting\n ");
}