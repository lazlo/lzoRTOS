#ifndef D_ARCH_AVR_SPI_H
#define D_ARCH_AVR_SPI_H

void avr_spi_init(void);

void avr_spi_send(const char c);

char avr_spi_recv(void);

#endif /* D_ARCH_AVR_SPI_H */
