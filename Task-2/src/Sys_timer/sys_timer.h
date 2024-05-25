#ifndef SYS_TIMER_H
#define SYS_TIMER_H
#include "../gpio.h"
#define CLK_HZ 1000000

#define TIMER_BASE 0x3F003000

// registers
#define TIMER_CONTROL_STATUS    (*(volatile unsigned int *)(TIMER_BASE + 0x0))  // R/W 3:0
#define TIMER_COUNTER_LOW       (*(volatile unsigned int *)(TIMER_BASE + 0x4))  // R
#define TIMER_COUNTER_HIGH      (*(volatile unsigned int *)(TIMER_BASE + 0x8))  // R 
#define TIMER_COMPARE_0         (*(volatile unsigned int *)(TIMER_BASE + 0xC))  // R/W
#define TIMER_COMPARE_1         (*(volatile unsigned int *)(TIMER_BASE + 0x10)) // R/W
#define TIMER_COMPARE_2         (*(volatile unsigned int *)(TIMER_BASE + 0x14)) // R/W
#define TIMER_COMPARE_3         (*(volatile unsigned int *)(TIMER_BASE + 0x18)) // R/W

// prototypes functions
void timer_1_init();
void handle_timer_1();

#endif 