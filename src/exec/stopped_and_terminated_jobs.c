/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stopped_and_terminated_jobs.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:15:58 by qmartina          #+#    #+#             */
/*   Updated: 2020/02/18 17:15:59 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".././inc/fshell.h"
#include <errno.h>

/* Store the status of the process pid that was returned by waitpid.
   Return 0 if all went well, nonzero otherwise.  */

int mark_process_status (pid_t pid, int status)
{
	t_job *j;
	t_process *p;

	if (pid > 0)
	{
		/* Update the record for the process.  */
		for (j = f_job; j; j = j->next)
			for (p = j->first_process; p; p = p->next)
				if (p->pid == pid)
				{
					p->status = status;
					if (WIFSTOPPED (status))
						p->stopped = 1;
					else
					{
						p->completed = 1;
						if (WIFSIGNALED (status))
							fprintf (stderr, "%d: Terminated by signal %d.\n",
									 (int) pid, WTERMSIG (p->status));
					}
					return 0;
				}
		fprintf (stderr, "No child process %d.\n", pid);
		return -1;
	}
	else if (pid == 0 || errno == ECHILD)
		/* No processes ready to report.  */
		return -1;
	else {
		/* Other weird errors.  */
		perror ("waitpid");
		return -1;
	}
}

/* Check for processes that have status information available,
   without blocking.  */

void	update_status (void)
{
	int status;
	pid_t pid;

	do
		pid = waitpid (WAIT_ANY, &status, WUNTRACED|WNOHANG);
	while (!mark_process_status (pid, status));
}

/* Check for processes that have status information available,
   blocking until all processes in the given job have reported.  */

void	wait_for_job (t_job *j)
{
	int status = 0;
	pid_t pid;
	pid = -1;

	do
	{
		dprintf(2, "\nsas123: |%d|\n", status);

		pid = waitpid(j->pgid, &status, 0);

		int err = errno;
		if (err == ECHILD)
			dprintf(2, "\nerr1\n");
		if (err == EFAULT)
			dprintf(2, "\nerr2\n");
		if (err == EINVAL)
			dprintf(2, "\nerr3\n");
		if (err == EINTR)
			dprintf(2, "\nerr4\n");
		dprintf(2, "\nsas1234: |%d|, |%d|\n", status, pid);

	}
	while (!mark_process_status (pid, status)
		   && !job_is_stopped (j)
		   && !job_is_completed (j));

//	while (1)
//	{
//		dprintf(2, "\nsas123: |%d|\n", status);
//		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
//		dprintf(2, "\nsas1234: |%d|, |%d|\n", status, pid);
//		fprintf(stderr, "\nda|%d|\n", WIFEXITED(status));
//		if (mark_process_status(pid, status) < 1 && job_is_stopped(j) < 1 && job_is_completed(j) < 1)
//			break ;
//	}
}

/* Format information about job status for the user to look at.  */

void format_job_info (t_job *j, const char *status)
{
	fprintf (stderr, "||%ld (%s): %s\n", (long)j->pgid, status, j->command);
}

/* Notify the user about stopped or terminated jobs.
   Delete terminated jobs from the active job list.  */

void    do_job_notification (void)
{
	t_job *j, *jlast, *jnext;
//	t_process *p;

	/* Update status information for child processes.  */
	update_status ();

	jlast = NULL;
	for (j = f_job; j; j = jnext)
	{
		jnext = j->next;
        dprintf(2, "sas\n");
		/* If all processes have completed, tell the user the job has
		   completed and delete it from the list of active jobs.  */
		if (job_is_completed (j)) {
			format_job_info (j, "completed");
			if (jlast)
				jlast->next = jnext;
			else
				f_job = jnext;
			//free_job(j);
		}

			/* Notify the user about stopped jobs,
			   marking them so that we won’t do this more than once.  */
		else if (job_is_stopped (j) && !j->notified) {
			format_job_info (j, "stopped");
			j->notified = 1;
			jlast = j;
		}

			/* Don’t say anything about jobs that are still running.  */
		else
			jlast = j;
		dprintf(2, "sas1\n");
	}
}

/* Find the active job with the indicated pgid.  */


t_job		*get_last_job()
{
	t_job *j;

	j = f_job;
	while (j->next)
	{
		j = j->next;
	}
	dprintf(2, "2roflan");
	if (j == NULL)
		dprintf(2, "2roflan");
	return (j);
}