#include "./uart/mini_uart1.h"
#include "./irq/irq.h"
#include "./Sys_timer/sys_timer.h"
#include "./mbox/mbox.h"

#define COUNT 4000  //count value for 1 seconds
void delay();
void main() {
    GPFSEL0 |= 1<<9;
    /* Test GPIO 
    for (int i = 0; i < 5; i++) {
        GPSET0 |= 1<<3; //led on
        delay();
        GPCLR0 |= (1<<3); //led off
        delay();        
    }
    */
    uart1_init();
    uart1_puts("\nProgram Begin\n");
//enable IRQ and Timer
    enable_irq();
    timer_1_init();

    uart1_puts("\ndelay 1s\n");
    timer_sleep(1000);

    uart1_puts("\ndelay 5s\n");
    timer_sleep(5000);
    handle_irq();

    uart1_puts("\ndelay 10s\n");
    timer_sleep(10000);

    uart1_puts("\nDone.\n");
    
    
    while (1) {
        uart1_sendc(uart1_getc());
    }
}

void delay(){
    //Have some delay
    unsigned int count = 1000000; 
    while (count--) { asm volatile("nop"); } //waiting 1000000 cycles
}

