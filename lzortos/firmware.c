#include "debug.h"
#include "chip.h"
#include "avr_usart.h"
#include "board.h"
#include "fs.h"
#include "sched.h"

void hw_init(void)
{
	chip_init();
	board_init();
	dbg("hw: ready!\r\n");
}

void os_start(void)
{
	fs_init();
	sched_init();
	dbg("os: ready!\r\n");
}

int main(void)
{
	hw_init();
	os_start();
}
