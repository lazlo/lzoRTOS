#include "avr_usart.h"

#include <avr/io.h>

#define LED1_OFFSET	2
#define LED1_DDR	DDRD
#define LED1_PORT	PORTD

#define LED2_OFFSET	4
#define LED2_DDR	DDRD
#define LED2_PORT	PORTD

#define LED3_OFFSET	6
#define LED3_DDR	DDRD
#define LED3_PORT	PORTD

#define ENC28J60_CS_OFFSET	4
#define ENC28J60_CS_DDR		DDRB
#define ENC28J60_CS_PORT	PORTB

#define ENC28J60_INT_OFFSET	2
#define ENC28J60_INT_DDR	DDRB
#define ENC28J60_INT_PORT	PORTB

static void netioaddon_init_led(void)
{
	LED1_DDR |= (1 << LED1_OFFSET);
	LED2_DDR |= (1 << LED2_OFFSET);
	LED3_DDR |= (1 << LED3_OFFSET);

	LED1_PORT |= (1 << LED1_OFFSET);
	LED2_PORT |= (1 << LED2_OFFSET);
	LED3_PORT |= (1 << LED3_OFFSET);
}

static void netio_init_serial(void)
{
	avr_usart_init();
}

static void netio_init_eth(void)
{
	ENC28J60_INT_DDR |= (1 << ENC28J60_CS_OFFSET);
	ENC28J60_INT_DDR &= ~(1 << ENC28J60_INT_OFFSET);
}

void netio_init(void)
{
	netioaddon_init_led();
	netio_init_serial();
	netio_init_eth();
}
