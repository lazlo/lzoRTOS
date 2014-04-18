#include "debug.h"
#include "config.h"
#include "sched.h"

#define task_set(t, f, d, p, r)		\
	do {				\
		t.fp		= f;	\
		t.delay		= d;	\
		t.periode	= p;	\
		t.run		= r;	\
	} while (0);

#define task_init(t)	task_set(t, 0, 0, 0, 0)

#define CONFIG_SCHED_ETL
#ifdef CONFIG_SCHED_ETL
extern struct task g_sched_task[];
#else
static struct task g_sched_task[CONFIG_SCHED_NTASKS];
#endif

void sched_init(void)
{
	int i;
	for (i = 0; i  < CONFIG_SCHED_NTASKS; i++)
		task_init(g_sched_task[i]);
	dbg("sched: ready!\r\n");
}

/* Add a task. */
int sched_add_task(void (*fp)(void), const int delay, const int periode)
{
	int i;
	for (i = 0; i < CONFIG_SCHED_NTASKS && g_sched_task[i].fp != 0; i++)
		;

	if (i == CONFIG_SCHED_NTASKS-1)
		return -1;

	task_set(g_sched_task[i], fp, delay, periode, 0);

	return i;
}

/* Enable the scheduler. */
void sched_start(void)
{
}

/* Schedule tasks for execution.
 * Needs to be called periodically. */
void sched_update(void)
{
	int i;
	struct task *t;
	for (i = 0; i < CONFIG_SCHED_NTASKS; i++) {
		t = &g_sched_task[i];
		if (t->fp) {
			if (t->delay > 0) {
				t->delay -= 1;
			} else {
				t->run += 1;
				if (t->periode)
					t->delay = t->periode;
				else
					t->fp = 0;
			}
		}
	}
}

/* Execute scheduled tasks
 * Needs to be called periodically. */
void sched_dispatch_tasks(void)
{
	int i;
	struct task *t;
	for (i = 0; i < CONFIG_SCHED_NTASKS; i++) {
		t = &g_sched_task[i];
		if (t->fp && t->run) {
			(t->fp)();
			t->run = 0;
		}
	}
}
