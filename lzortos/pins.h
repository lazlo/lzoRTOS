#ifndef D_PINS_H
#define D_PINS_H

#include <avr/io.h>

/* used by arch/avr/avr_spi.c */

#define SPI_MOSI_OFFSET		5
#define SPI_MOSI_DDR		DDRB
#define SPI_MOSI_PORT		PORTB

#define SPI_SCK_OFFSET		7
#define SPI_SCK_DDR		DDRB
#define SPI_SCK_PORT		PORTB

/* used by configs/netio/netio.c */

#define ENC28J60_CS_OFFSET	4
#define ENC28J60_CS_DDR		DDRB
#define ENC28J60_CS_PORT	PORTB

#define ENC28J60_INT_OFFSET	2
#define ENC28J60_INT_DDR	DDRB
#define ENC28J60_INT_PORT	PORTB

/* used by configs/netio/netio.c */

#define LED1_OFFSET		2
#define LED1_DDR		DDRD
#define LED1_PORT		PORTD

#define LED2_OFFSET		4
#define LED2_DDR		DDRD
#define LED2_PORT		PORTD

#define LED3_OFFSET		6
#define LED3_DDR		DDRD
#define LED3_PORT		PORTD

#endif /* D_PINS_H */
