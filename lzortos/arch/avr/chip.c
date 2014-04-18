#include "config.h"
#include "avr_timer.h"
#include "avr_usart.h"
#include "avr_spi.h"
#include "avr_i2c.h"
#include "avr_adc.h"

int chip_init(void)
{
	avr_timer1_init(CONFIG_TIMER1_TICK_MS);
	avr_usart_init();
#ifdef CONFIG_SPI
	avr_spi_init();
#endif
#ifdef CONFIG_I2C
	avr_i2c_init();
#endif
#ifdef CONFIG_ADC
	avr_adc_init();
#endif
	return 0;
}
