#include "config.h"
#include "lsh_internal.h"

#include "sched.h"

extern struct task g_sched_task[];

void lsh_cmd_ps(void)
{
	int i;
	char pidstr[3];

	lsh_puts("PID TTY TIME CMD\r\n");
	for (i = 0; i < CONFIG_SCHED_NTASKS; i++) {
		if (g_sched_task[i].fp != 0) {
			pidstr[0] = '0' + i;
			pidstr[1] = '\0';

			lsh_puts(pidstr);
			lsh_puts("   ");
			lsh_puts("pts/0 ");
			lsh_puts("00:00:00 ");
			lsh_puts("foo\r\n");
		}
	}
}
