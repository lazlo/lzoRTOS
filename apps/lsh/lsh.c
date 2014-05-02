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
#ifdef CONFIG_NET
#ifdef CONFIG_CMD_ARP
	lsh_puts(" arp\r\n");
#endif
#endif
#ifdef CONFIG_FS
#ifdef CONFIG_CMD_CAT
	lsh_puts(" cat\r\n");
#endif
#ifdef CONFIG_CMD_CD
	lsh_puts(" cd\r\n");
#endif
#ifdef CONFIG_CMD_CP
	lsh_puts(" cp\r\n");
#endif
#ifdef CONFIG_CMD_DD
	lsh_puts(" dd\r\n");
#endif
#ifdef CONFIG_CMD_DU
	lsh_puts(" du\r\n");
#endif
#ifdef CONFIG_CMD_DF
	lsh_puts(" df\r\n");
#endif
#endif
#if 0
#ifdef CONFIG_CMD_ECHO
	lsh_puts(" echo\r\n");
#endif
#endif
#ifdef CONFIG_NET
#ifdef CONFIG_CMD_ETHTOOL
	lsh_puts(" ethtool\r\n");
#endif
#endif
#if 0
#ifdef CONFIG_CMD_ENV
	lsh_puts(" env\r\n");
#endif
#ifdef CONFIG_CMD_FREE
	lsh_puts(" free\r\n");
#endif
#ifdef CONFIG_CMD_GREP
	lsh_puts(" grep\r\n");
#endif
#ifdef CONFIG_CMD_HALT
	lsh_puts(" halt\r\n");
#endif
#ifdef CONFIG_CMD_HEAD
	lsh_puts(" head\r\n");
#endif
#endif
	lsh_puts(" help\r\n");
#ifdef CONFIG_NET
#ifdef CONFIG_CMD_HOSTNAME
	lsh_puts(" hostname\r\n");
#endif
#endif
#if 0
#ifdef CONFIG_CMD_HWCLOCK
	lsh_puts(" hwclock\r\n");
#endif
#endif
#ifdef CONFIG_I2C
#ifdef CONFIG_CMD_I2C
	lsh_puts(" i2c\r\n");
#endif
#endif
#ifdef CONFIG_NET
#ifdef CONFIG_CMD_IFCONFIG
	lsh_puts(" ifconfig\r\n");
#endif
#endif
#ifdef CONFIG_SCHED
#ifdef CONFIG_CMD_KILL
	lsh_puts(" kill\r\n");
#endif
#endif
#if 0
#ifdef CONFIG_CMD_LESS
	lsh_puts(" less\r\n");
#endif
#endif
#ifdef CONFIG_FS
#ifdef CONFIG_CMD_LS
	lsh_puts(" ls\r\n");
#endif
#endif
#ifdef CONFIG_NET
#ifdef CONFIG_CMD_MIITOOL
	lsh_puts(" mii-tool\r\n");
#endif
#endif
#ifdef CONFIG_FS
#ifdef CONFIG_CMD_MOUNT
	lsh_puts(" mount\r\n");
#endif
#ifdef CONFIG_CMD_MKDIR
	lsh_puts(" mkdir\r\n");
#endif
#ifdef CONFIG_CMD_MV
	lsh_puts(" mv\r\n");
#endif
#endif
#ifdef CONFIG_NET
#ifdef CONFIG_CMD_NETSTAT
	lsh_puts(" netstat\r\n");
#endif
#ifdef CONFIG_CMD_NETCAT
	lsh_puts(" netcat\r\n");
#endif
#ifdef CONFIG_CMD_PING
	lsh_puts(" ping\r\n");
#endif
#endif
#ifdef CONFIG_SCHED
#ifdef CONFIG_CMD_PS
	lsh_puts(" ps\r\n");
#endif
#endif
#ifdef CONFIG_FS
#ifdef CONFIG_CMD_PWD
	lsh_puts(" pwd\r\n");
#endif
#ifdef CONFIG_CMD_RM
	lsh_puts(" rm\r\n");
#endif
#ifdef CONFIG_CMD_RMDIR
	lsh_puts(" rmdir\r\n");
#endif
#endif
#ifdef CONFIG_NET
#ifdef CONFIG_CMD_ROUTE
	lsh_puts(" route\r\n");
#endif
#ifdef CONFIG_CMD_SS
	lsh_puts(" ss\r\n");
#endif
#endif
#ifdef CONFIG_SPI
#ifdef CONFIG_CMD_SPI
	lsh_puts(" spi\r\n");
#endif
#endif
#ifdef CONFIG_FS
#ifdef CONFIG_CMD_STRINGS
	lsh_puts(" strings\r\n");
#endif
#ifdef CONFIG_CMD_TAIL
	lsh_puts(" tail\r\n");
#endif
#endif
#ifdef CONFIG_NET
#ifdef CONFIG_CMD_TCPDUMP
	lsh_puts(" tcpdump\r\n");
#endif
#ifdef CONFIG_CMD_TELNET
	lsh_puts(" telnet\r\n");
#endif
#endif
#ifdef CONFIG_FS
#ifdef CONFIG_CMD_TOUCH
	lsh_puts(" touch\r\n");
#endif
#ifdef CONFIG_CMD_TTY
	lsh_puts(" tty\r\n");
#endif
#endif
#ifdef CONFIG_NET
#ifdef CONFIG_CMD_TRACEROUTE
	lsh_puts(" traceroute\r\n");
#endif
#endif
#if 0
#ifdef CONFIG_CMD_UPTIME
	lsh_puts(" uptime\r\n");
#endif
#endif
#ifdef CONFIG_FS
#ifdef CONFIG_CMD_UMOUNT
	lsh_puts(" umount\r\n");
#endif
#endif
#if 0
#ifdef CONFIG_CMD_UNAME
	lsh_puts(" uname\r\n");
#endif
#ifdef CONFIG_CMD_WGET
	lsh_puts(" wget\r\n");
#endif
#ifdef CONFIG_CMD_XD
	lsh_puts(" xd\r\n");
#endif
#ifdef CONFIG_CMD_MB
	lsh_puts(" mb\r\n");
#endif
#ifdef CONFIG_CMD_MH
	lsh_puts(" mh\r\n");
#endif
#ifdef CONFIG_CMD_MW
	lsh_puts(" mw\r\n");
#endif
#endif
}

/* Command line processing ***************************************************/

static void lsh_parse(char *input, const int limit)
{
#ifdef CONFIG_NET
#ifdef CONFIG_CMD_IFCONFIG
	if (lsh_strncmp(input, "ifconfig", limit) == 0)
		return lsh_cmd_ifconfig();
#endif
#endif
#ifdef CONFIG_SCHED
	if (lsh_strncmp(input, "kill", limit) == 0)
		return lsh_cmd_kill();
	if (lsh_strncmp(input, "ps", limit) == 0)
		return lsh_cmd_ps();
#endif
#ifdef CONFIG_SPI
	if (lsh_strncmp(input, "spi", limit) == 0)
		return lsh_cmd_spi();
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
