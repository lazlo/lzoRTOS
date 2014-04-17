#include "debug.h"
#include "pins.h"
#include "chip.h"
#include "avr_usart.h"
#include "netio.h"
#ifdef CONFIG_FS
#include "fs.h"
#endif
#ifdef CONFIG_SCHED
#include "sched.h"
#endif

#include "avr_irq.h"

void hw_init(void)
{
	chip_init();
	board_init();
	dbg("hw: ready!\r\n");
}

void os_start(void)
{
#ifdef CONFIG_FS
	fs_init();
#endif
#ifdef CONFIG_SCHED
	sched_init();
#endif
#ifdef CONFIG_SCHED

	/* Add tasks here. */

#endif
#ifdef CONFIG_SCHED
	sched_start();
#endif
	dbg("os: ready!\r\n");
}

int main(void)
{
	hw_init();
	os_start();

	avr_irq_enable();

	#include "lsh.h"

	while (1)
	{
#ifdef CONFIG_SCHED
		sched_dispatch_tasks();
#else
		lsh();
#endif
	}
}

void Task_ToggleLeds(void)
{
	static int i = 0;

	if (i < 100) {
		i++;
	} else {
		i = 0;
		if (LED1_PORT & (1 << LED1_OFFSET)) {
			LED1_PORT &= ~(1 << LED1_OFFSET);
			LED2_PORT &= ~(1 << LED2_OFFSET);
			LED3_PORT &= ~(1 << LED3_OFFSET);
		} else {
			LED1_PORT |= (1 << LED1_OFFSET);
			LED2_PORT |= (1 << LED2_OFFSET);
			LED3_PORT |= (1 << LED3_OFFSET);
		}
	}
}

ISR(TIMER1_COMPA_vect)
{
	Task_ToggleLeds();
#ifdef CONFIG_SCHED
	sched_update();
#endif
}
