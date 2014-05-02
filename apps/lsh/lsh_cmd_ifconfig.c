#include "config.h"
#include "lsh_internal.h"

void lsh_cmd_ifconfig(void)
{
	lsh_puts("eth0      ");
	lsh_puts("Link encap:Ethernet  HWaddr 00:00:00:00:00:00\r\n");
	lsh_puts("          ");
	lsh_puts("RX ");
	lsh_puts("packets:0 ");
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
}
