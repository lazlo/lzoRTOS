#include <avr/io.h>

void avr_usart_init(void)
{
	/* configure baud rate generator with prescaler */
#if 1
	UBRRL = 25; /* 38400 bps */
#else
	UBRRL = 12; /* 76800 bps */
#endif
	UBRRH = 0;
	/* enable transmitter and receiver */
	UCSRB |= (1 << RXEN)|(1 << TXEN);
}

void avr_usart_putc(const char c)
{
	while (!(UCSRA & (1 << UDRE)))
		;
	UDR = c;
}

char avr_usart_getc(void)
{
	while (!(UCSRA & (1 << RXC)))
		;

	return UDR;
}
