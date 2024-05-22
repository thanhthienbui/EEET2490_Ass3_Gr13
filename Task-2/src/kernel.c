#include "./uart/uart1.h"
// #include "./uart/uart0.h"

#include "./irq/irq.h"
#include "./Sys_timer/sys_timer.h"
#include "./mbox/mbox.h"
// #include "./Arm_timer/arm_timer.h"

#define COUNT 4000  //count value for 1 seconds
// #include "./framebf/framebf.h"
// #include "./timer/timer.h"
// #include "./timer/interrupt.h"

void main() {
    
    // set_ARM_clk(ARM_CLK);   //set ARM clock = 4MHz
    // get_ARM_clk();
    // set up serial console
    uart1_init();
    uart1_puts("\nProgram Begin\n");
    timer_1_init(5*COUNT);

    // get_ARM_clk();
    // set_ARM_clk(ARM_CLK);   //set ARM clock = 4MHz




    // timer_1_init(100000);//count value
    // enable_irq();
    // handle_timer_1();

    
    // handle_irq();
    // say hello
    // uart0_puts("\n\nTimer 1 received: .\n");
    // framebf_init();
    // timer_init();
    // handle_timer_1();
    
    for (int i = 0; i < 10; i++) {
        handle_timer_1();
    }
    
    while (1) {
        // handle_timer_1();
        
        // uart1_puts("\nGot into While loop\n");
        // handle_timer_1();
        // handle_irq();
        // char c = uart1_getc();
        // uart1_sendc(c);
    }
}
