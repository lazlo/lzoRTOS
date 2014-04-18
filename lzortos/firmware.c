#include "debug.h"
#include "config.h"
#include "pins.h"
#include "chip.h"
#include "avr_usart.h"

/* Board specific ************************************************************/

#include "netio.h"

/* OS Components *************************************************************/

#ifdef CONFIG_FS
#include "fs.h"
#endif
#ifdef CONFIG_NET
#include "net.h"
#endif
#ifdef CONFIG_SCHED
#include "sched.h"
#endif

#include "avr_irq.h"

/* Applications **************************************************************/

#include "lsh.h"

#ifdef CONFIG_SCHED
/* Task list used by the simple co-operative scheduler. */
struct task g_sched_task[CONFIG_SCHED_NTASKS];
#endif

void Task_ToggleLed3(void);

int hw_init(void)
{
	chip_init();
	board_init();
	dbg("hw: ready!\r\n");
	return 0;
}

int os_start(void)
{
#ifdef CONFIG_FS
	fs_init();
#endif
#ifdef CONFIG_NET
	net_init();
#endif
#ifdef CONFIG_SCHED
	sched_init();
#endif
#ifdef CONFIG_SCHED
	sched_add_task(lsh, 0, 100);
	sched_add_task(Task_ToggleLed3, 10, 100);
	/* Add tasks here. */

#endif
#ifdef CONFIG_SCHED
	sched_start();
#endif
	dbg("os: ready!\r\n");
	return 0;
}

void os_run(void)
{
	avr_irq_enable();

	while (1)
	{
		if (GPIO_LED1_PORT & (1 << GPIO_LED1_OFFSET)) {
			GPIO_LED1_PORT &= ~(1 << GPIO_LED1_OFFSET);
		} else {
			GPIO_LED1_PORT |= (1 << GPIO_LED1_OFFSET);
		}
#ifdef CONFIG_SCHED
		sched_dispatch_tasks();
#else
		lsh();
#endif
	}
}

int main(void)
{
	hw_init();
	os_start();
	os_run();
}

void Task_ToggleLed3(void)
{
	static int i = 0;

	if (i < 100) {
		i++;
	} else {
		i = 0;
		if (GPIO_LED3_PORT & (1 << GPIO_LED3_OFFSET)) {
			GPIO_LED3_PORT &= ~(1 << GPIO_LED3_OFFSET);
		} else {
			GPIO_LED3_PORT |= (1 << GPIO_LED3_OFFSET);
		}
	}
}

ISR(TIMER1_COMPA_vect)
{
	if (GPIO_LED2_PORT & (1 << GPIO_LED2_OFFSET)) {
		GPIO_LED2_PORT &= ~(1 << GPIO_LED2_OFFSET);
	} else {
		GPIO_LED2_PORT |= (1 << GPIO_LED2_OFFSET);
	}

#ifndef CONFIG_SCHED
	Task_ToggleLed3();
#endif
#ifdef CONFIG_SCHED
	sched_update();
#endif
}
