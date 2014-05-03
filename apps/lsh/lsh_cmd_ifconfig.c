#include "config.h"
#include "lsh_internal.h"

#include "strutils.h"

extern char g_eth0_hwaddr[6];
extern unsigned short g_eth0_rxpktcnt;

void lsh_cmd_ifconfig(void)
{
	unsigned char hwaddr[6];
	unsigned short rxpktcnt = 0;
	char str_hwaddr[6][3];
	char str_rxpktcnt[6];

	/* Get the information for the interface */

	hwaddr[0] = g_eth0_hwaddr[0];
	hwaddr[1] = g_eth0_hwaddr[1];
	hwaddr[2] = g_eth0_hwaddr[2];
	hwaddr[3] = g_eth0_hwaddr[3];
	hwaddr[4] = g_eth0_hwaddr[4];
	hwaddr[5] = g_eth0_hwaddr[5];
	rxpktcnt = g_eth0_rxpktcnt;

	/* Convert information for output */

	itoa(hwaddr[0], str_hwaddr[0], 16);
	itoa(hwaddr[1], str_hwaddr[1], 16);
	itoa(hwaddr[2], str_hwaddr[2], 16);
	itoa(hwaddr[3], str_hwaddr[3], 16);
	itoa(hwaddr[4], str_hwaddr[4], 16);
	itoa(hwaddr[5], str_hwaddr[5], 16);
	itoa(rxpktcnt, str_rxpktcnt, 10);

	/* Show the outout */

	lsh_puts("eth0      ");
	lsh_puts("Link encap:Ethernet  ");
	lsh_puts("HWaddr ");
	lsh_puts(str_hwaddr[0]);
	lsh_puts(":");
	lsh_puts(str_hwaddr[1]);
	lsh_puts(":");
	lsh_puts(str_hwaddr[2]);
	lsh_puts(":");
	lsh_puts(str_hwaddr[3]);
	lsh_puts(":");
	lsh_puts(str_hwaddr[4]);
	lsh_puts(":");
	lsh_puts(str_hwaddr[5]);
	lsh_puts("\r\n");
	lsh_puts("          ");
	lsh_puts("RX ");
	lsh_puts("packets:");
	lsh_puts(str_rxpktcnt);
	lsh_puts(" ");
	lsh_puts("errors:0 ");
	lsh_puts("dropped:0 ");
	lsh_puts("overruns:0 ");
	lsh_puts("frame:0\r\n");
	lsh_puts("          ");
	lsh_puts("TX ");
	lsh_puts("packets:0 ");
	lsh_puts("errors:0 ");
	lsh_puts("dropped:0 ");
	lsh_puts("overruns:0 ");
	lsh_puts("carrier:0\r\n");
	lsh_puts("          ");
	lsh_puts("collision:0 txqueuelen:0\r\n");
	lsh_puts("          ");
	lsh_puts("RX bytes:0   TX bytes:0\r\n");
	lsh_puts("\r\n");
}
