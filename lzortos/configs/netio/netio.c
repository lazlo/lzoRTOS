#include "config.h"
#include "pins.h"
#include "enc28j60.h"

static void netioaddon_init_led(void)
{
	GPIO_LED1_DDR |= (1 << GPIO_LED1_OFFSET);
	GPIO_LED2_DDR |= (1 << GPIO_LED2_OFFSET);
	GPIO_LED3_DDR |= (1 << GPIO_LED3_OFFSET);

	GPIO_LED1_PORT |= (1 << GPIO_LED1_OFFSET);
	GPIO_LED2_PORT |= (1 << GPIO_LED2_OFFSET);
	GPIO_LED3_PORT |= (1 << GPIO_LED3_OFFSET);
}

static void netioaddon_init_irda(void)
{
	GPIO_IRDA_DDR &= ~(1 << GPIO_IRDA_OFFSET);
}

static void netioaddon_init_mmcsd(void)
{
}

static void netioaddon_init_rf(void)
{
}

static void netio_init_eth(void)
{
#ifdef CONFIG_SPI
	enc28j60_init();
#endif
}

int board_init(void)
{
	netioaddon_init_led();
	netioaddon_init_irda();
	netioaddon_init_mmcsd();
	netioaddon_init_rf();
	netio_init_eth();
	return 0;
}
