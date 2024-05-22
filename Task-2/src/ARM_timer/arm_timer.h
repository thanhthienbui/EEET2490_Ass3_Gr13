#ifndef ARM_TIMER_H
#define ARM_TIMER_H
#include "../gpio.h"
// sys_clock = 250MHz
#define ARM_TIMER_BASE (MMIO_BASE + 0x7E00B000)

#define ARM_TIMER_LOAD          (*(volatile unsigned int *)(ARM_TIMER_BASE + 0x400))
#define ARM_TIMER_VALUE         (*(volatile unsigned int *)(ARM_TIMER_BASE + 0x404))
#define ARM_TIMER_CONTROL       (*(volatile unsigned int *)(ARM_TIMER_BASE + 0x408))
#define ARM_TIMER_IRQ_CLR       (*(volatile unsigned int *)(ARM_TIMER_BASE + 0x40C))
#define ARM_TIMER_RAW_IRQ       (*(volatile unsigned int *)(ARM_TIMER_BASE + 0x410))
#define ARM_TIMER_MASKED_IRQ    (*(volatile unsigned int *)(ARM_TIMER_BASE + 0x414))
#define ARM_TIMER_RELOAD        (*(volatile unsigned int *)(ARM_TIMER_BASE + 0x418))
#define ARM_TIMER_PREDIVIDER    (*(volatile unsigned int *)(ARM_TIMER_BASE + 0x41C))
#define ARM_TIMER_FREE_RUNNING_COUNTER  (*(volatile unsigned int *)(ARM_TIMER_BASE + 0x420))

#define ARM_TIMER_CONTROL_FREE_RUNNING_ENABLE   (1<<9)
#define ARM_TIMER_CONTROL_DEBUG_HALT_ENABLE     (1<<8)
#define ARM_TIMER_CONTROL_TIMER_ENABLE          (1<<7)

#define ARM_TIMER_CONTROL_INTERRUPT_ENABLE    (1<<5)

#define ARM_TIMER_CONTROL_PRESCALE_1        (0b00<<2)
#define ARM_TIMER_CONTROL_PRESCALE_16       (0b01<<2)
#define ARM_TIMER_CONTROL_PRESCALE_256      (0b10<<2)
#define ARM_TIMER_CONTROL_PRESCALE_RESERVED (0b11<<2)

#define ARM_TIMER_CONTROL_32BIT_COUNTER (1<<1)
#define ARM_TIMER_CONTROL_16BIT_COUNTER (0<<1)

void arm_timer_init(uint32_t load_val);

#endif