#include <avr/io.h>

static void set_reload(const uint16_t reload)
{
	OCR1AH = reload >> 8;
	OCR1AL = reload;
}

static void set_mode_ctc(void)
{
	TCCR1B |= (1 << WGM12);
}

static void set_inten(void)
{
	TIMSK |= (1 << OCIE1A);
}

static void set_clock(void)
{
#if 0
	TCCR1B |= (1 << CS12);			/* fck/256 */
#else
	TCCR1B |= (1 << CS12)|(1 << CS10);	/* fck/1024 */
#endif
}

void avr_timer1_init(void)
{
	const int ms = 4;
	uint16_t reload;

	/* calculate reload value */
	reload = F_CPU / 1024 / 1000 * ms;
	/* write reload  value */
	set_reload(reload);
	/* set timer mode to ctc */
	set_mode_ctc();
	/* enable interrupt */
	set_inten();
	/* start timer by selecting a clock source */
	set_clock();
}
