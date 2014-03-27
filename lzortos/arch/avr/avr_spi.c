#include "pins.h"

#define SPI_MOSI_OUTPUT		(SPI_MOSI_DDR	|= (1 << SPI_MOSI_OFFSET))
#define SPI_SCK_OUTPUT		(SPI_SCK_DDR	|= (1 << SPI_SCK_OFFSET))

static void avr_spi_gpioinit(void)
{
	SPI_MOSI_OUTPUT;
	SPI_SCK_OUTPUT;
}

static void avr_spi_devinit(void)
{
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1 << SPE)|(1 << MSTR)|(1 << SPR0);
}
void avr_spi_init(void)
{
	avr_spi_gpioinit();
	avr_spi_devinit();
}

char avr_spi_trx(const char c)
{
	/* Start transmission */
	SPDR = c;
	/* Wait for transmission complete */
	while (!(SPSR & (1 << SPIF)))
		;
	return SPDR;
}
