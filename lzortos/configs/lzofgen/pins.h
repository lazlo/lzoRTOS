#ifndef D_PINS_H
#define D_PINS_H

#include <avr/io.h>

/* USART 0 */

#define GPIO_USART0_TX_OFFSET		1
#define GPIO_USART0_TX_DDR		DDRD
#define GPIO_USART0_TX_PORT		PORTD

#define GPIO_USART0_RX_OFFSET		0
#define GPIO_USART0_RX_DDR		DDRD
#define GPIO_USART0_RX_PORT		PORTD

/* Output Channels */

#define GPIO_OC2A_OFFSET		3
#define GPIO_OC2A_DDR			DDRB
#define GPIO_OC2A_PORT			PORTB

#define GPIO_OC0A_OFFSET		6
#define GPIO_OC0A_DDR			DDRD
#define GPIO_OC0A_PORT			PORTD

/* External Trigger */

/* USB */

/* LEDs */

#endif /* D_PINS_H */
