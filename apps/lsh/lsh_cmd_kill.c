#include "config.h"
#include "lsh_internal.h"

#include "sched.h"

extern struct task g_sched_task[];

void lsh_cmd_kill(void)
{
	int i = 0;
	char pidstr[3];

	if (i > CONFIG_SCHED_NTASKS)
		return;
#if 0
	if (g_sched_task[i])
		return;
#endif
	if (g_sched_task[i].fp == 0)
		return;

	pidstr[0] = '0' + i;
	pidstr[1] = '\0';

	lsh_puts("kill ");
	lsh_puts(pidstr);
	lsh_puts("\r\n");
}
