#include <avr/io.h>
#include "board.h"
#include "enc28j60.h"

void _putc(const char c)
{
	while (!(UCSRA & (1 << UDRE)))
		;
	UDR = c;
}

void _puts(const char *s)
{
	while (*s)
		_putc(*s++);
}

int main(void)
{
	board_init();
	enc28j60_init();
	_puts("ready!\r\n");
}
