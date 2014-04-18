#include "config.h"
#include "lsh_internal.h"

void lsh_cmd_ps(void)
{
	int i;

	lsh_puts("PID TTY TIME CMD\r\n");
	for (i = 0; i < CONFIG_SCHED_NTASKS; i++)
		lsh_puts("0   pts/0 00:00:00 foo\r\n");
}
