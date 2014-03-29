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

/* used by drivers/net/enc28j60.c */

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

/* used by ... */

#define IRDA_OFFSET		0
#define IRDA_DDR		DDRB
#define IRDA_PORT		PORTB
#define IRDA_PIN		PINB

/* used by ... */

#define MMC_CARD_OFFSET		7
#define MMC_CARD_DDR		DDRD
#define MMC_CARD_PORT		PORTD

#define MMC_DATA3_OFFSET	3
#define MMC_DATA3_DDR		DDRB
#define MMC_DATA3_PORT		PORTB

/* used by ... */

#define USART_RXD_OFFSET	0
#define USART_RXD_DDR		DDRD
#define USART_RXD_PORT		PORTD

#define USART_TXD_OFFSET	1
#define USART_TXD_DDR		DDRD
#define USART_TXD_PORT		PORTD

/* used by ... */

#define I2C_SCL_OFFSET		0
#define I2C_SCL_DDR		DDRC
#define I2C_SCL_PORT		PORTC

#define I2C_SDA_OFFSET		1
#define I2C_SDA_DDR		DDRC
#define I2C_SDA_PORT		PORTC

/* used by ... */

#define DB25_D2_OFFSET		0
#define DB25_D2_DDR		DDRC
#define DB25_D2_PORT		PORTC
#define DB25_D2_PIN		PINC

#define DB25_D3_OFFSET		1
#define DB25_D3_DDR		DDRC
#define DB25_D3_PORT		PORTC
#define DB25_D3_PIN		PINC

#define DB25_D4_OFFSET		2
#define DB25_D4_DDR		DDRC
#define DB25_D4_PORT		PORTC
#define DB25_D4_PIN		PINC

#define DB25_D5_OFFSET		3
#define DB25_D5_DDR		DDRC
#define DB25_D5_PORT		PORTC
#define DB25_D5_PIN		PINC

#define DB25_D6_OFFSET		4
#define DB25_D6_DDR		DDRC
#define DB25_D6_PORT		PORTC
#define DB25_D6_PIN		PINC

#define DB25_D7_OFFSET		5
#define DB25_D7_DDR		DDRC
#define DB25_D7_PORT		PORTC
#define DB25_D7_PIN		PINC

#define DB25_D8_OFFSET		6
#define DB25_D8_DDR		DDRC
#define DB25_D8_PORT		PORTC
#define DB25_D8_PIN		PINC

#define DB25_D9_OFFSET		7
#define DB25_D9_DDR		DDRC
#define DB25_D9_PORT		PORTC
#define DB25_D9_PIN		PINC

#define DB25_D10_OFFSET		0
#define DB25_D10_DDR		DDRA
#define DB25_D10_PORT		PORTA
#define DB25_D10_PIN		PINA

#define DB25_D11_OFFSET		1
#define DB25_D11_DDR		DDRA
#define DB25_D11_PORT		PORTA
#define DB25_D11_PIN		PINA

#define DB25_D12_OFFSET		2
#define DB25_D12_DDR		DDRA
#define DB25_D12_PORT		PORTA
#define DB25_D12_PIN		PINA

#define DB25_D13_OFFSET		3
#define DB25_D13_DDR		DDRA
#define DB25_D13_PORT		PORTA
#define DB25_D13_PIN		PINA

#endif /* D_PINS_H */
