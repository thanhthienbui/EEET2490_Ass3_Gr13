//----------------------------------irq.c----------------------------------//
#include "irq.h"
#include "../uart/uart1.h"
#include "gpio.h"
#include "sys_timer.h"

// Enable interrupt
void enable_irq(){  //enable for timer 1
    /* Enable the interrupt for timer 1, timer 3 and AUX */
    // ENABLE_IRQS_1 |= (1 << SYS_TIMER_MATCH_1_INT)|(1 << AUX_INT)|(1<<SYS_TIMER_MATCH_3_INT); //interrupt for timer 1
    
    /* interrupt for Mini UART */
    // ENABLE_IRQS_1 |= (1 << AUX_INT); 
    
    /* interrupt for TIMER 1 */
    ENABLE_IRQS_1 |= (1 << SYS_TIMER_MATCH_1_INT);
    
    /* interrupt for TIMER 3 */
    // ENABLE_IRQS_1 |= (1 << SYS_TIMER_MATCH_3_INT);

    
    /* Double check for value in the register
    uint32_t irq = ENABLE_IRQS_1;
    uart1_puts("\nENABLE_IRQ_1 reg: ");
    uart1_bi(irq);
    uart1_puts("\nCompleted\n");
    */
}
// Disable interrupt 
void disable_irq() {
    DISABLE_IRQS_1 |= (1 << SYS_TIMER_MATCH_1_INT)|(1<< AUX_INT)|(1<<SYS_TIMER_MATCH_3_INT);
    uint32_t irq = DISABLE_IRQS_1;
    // uart_puts("DISABLE_IRQ_1: ");
    // uart_bi(irq);
    // uart_puts("Completed\n");
}

// Check and IRQ pending register and handle each interrupt accordingly
void handle_irq(){
    uint32_t irq = IRQ_PENDING_1;    // read from pending interrupt register
    while(irq) {
        // handling mini uart interrupt (valid bit at receiver FIFO) 
        // if (irq & (1 << AUX_INT)){
        //     irq &= ~(1 << AUX_INT);
        //     while((AUX_MU_IIR & 4) == 4){
        //         uart_puts("UART receive: ");
        //         uart_sendc(uart_getc());
        //         uart_puts("\n");
        //     }
        // }
        // // handling timer 3 interrupt
        // if (irq & (1 << SYS_TIMER_MATCH_3_INT)){    // check for interrupt from timer 3
        //     irq &= ~(1 << SYS_TIMER_MATCH_3_INT);   // clear interrupt bit
        //     handle_timer_3();
        // }
        // handling timer 1 interrupt
        if (irq & (1 << SYS_TIMER_MATCH_1_INT)){    // check for interrupt from timer 1
            irq &= ~(1 << SYS_TIMER_MATCH_1_INT);   // clear interrupt bit
            handle_timer_1();
        }
    }
}