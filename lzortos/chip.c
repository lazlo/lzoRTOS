#include "avr_timer.h"
#include "avr_usart.h"
#include "avr_spi.h"
#include "avr_i2c.h"
#include "avr_adc.h"

void chip_init(void)
{
	avr_timer1_init();
	avr_usart_init();
	avr_spi_init();
	avr_i2c_init();
#ifdef CONFIG_ADC
	avr_adc_init();
#endif
}
