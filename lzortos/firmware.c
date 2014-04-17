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

#if 0
#ifdef CONFIG_SCHED
/* Task list used by the simple co-operative scheduler. */
struct task g_sched_task[CONFIG_SCHED_NTASKS];
#endif
#endif

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
	sched_add_task(lsh, 0, 100);
	sched_add_task(Task_ToggleLeds, 10, 100);
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
		if (LED3_PORT & (1 << LED3_OFFSET)) {
			LED3_PORT &= ~(1 << LED3_OFFSET);
		} else {
			LED3_PORT |= (1 << LED3_OFFSET);
		}
	}
}

ISR(TIMER1_COMPA_vect)
{
#ifndef CONFIG_SCHED
	Task_ToggleLeds();
#endif
#ifdef CONFIG_SCHED
	sched_update();
#endif
}
