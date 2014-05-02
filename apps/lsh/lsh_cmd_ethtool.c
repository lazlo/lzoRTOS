#include "config.h"
#include "lsh_internal.h"

#include "strutils.h"

extern unsigned short g_eth0_rxpktcnt;

void lsh_cmd_ethtool(void)
{
	char str_ifname[] = "eth0";

	lsh_puts("Settings for ");
	lsh_puts(str_ifname);
	lsh_puts(":\r\n");

	lsh_puts("        Supported ports: ");
	lsh_puts("\r\n");
	lsh_puts("        Supported link modes: ");
	lsh_puts("\r\n");
	lsh_puts("        Supported pause frame use: ");
	lsh_puts("\r\n");
	lsh_puts("        Supports auto-negotiation: ");
	lsh_puts("\r\n");
	lsh_puts("        Speed: ");
	lsh_puts("\r\n");
	lsh_puts("        Duplex: ");
	lsh_puts("\r\n");
	lsh_puts("        Port: ");
	lsh_puts("\r\n");
	lsh_puts("        PHYAD: ");
	lsh_puts("\r\n");
	lsh_puts("        Transceiver: ");
	lsh_puts("\r\n");
	lsh_puts("        Auto-negotiation: ");
	lsh_puts("\r\n");
	lsh_puts("        MDI-X: ");
	lsh_puts("\r\n");
	lsh_puts("        Link detected: ");
	lsh_puts("\r\n");
}
