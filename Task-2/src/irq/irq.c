#include "irq.h"
#include "../uart/mini_uart1.h"
#include "../entry.h"
#include "../gpio.h"
#include "../Sys_timer/sys_timer.h"

// Enable Interrupt for timer 1
void enable_irq(){  //enable for timer 1
    // Enable the interrupt for timer 1, timer 3 and AUX
    ENABLE_IRQS_1 |= (1 << SYS_TIMER_MATCH_1_INT)|(1 << AUX_INT)|(1<<SYS_TIMER_MATCH_3_INT); //interrupt for timer 1
    
    // Double check for value in the register
    /*
    uint32_t irq = ENABLE_IRQS_1;
    uart1_puts("\nENABLE_IRQ_1 reg: ");
    uart1_bi(irq);
    uart1_puts("\nCompleted\n");
    */
}

void disable_irq() {
    DISABLE_IRQS_1 |= (1 << SYS_TIMER_MATCH_1_INT)|(1<< AUX_INT)|(1<<SYS_TIMER_MATCH_3_INT);
    uint32_t irq = DISABLE_IRQS_1;
    uart1_puts("DISABLE_IRQ_1: ");
    uart1_bi(irq);
    uart1_puts("Completed\n");
}

// Check and IRQ pending register and handle each interrupt accordingly
void handle_irq(){
    uint32_t irq = IRQ_PENDING_1;    // read from pending interrupt register
    while(irq){
        if (irq & (1 << AUX_INT)){
            irq &= ~(1 << AUX_INT);
            while((AUX_MU_IIR & 4) == 4){
                uart1_puts("UART receive: ");
                uart1_sendc(uart1_getc());
                uart1_puts("\n");
            }
        }
        // handling timer 1 interrupt
        if (irq & (1 << SYS_TIMER_MATCH_1_INT)){    // check for interrupt from timer 1
            irq &= ~(1 << SYS_TIMER_MATCH_1_INT);    //clear interrupt bit
            handle_timer_1();
        }
        // handling timer 3 interrupt
        if (irq & (1 << SYS_TIMER_MATCH_3_INT)){    // check for interrupt from timer 3
            irq &= ~(1 << SYS_TIMER_MATCH_3_INT);    //clear interrupt bit
            handle_timer_3();
        }
    }
}