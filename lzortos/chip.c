#include "avr_usart.h"
#include "avr_spi.h"

void chip_init(void)
{
	avr_usart_init();
	avr_spi_init();
}
