#include "debug.h"
#include "config.h"
#include "avr_usart.h"

unsigned short g_eth0_rxpktcnt;

int net_init(void)
{
	dbg("net: ready!\r\n");
	return 0;
}
