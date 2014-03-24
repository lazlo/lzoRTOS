#include "chip.h"
#include "avr_usart.h"
#include "board.h"
#include "enc28j60.h"

void _putc(const char c)
{
	avr_usart_putc(c);
}

void _puts(const char *s)
{
	while (*s)
		_putc(*s++);
}

int main(void)
{
	chip_init();
	board_init();
	enc28j60_init();
	_puts("ready!\r\n");
}
