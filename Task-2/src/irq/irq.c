#include "irq.h"
#include "../uart/mini_uart1.h"
#include "../entry.h"
#include "../gpio.h"
#include "../Sys_timer/sys_timer.h"

// /*
void enable_irq(){  //enable for timer 1
    // arm cpu
    uart1_puts("Enabling SYS_TIMER_1 interrupt\n");
    // ENABLE_IRQS_1 |= (1 << SYS_TIMER_MATCH_1_INT)|(1 << SYS_TIMER_MATCH_3_INT); //interrupt for mini uart 1 and timer 1
    ENABLE_IRQS_1 = 0b1010; //enable timer 1 and 3
    uart1_puts("Address of register: ");
    uart1_hex((unsigned int)ENABLE_IRQS_1);
    get_add();


    // ENABLE_BASIC_IRQS = ENABLE_BASIC_IRQS|(1 << 1);

    // print out register value
    
    uint32_t irq = ENABLE_IRQS_1;
    uart1_puts("\nENABLE_IRQ_1 reg: ");
    uart1_bi(irq);
    uart1_puts("\nCompleted\n");
}

// void disable_irq() {
// #ifdef RPI3
//     DISABLE_IRQS_1 = (1 << SYS_TIMER_MATCH_1_INT);
//     uint32_t irq = DISABLE_IRQS_1;
//     uart1_puts("DISABLE_IRQ_1: ");
//     uart1_bi(irq);
//     uart1_puts("Completed\n");
// #endif 

// #ifdef RPI4
//     DISABLE_IRQS_1 = (1<<SYS_TIMER_MATCH_1_INT);
// #endif

// }

uint64_t timer_get_tick(){
    uint32_t high = TIMER_COUNTER_HIGH;
    uint32_t low = TIMER_COUNTER_LOW;

    if (high != TIMER_COUNTER_HIGH){
        high = TIMER_COUNTER_HIGH;
        low = TIMER_COUNTER_LOW;
    }
    return ((uint64_t)high << 32) | low;
}

void timer_sleep(uint32_t ms){
    uint64_t start = timer_get_tick();
    // uart1_dec(start);
    while(timer_get_tick() < start + (ms*1000)){
        // uart1_puts("Sleeping\n");
    }
    // uart1_puts("Wake up\n");
}

// void handle_irq(){
// /*
//     uart1_puts("Handling interrupt\n");
//     while (IRQ_PENDING_1 & (1 << SYS_TIMER_MATCH_1_INT)){
//         uart1_puts("Timer 1 interrupt\n");
//         // hand
//         IRQ_BASIC_PENDING &= ~(1 << SYS_TIMER_MATCH_1_INT);
//     }
// */
//     uint32_t irq;
//     irq = IRQ_PENDING_1;    //read from pending interrupt register
//     while(irq){
//         if (irq & (1 << SYS_TIMER_MATCH_1_INT)){
//             irq &= ~(1<< SYS_TIMER_MATCH_1_INT);
//             handle_timer_1();
//         }
//         if (irq & (1<< SYS_TIMER_MATCH_3_INT)){
//             irq &= ~(1<< SYS_TIMER_MATCH_3_INT);
//             // handle_timer_3();
//             uart1_puts("Timer 3 interrupt\n");
//         }
//     }
// }



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