#ifndef TIMER_H
#define TIMER_H
#define TIMER_BASE (MMIO_BASE + 0x7E003000)
#define ClockHz 4000000
// registers
#define TIMER_STATUS   (*(volatile unsigned int *)(TIMER_BASE + 0x0))
#define TIMER_LOW       (*(volatile unsigned int *)(TIMER_BASE + 0x4))
#define TIMER_HIGH      (*(volatile unsigned int *)(TIMER_BASE + 0x8))
#define TIMER_COMPARE_0         (*(volatile unsigned int *)(TIMER_BASE + 0xc))
#define TIMER_COMPARE_1        (*(volatile unsigned int *)(TIMER_BASE + 0x10))
#define TIMER_COMPARE_2        (*(volatile unsigned int *)(TIMER_BASE + 0x14))
#define TIMER_COMPARE_3   (*(volatile unsigned int *)(TIMER_BASE + 0x18))


void timer_init();
void handle_timer_1();
#endif 