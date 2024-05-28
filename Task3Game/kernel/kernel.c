
#include "../uart/uart0.h"
#include "../uart/uart1.h"
#include "frame.h" 
#include "utils.h" 
#include "cmd.h"
#include "sys_timer.h"
void main() {
	// set up serial console 
	uart_init();
	timer_init();
	framebf_init(1024, 768);

	while (1) {
		execute();
	}
}



