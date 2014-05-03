#include "debug.h"
#include "config.h"
#include "avr_usart.h"

unsigned short g_eth0_rxpktcnt;
char g_eth0_hwaddr[6];

int net_init(void)
{
	dbg("net: ready!\r\n");
	return 0;
}
