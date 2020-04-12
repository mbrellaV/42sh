#include "fshell.h"

void			format_job_info(t_job *j, const char *status, int num)
{
	dprintf (2, "[%d] + %ld (%s): %s\n", num, (long)j->pgid, status, j->command);
}

void    do_job_notification(void)
{
	t_job *j, *jlast, *jnext;
	int job_count;

	job_count = 0;
	update_status ();
	jlast = NULL;
	for (j = f_job; j; j = jnext)
	{
		job_count++;
		jnext = j->next;
		if (job_is_completed (j))
		{
			format_job_info (j, "completed", job_count);
			if (jlast)
				jlast->next = jnext;
			else
				f_job = jnext;
		}
		else if (job_is_stopped (j) && !j->notified) {
			format_job_info (j, "suspended", job_count);
			j->notified = 1;
			jlast = j;
		}
		else
			jlast = j;
	}
}