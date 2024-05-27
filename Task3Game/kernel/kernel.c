
#include "../uart/uart0.h"
#include "../uart/uart1.h"
#include "frame.h" 
#include "utils.h" 
#include "cmd.h"
void main() {
	// set up serial console 
	uart_init();
	framebf_init(1024, 768);

	while (1) {
		execute();
	}
}

/*void main() {
	// set up serial console 
	uart_init();
	framebf_init(1024, 768);

	while (1) {
		drawMaze(0,40,30);
	}
}*/

