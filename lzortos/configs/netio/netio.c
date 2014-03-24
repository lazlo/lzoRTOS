#include "pins.h"

static void netioaddon_init_led(void)
{
	LED1_DDR |= (1 << LED1_OFFSET);
	LED2_DDR |= (1 << LED2_OFFSET);
	LED3_DDR |= (1 << LED3_OFFSET);

	LED1_PORT |= (1 << LED1_OFFSET);
	LED2_PORT |= (1 << LED2_OFFSET);
	LED3_PORT |= (1 << LED3_OFFSET);
}

static void netio_init_eth(void)
{
	ENC28J60_INT_DDR |= (1 << ENC28J60_CS_OFFSET);
	ENC28J60_INT_DDR &= ~(1 << ENC28J60_INT_OFFSET);
}

void netio_init(void)
{
	netioaddon_init_led();
	netio_init_eth();
}
