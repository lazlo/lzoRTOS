#ifndef D_PINS_H
#define D_PINS_H

#include <avr/io.h>

/* used by ... */

#define GPIO_IRDA_OFFSET		0
#define GPIO_IRDA_DDR			DDRB
#define GPIO_IRDA_PORT			PORTB
#define GPIO_IRDA_PIN			PINB

/* used by ... */

#define GPIO_J11_OFFSET			1
#define GPIO_J11_DDR			PORTB
#define GPIO_J11_PORT			PORTB
#define GPIO_J11_PIN			PINB

/* used by drivers/net/enc28j60.c */

#define GPIO_ENC28J60_CS_OFFSET		4
#define GPIO_ENC28J60_CS_DDR		DDRB
#define GPIO_ENC28J60_CS_PORT		PORTB

#define GPIO_ENC28J60_INT_OFFSET	2
#define GPIO_ENC28J60_INT_DDR		DDRB
#define GPIO_ENC28J60_INT_PORT		PORTB

/* used by arch/avr/avr_spi.c */

#define GPIO_SPI_MOSI_OFFSET		5
#define GPIO_SPI_MOSI_DDR		DDRB
#define GPIO_SPI_MOSI_PORT		PORTB

#define GPIO_SPI_SCK_OFFSET		7
#define GPIO_SPI_SCK_DDR		DDRB
#define GPIO_SPI_SCK_PORT		PORTB

/* used by configs/netio/netio.c */

#define GPIO_LED1_OFFSET		2
#define GPIO_LED1_DDR			DDRD
#define GPIO_LED1_PORT			PORTD

#define GPIO_LED2_OFFSET		4
#define GPIO_LED2_DDR			DDRD
#define GPIO_LED2_PORT			PORTD

#define GPIO_LED3_OFFSET		6
#define GPIO_LED3_DDR			DDRD
#define GPIO_LED3_PORT			PORTD

/* used by ... */

#define GPIO_MMC_CARD_OFFSET		7
#define GPIO_MMC_CARD_DDR		DDRD
#define GPIO_MMC_CARD_PORT		PORTD

#define GPIO_MMC_DATA3_OFFSET		3
#define GPIO_MMC_DATA3_DDR		DDRB
#define GPIO_MMC_DATA3_PORT		PORTB

/* used by ... */

#define GPIO_I2C_SCL_OFFSET		0
#define GPIO_I2C_SCL_DDR		DDRC
#define GPIO_I2C_SCL_PORT		PORTC

#define GPIO_I2C_SDA_OFFSET		1
#define GPIO_I2C_SDA_DDR		DDRC
#define GPIO_I2C_SDA_PORT		PORTC

/* used by configs/netio/netio.c */

#define GPIO_DB25_D2_OFFSET		0
#define GPIO_DB25_D2_DDR		DDRC
#define GPIO_DB25_D2_PORT		PORTC
#define GPIO_DB25_D2_PIN		PINC

#define GPIO_DB25_D3_OFFSET		1
#define GPIO_DB25_D3_DDR		DDRC
#define GPIO_DB25_D3_PORT		PORTC
#define GPIO_DB25_D3_PIN		PINC

#define GPIO_DB25_D4_OFFSET		2
#define GPIO_DB25_D4_DDR		DDRC
#define GPIO_DB25_D4_PORT		PORTC
#define GPIO_DB25_D4_PIN		PINC

#define GPIO_DB25_D5_OFFSET		3
#define GPIO_DB25_D5_DDR		DDRC
#define GPIO_DB25_D5_PORT		PORTC
#define GPIO_DB25_D5_PIN		PINC

#define GPIO_DB25_D6_OFFSET		4
#define GPIO_DB25_D6_DDR		DDRC
#define GPIO_DB25_D6_PORT		PORTC
#define GPIO_DB25_D6_PIN		PINC

#define GPIO_DB25_D7_OFFSET		5
#define GPIO_DB25_D7_DDR		DDRC
#define GPIO_DB25_D7_PORT		PORTC
#define GPIO_DB25_D7_PIN		PINC

#define GPIO_DB25_D8_OFFSET		6
#define GPIO_DB25_D8_DDR		DDRC
#define GPIO_DB25_D8_PORT		PORTC
#define GPIO_DB25_D8_PIN		PINC

#define GPIO_DB25_D9_OFFSET		7
#define GPIO_DB25_D9_DDR		DDRC
#define GPIO_DB25_D9_PORT		PORTC
#define GPIO_DB25_D9_PIN		PINC

#define GPIO_DB25_D10_OFFSET		0
#define GPIO_DB25_D10_DDR		DDRA
#define GPIO_DB25_D10_PORT		PORTA
#define GPIO_DB25_D10_PIN		PINA

#define GPIO_DB25_D11_OFFSET		1
#define GPIO_DB25_D11_DDR		DDRA
#define GPIO_DB25_D11_PORT		PORTA
#define GPIO_DB25_D11_PIN		PINA

#define GPIO_DB25_D12_OFFSET		2
#define GPIO_DB25_D12_DDR		DDRA
#define GPIO_DB25_D12_PORT		PORTA
#define GPIO_DB25_D12_PIN		PINA

#define GPIO_DB25_D13_OFFSET		3
#define GPIO_DB25_D13_DDR		DDRA
#define GPIO_DB25_D13_PORT		PORTA
#define GPIO_DB25_D13_PIN		PINA

/* used by ... */

#define GPIO_ADC1_OFFSET		4
#define GPIO_ADC1_DDR			DDRA
#define GPIO_ADC1_PORT			PORTA

#define GPIO_ADC2_OFFSET		5
#define GPIO_ADC2_DDR			DDRA
#define GPIO_ADC2_PORT			PORTA

#define GPIO_ADC3_OFFSET		6
#define GPIO_ADC3_DDR			DDRA
#define GPIO_ADC3_PORT			PORTA

#define GPIO_ADC4_OFFSET		7
#define GPIO_ADC4_DDR			DDRA
#define GPIO_ADC4_PORT			PORTA

/* used by ... */

#define GPIO_USART_RXD_OFFSET		0
#define GPIO_USART_RXD_DDR		DDRD
#define GPIO_USART_RXD_PORT		PORTD

#define GPIO_USART_TXD_OFFSET		1
#define GPIO_USART_TXD_DDR		DDRD
#define GPIO_USART_TXD_PORT		PORTD

#endif /* D_PINS_H */
