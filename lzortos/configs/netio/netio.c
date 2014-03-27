#include "pins.h"
#include "enc28j60.h"

static void netioaddon_init_led(void)
{
	LED1_DDR |= (1 << LED1_OFFSET);
	LED2_DDR |= (1 << LED2_OFFSET);
	LED3_DDR |= (1 << LED3_OFFSET);

	LED1_PORT |= (1 << LED1_OFFSET);
	LED2_PORT |= (1 << LED2_OFFSET);
	LED3_PORT |= (1 << LED3_OFFSET);
}

void netio_init(void)
{
	netioaddon_init_led();
	enc28j60_init();
}
