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

static void netio_init_db25(void)
{
	GPIO_DB25_D2_DDR |= (1 << GPIO_DB25_D2_OFFSET);
	GPIO_DB25_D3_DDR |= (1 << GPIO_DB25_D3_OFFSET);
	GPIO_DB25_D4_DDR |= (1 << GPIO_DB25_D4_OFFSET);
	GPIO_DB25_D5_DDR |= (1 << GPIO_DB25_D5_OFFSET);

	GPIO_DB25_D6_DDR |= (1 << GPIO_DB25_D6_OFFSET);
	GPIO_DB25_D7_DDR |= (1 << GPIO_DB25_D7_OFFSET);
	GPIO_DB25_D8_DDR |= (1 << GPIO_DB25_D8_OFFSET);
	GPIO_DB25_D9_DDR |= (1 << GPIO_DB25_D9_OFFSET);

	GPIO_DB25_D10_DDR |= (1 << GPIO_DB25_D10_OFFSET);
	GPIO_DB25_D11_DDR |= (1 << GPIO_DB25_D11_OFFSET);
	GPIO_DB25_D12_DDR |= (1 << GPIO_DB25_D12_OFFSET);
	GPIO_DB25_D13_DDR |= (1 << GPIO_DB25_D13_OFFSET);
}

static void netio_init_eth(unsigned char hwaddr[6],
				unsigned short framelen,
				unsigned char fd)
{
#ifdef CONFIG_SPI
	enc28j60_init(hwaddr, framelen, fd);
#endif
}

int board_init(void)
{
	unsigned char hwaddr[6];
	unsigned short framelen;
	unsigned char fd;

	hwaddr[0] = 0x00;
	hwaddr[1] = 0xAA;
	hwaddr[2] = 0xBB;
	hwaddr[3] = 0xCC;
	hwaddr[4] = 0xDD;
	hwaddr[5] = 0xEE;

	framelen = 1518;
	fd = 1;

	netioaddon_init_led();
	netioaddon_init_irda();
	netioaddon_init_mmcsd();
	netioaddon_init_rf();
	netio_init_db25();
	netio_init_eth(hwaddr, framelen, fd);
	return 0;
}
