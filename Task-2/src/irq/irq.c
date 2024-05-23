#include "irq.h"
#include "../uart/mini_uart1.h"
// #include "../entry.h"

// /*
void enable_irq(){  //enable for timer 1
    // arm cpu
    uart1_puts("Enabling Mini_UART1 interrupt\n");
    ENABLE_IRQS_1 = (1 << AUX_INT); //interrupt for mini uart 1
    
    uint32_t irq = ENABLE_IRQS_1;
    uart1_puts("ENABLE_IRQ_1: ");
    uart1_hex(irq);
    uart1_puts("Completed\n");
}

void disable_irq() {
#ifdef RPI3
    DISABLE_IRQS_1 = (1 << SYS_TIMER_MATCH_1_INT);
    uint32_t irq = DISABLE_IRQS_1;
    uart1_puts("DISABLE_IRQ_1: ");
    uart1_hex(irq);
    uart1_puts("Completed\n");
#else
    DISABLE_IRQS_1 = (1<<SYS_TIMER_MATCH_1_INT);
#endif

}

void handle_irq(){
    uart1_puts("Handling interrupt\n");
    while (IRQ_PENDING_1 & (1 << SYS_TIMER_MATCH_1_INT)){
        uart1_puts("Timer 1 interrupt\n");
        IRQ_BASIC_PENDING &= ~(1 << SYS_TIMER_MATCH_1_INT);
    }


    // if (IRQ_PENDING_1 & (1 << SYS_TIMER_MATCH_1_INT)){
    //     // clear the interrupt
    //     IRQ_BASIC_PENDING &= ~(1 << SYS_TIMER_MATCH_1_INT);
    //     // do something
    //     uart1_puts("Timer 1 interrupt\n");
    // } else {
    //     uart1_puts("failed interrupt\n");
    // }

}
// */
/*
char entry_error_message[16][32] = {
    "SYNC_INVALID_EL1t",
    "IRQ_INVALID_EL1t",
    "FIQ_INVALID_EL1t",
    "ERROR_INVALID_EL1t",

    "SYNC_INVALID_EL1h",
    "IRQ_INVALID_EL1h",
    "FIQ_INVALID_EL1h",
    "ERROR_INVALID_EL1h",
    
    "SYNC_INVALID_EL0_64",
    "IRQ_INVALID_EL0_64",
    "FIQ_INVALID_EL0_64",
    "ERROR_INVALID_EL0_64",
    
    "SYNC_INVALID_EL0_32",
    "IRQ_INVALID_EL0_32",
    "FIQ_INVALID_EL0_32",
    "ERROR_INVALID_EL0_32"
};

void show_invalid_entry_message(uint32_t type, uint64_t esr, uint64_t address){
    uart1_puts("ERROR CAUGHT: ");
    uart1_puts(entry_error_message[type]);
    uart1_puts(" - " );
    uart1_dec(type);
    uart1_puts("\nESR: ");
    uart1_hex(esr);
    uart1_puts("\nAddress: ");
    uart1_hex(address);
    uart1_puts("\n");
}

void enable_interrupt_controller(){
    // need to define which pi 3 or 4 is use
    // currently define for pi 3 only
    ENABLE_IRQS_1 = (1<<SYS_TIMER_MATCH_1_INT);
}

void handle_irq(){
    uint32_t irq;
    irq = IRQ_PENDING_1;    //read from pending interrupt register

    while (irq) {
        if (irq & (1 << AUX_INT)){
            irq &= ~(1 << AUX_INT);
            while ((AUX_MU_IIR & (0b10 << 1)) == 4){
                uart1_puts("UART1 received\n");
                char c = uart1_getc();
                uart1_sendc(c);
                uart1_puts("\n");
            }
        }
    }
}
*/