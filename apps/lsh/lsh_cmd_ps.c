#include "config.h"
#include "lsh_internal.h"

#include "sched.h"

extern struct task g_sched_task[];

void lsh_cmd_ps(void)
{
	int i;

	lsh_puts("PID TTY TIME CMD\r\n");
	for (i = 0; i < CONFIG_SCHED_NTASKS; i++) {
		if (g_sched_task[i].fp != 0)
			lsh_puts("0   pts/0 00:00:00 foo\r\n");
	}
}
