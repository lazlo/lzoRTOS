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
}

void os_start(void)
{
	fs_init();
	dbg("fs: ready!\r\n");
	sched_init();
	dbg("sched: ready!\r\n");
}

int main(void)
{
	hw_init();
	dbg("hw: ready!\r\n");
	os_start();
	dbg("os: ready!\r\n");
}
