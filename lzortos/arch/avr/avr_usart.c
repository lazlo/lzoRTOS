#include <avr/io.h>

#ifdef __AVR_ATmega1284P__
#define usart0_set_ubrr(ubrr)			\
		do {				\
			UBRR0L = ubrr;		\
			UBRR0H = ubrr >> 8;	\
		} while (0);
#define usart0_enable()	(UCSR0B |= (1 << RXEN0)|(1 << TXEN0))
#define usart0_write(b)	(UDR0 = b)
#define usart0_read()	(UDR0)
#define usart0_dre()	(UCSR0A & (1 << UDRE0))
#define usart0_rxc()	(UCSR0A & (1 << RXC0))
#else
#define usart0_set_ubrr(ubrr)			\
		do {				\
			UBRRL = ubrr;		\
			UBRRH = ubrr >> 8;	\
		} while (0);
#define usart0_enable()	(UCSRB |= (1 << RXEN)|(1 << TXEN))
#define usart0_write(b)	(UDR = b)
#define usart0_read()	(UDR)
#define usart0_dre()	(UCSRA & (1 << UDRE))
#define usart0_rxc()	(UCSRA & (1 << RXC))
#endif

void avr_usart_init(const unsigned int baud)
{
	unsigned short ubrr;

#if 1
	if (baud == 38400)
		ubrr = 25; /* 38400 bps */
#else
	if (baud == 76800)
		ubrr = 12; /* 76800 bps */
#endif
	/* configure baud rate generator with prescaler */
	usart0_set_ubrr(ubrr);
	/* enable transmitter and receiver */
	usart0_enable();
}

void avr_usart_putc(const char c)
{
	while (!usart0_dre())
		;

	usart0_write(c);
}

char avr_usart_getc(void)
{
	while (!usart0_rxc())
		;

	return usart0_read();
}
