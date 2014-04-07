#include "config.h"
#include "debug.h"
#include "avr_usart.h"

#define uart_putc	avr_usart_putc
#define uart_getc	avr_usart_getc

static char line[LSH_GETLINE_NCHARS];

static void lsh_puts(char *s)
{
	while (*s)
		uart_putc(*s++);
}

static void lsh_prompt(void)
{
	lsh_puts("> ");
}

static void lsh_getline(char *input, const int limit)
{
	int c;
	int i = 0;

	while ((c = uart_getc()) != '\r' && i < limit-1) {
		line[i++] = c;
		uart_putc(c);
	}
	line[++i] = '\0';
}

void lsh(void)
{
	lsh_prompt();
	lsh_getline(line, LSH_GETLINE_NCHARS);
	lsh_puts("\r\n");

	lsh_puts("read: ");
	lsh_puts(line);
	lsh_puts("\r\n");
}
