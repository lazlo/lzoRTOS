#include "chip.h"
#include "avr_usart.h"
#include "board.h"
#include "enc28j60.h"
#include "fs.h"
#include "sched.h"

void _putc(const char c)
{
	avr_usart_putc(c);
}

void _puts(const char *s)
{
	while (*s)
		_putc(*s++);
}

void hw_init(void)
{
	chip_init();
	board_init();
	enc28j60_init();
}

void os_start(void)
{
	fs_init();
	sched_init();
	_puts("ready!\r\n");
}

int main(void)
{
	hw_init();
	os_start();
}
