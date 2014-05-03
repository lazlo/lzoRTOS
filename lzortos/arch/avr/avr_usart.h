#ifndef D_ARCH_AVR_USART_H
#define D_ARCH_AVR_USART_H

void avr_usart_init(const unsigned int baud);

void avr_usart_putc(const char c);

char avr_usart_getc(void);

#endif /* D_ARCH_AVR_USART_H */
