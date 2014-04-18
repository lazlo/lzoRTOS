#include "config.h"
#include "debug.h"
#include "avr_usart.h"

#include "lsh_cmd.h"

#define uart_putc	avr_usart_putc
#define uart_getc	avr_usart_getc

static char line[CONFIG_LSH_GETLINE_NCHARS];

/* IO functions **************************************************************/

void lsh_puts(char *s)
{
	while (*s)
		uart_putc(*s++);
}

static void lsh_prompt(void)
{
	lsh_puts("lsh> ");
}

static int lsh_getline(char *input, const int limit)
{
	int c;
	int i = 0;

	while ((c = uart_getc()) != '\r' && i < limit-1) {
		line[i++] = c;
		uart_putc(c);
	}
	line[++i] = '\0';
	return i;
}

/* String functions **********************************************************/

static int lsh_strncmp(char *s1, char *s2, const int limit)
{
	int i = 0;
	while (i < limit && s1[i] != '\0' && s2[i] != '\0') {
		if (s1[i] > s2[i])
			return 1;
		else if (s1[i] < s2[i])
			return 2;
		i++;
	}
	return 0;
}

/* Commands ******************************************************************/

static void lsh_cmd_help(void)
{
#if 0
	lsh_puts(" arp\r\n");
	lsh_puts(" cat\r\n");
	lsh_puts(" cd\r\n");
	lsh_puts(" cp\r\n");
	lsh_puts(" dd\r\n");
	lsh_puts(" du\r\n");
	lsh_puts(" df\r\n");
	lsh_puts(" echo\r\n");
	lsh_puts(" env\r\n");
	lsh_puts(" free\r\n");
	lsh_puts(" grep\r\n");
	lsh_puts(" halt\r\n");
	lsh_puts(" head\r\n");
#endif
	lsh_puts(" help\r\n");
#if 0
	lsh_puts(" hostname\r\n");
	lsh_puts(" hwclock\r\n");
	lsh_puts(" i2c\r\n");
	lsh_puts(" ifconfig\r\n");
	lsh_puts(" kill\r\n");
	lsh_puts(" less\r\n");
	lsh_puts(" ls\r\n");
	lsh_puts(" mount\r\n");
	lsh_puts(" mkdir\r\n");
	lsh_puts(" mv\r\n");
	lsh_puts(" netstat\r\n");
	lsh_puts(" ping\r\n");
#endif
#ifdef CONFIG_SCHED
	lsh_puts(" ps\r\n");
#endif
#if 0
	lsh_puts(" pwd\r\n");
	lsh_puts(" rm\r\n");
	lsh_puts(" rmdir\r\n");
	lsh_puts(" ss\r\n");
	lsh_puts(" strings\r\n");
	lsh_puts(" tail\r\n");
	lsh_puts(" touch\r\n");
	lsh_puts(" tty\r\n");
	lsh_puts(" uptime\r\n");
	lsh_puts(" umount\r\n");
	lsh_puts(" uname\r\n");
	lsh_puts(" wget\r\n");
	lsh_puts(" xd\r\n");
	lsh_puts(" mb\r\n");
	lsh_puts(" mh\r\n");
	lsh_puts(" mw\r\n");
#endif
}

/* Command line processing ***************************************************/

static void lsh_parse(char *input, const int limit)
{
#ifdef CONFIG_SCHED
	if (lsh_strncmp(input, "ps", limit) == 0)
		return lsh_cmd_ps();
#endif
	if (lsh_strncmp(input, "help", limit) == 0)
		return lsh_cmd_help();
	else
		lsh_puts("unknown command\r\n");
}

void lsh(void)
{
	int len;
	lsh_prompt();

	len = lsh_getline(line, CONFIG_LSH_GETLINE_NCHARS);
	lsh_puts("\r\n");

	if (len > 1) {
		lsh_puts("read: ");
		lsh_puts(line);
		lsh_puts("\r\n");

		lsh_parse(line, len);
	}
}
