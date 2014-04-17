#include "debug.h"
#include "config.h"
#include "sched.h"

extern struct task g_sched_task[];

void sched_init(void)
{
	dbg("sched: ready!\r\n");
}

/* Add a task. */
int sched_task_add(void (*fp)(void), const int delay, const int periode)
{
	return -1;
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
