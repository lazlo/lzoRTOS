#include "pins.h"

void avr_spi_init(void)
{
	/* Set MOSI and SCK output, all others input */
	SPI_MOSI_DDR |= (1 << SPI_MOSI_OFFSET);
	SPI_SCK_DDR |= (1 << SPI_SCK_OFFSET);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1 << SPE)|(1 << MSTR)|(1 << SPR0);
}

void avr_spi_send(const char c)
{
	/* Start transmission */
	SPDR = c;
	/* Wait for transmission complete */
	while (!(SPSR & (1 << SPIF)))
		;
}

char avr_spi_recv(void)
{
	return SPDR;
}
