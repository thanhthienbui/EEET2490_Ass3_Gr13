#ifndef IRQ_H
#define IRQ_H
#include "../gpio.h"

// #define IRQ_BASE (MMIO_BASE + 0x7E00B000)
#define IRQ_BASE 0x3F00B000

// registers
#define IRQ_BASIC_PENDING (* (volatile unsigned int*)(IRQ_BASE+0x200))  // R
#define IRQ_PENDING_1 (* (volatile unsigned int*)(IRQ_BASE+0x204))  // R
#define IRQ_PENDING_2 (* (volatile unsigned int*)(IRQ_BASE+0x208))  // R
// FIQ control
#define FIQ_CONTROL (* (volatile unsigned int*)(IRQ_BASE+0x20C))  // R/W 6:0
// IRQ enable
#define ENABLE_IRQS_1 (* (volatile unsigned int*)(IRQ_BASE+0x210))  //enable interrupt 31:0
#define ENABLE_IRQS_2 (* (volatile unsigned int*)(IRQ_BASE+0x214))  //enable interrupt 63:32
#define ENABLE_BASIC_IRQS (* (volatile unsigned int*)(IRQ_BASE+0x218))
//  IRQ disable 
#define DISABLE_IRQS_1 (* (volatile unsigned int*)(IRQ_BASE+0x21C))
#define DISABLE_IRQS_2 (* (volatile unsigned int*)(IRQ_BASE+0x220))
#define DISABLE_BASIC_IRQS (* (volatile unsigned int*)(IRQ_BASE+0x224))

// FIQ source
// 0-63: GPU interrupts
// 72-127: Do not use 
#define FIQ_ARM_TIMER 64
#define FIQ_ARM_MAILBOX 65
#define FIQ_ARM_DOORBELL_0 66
#define FIQ_ARM_DOORBELL_1 67
#define FIQ_GPU_0_HALT 68
#define FIQ_GPU_1_HALT 69
#define FIQ_ILLEGAL_ACCESS_TYPE_1 70
#define FIQ_ILLEGAL_ACCESS_TYPE_0 71

// ARM peripherals interrupt
// System Timer Interrupts
#define SYS_TIMER_MATCH_1_INT 1
#define SYS_TIMER_MATCH_3_INT 3

#define USB_CONTROLLER_INT 9
#define AUX_INT 29
#define I2C_SPI_SLV_INT 43

#define PWA0_INT 45
#define PWA1_INT 46

#define SMI_INT 48

#define GPIO_INT_0 49
#define GPIO_INT_1 50
#define GPIO_INT_2 51
#define GPIO_INT_3 52

#define I2C_INT 53
#define SPI_INT 54
#define PCM_INT 55
#define UART_INT 57

void enable_irq();  //enable for timer 1
void disable_irq(); //disable for timer 1
void handle_irq();
uint64_t timer_get_tick();
void timer_sleep(uint32_t ms);
#endif // IRQ_H