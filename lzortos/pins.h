#ifndef D_PINS_H
#define D_PINS_H

#include <avr/io.h>

/* used by arch/avr/avr_spi.c */

#define SPI_MOSI_OFFSET	5
#define SPI_MOSI_DDR	DDRB
#define SPI_MOSI_PORT	PORTB

#define SPI_SCK_OFFSET	7
#define SPI_SCK_DDR	DDRB
#define SPI_SCK_PORT	PORTB

#endif /* D_PINS_H */
