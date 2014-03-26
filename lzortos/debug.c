#include "avr_usart.h"

static void _puts(const char *s)
{
	while (*s)
		avr_usart_putc(*s++);
}

void dbg(const char *s)
{
	_puts(s);
}
