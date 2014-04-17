#include "debug.h"

void sched_init(void)
{
	dbg("sched: ready!\r\n");
}

/* Enable the scheduler. */
void sched_start(void)
{
}

/* Schedule tasks for execution.
 * Needs to be called periodically. */
void sched_update(void)
{
}

/* Execute scheduled tasks
 * Needs to be called periodically. */
void sched_dispatch_tasks(void)
{
}
