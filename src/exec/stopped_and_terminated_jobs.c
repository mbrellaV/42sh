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
	t_process *ptmp;
	int job_count;

	job_count = 0;
	if (pid > 0)
	{
		/* Update the record for the process.  */
		for (j = f_job; j; j = j->next)
		{
			job_count++;
			for (p = j->first_process; p; p = p->next)
				if (p->pid == pid)
				{
					p->status = status;
					if (WIFSTOPPED (status))
					{
						p->stopped = 1;
						set_new_var("?", ft_itoa(WEXITSTATUS(status)), &g_all_var);
						//dprintf(2, "\ndapoluch1: |%D|\n", WSTOPSIG(status));
					}
					else
					{
						p->completed = 1;
						p->status = WEXITSTATUS(status);
						set_new_var("?", ft_itoa(p->status), &g_all_var);
						//dprintf(2, "\nstatus: |%d|\n", WEXITSTATUS(status));
						ptmp = j->first_process;
						while (ptmp != p)
						{
							ptmp->completed = 1;
							//kill(ptmp->pid, SIGCONT);
							ptmp = ptmp->next;
						}
						if (WIFSIGNALED (status))
							fprintf (stderr, "%d: Terminated by signal %d.\n",
									 (int) pid, WTERMSIG (p->status));
					}
					return 0;
				}
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

int		process_count()
{
	t_job		*job;
	t_process	*p;
	int			res;

	job = f_job;
	res = 0;
	while (job)
	{
		p = job->first_process;
		while (p)
		{
			res++;
			p = p->next;
		}
		job = job->next;
	}
	return (res);
}

void	update_status (void)
{
	int status;
	pid_t pid;
	int		counter;
	int pr_count;

	pr_count = process_count();
	status = 0;
	counter = 0;
	pid = 0;
	while (counter < pr_count)
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
		mark_process_status(pid, status);
		counter++;
	}
	/* Update the record for the process.  */
//	do
//		pid = waitpid (WAIT_ANY, &status, WUNTRACED);
//	while (!mark_process_status (pid, status));
}

/* Check for processes that have status information available,
   blocking until all processes in the given job have reported.  */

void	wait_for_job (t_job *j)
{
	int status = 0;
	//t_process *p;
	pid_t pid;

	while (1)
	{
		//dprintf(2, "waiting");
		if (job_is_stopped(j))
			break ;
		pid = waitpid (-j->pgid, &status, WUNTRACED);
		mark_process_status (pid, status);
	}


//	pid = 0;
//	//sleep(3);
//	p = j->first_process;
//	while (p)
//	{
//		//dprintf(2, "\n\n\nrodlan\n\n\n");
//		if (job_is_stopped(j))
//			break ;
//		if (p->stopped == 0 && p->completed == 0)
//		{
//			pid = getpid();
//			status = 0;
//			//dprintf(2, "\ncurrent pid: |%d|, |%d|, |%d|\n", pid, p->pid, f_job->first_process->pid);
//			pid = -1;
//			pid = waitpid(p->pid, &status, WUNTRACED);
//			//dprintf(2, "\npidsas: |%d|\n", pid);
//			mark_process_status (p->pid, status);
//			//dprintf(2, "\n\n\nsas123: |%d|, |%d|, |%d|\n\n\n", pid, status, p->pid);
//			//break ;
//		}
//		p = p->next;
//		if (p == NULL)
//			p = j->first_process;
//	}


}

/* Format information about job status for the user to look at.  */

void format_job_info (t_job *j, const char *status, int num)
{
	dprintf (2, "[%d] + %ld (%s): %s\n", num, (long)j->pgid, status, j->command);
}

/* Notify the user about stopped or terminated jobs.
   Delete terminated jobs from the active job list.  */

void    do_job_notification (void)
{
	t_job *j, *jlast, *jnext;
	int job_count;

	job_count = 0;
	/* Update status information for child processes.  */
	update_status ();

	jlast = NULL;
	for (j = f_job; j; j = jnext)
	{
		job_count++;
		jnext = j->next;
        //dprintf(2, "sas\n");

		/* If all processes have completed, tell the user the job has
		   completed and delete it from the list of active jobs.  */
		if (job_is_completed (j)) {
			format_job_info (j, "completed", job_count);
			if (jlast)
				jlast->next = jnext;
			else
				f_job = jnext;
			//free_job(j);
		}

			/* Notify the user about stopped jobs,
			   marking them so that we won’t do this more than once.  */
		else if (job_is_stopped (j) && !j->notified) {
			format_job_info (j, "suspended", job_count);
			j->notified = 1;
			jlast = j;
		}

			/* Don’t say anything about jobs that are still running.  */
		else
			jlast = j;
		//dprintf(2, "sas1\n");
	}
	//f_job = j;
}

int		do_job_del()
{
	t_job *j, *jlast, *jnext;
	int d;

	d = 0;
	update_status();
	jlast = NULL;
	j = f_job;
	while (j)
	{
		d++;
		jnext = j->next;
		if (job_is_completed (j))
		{
			if (j->foreground == 0)
			{
				//ft_putchar_fd(, 2);
				format_job_info(j, "completed", d);
			}
			//kill(j->pgid, SIGCONT);
			if (jlast)
				jlast->next = jnext;
			else
				f_job = jnext;
		}
		else
			jlast = j;

		j = j->next;
	}
	return (1);
	//dprintf(2, "\n");
}



/* Find the active job with the indicated pgid.  */


t_job		*get_job_by_number(int n)
{
	t_job *j;
	int i;

	j = f_job;
	if (n < 0)
		return (NULL);
	i = 1;
	while (j && i < n)
	{
		i++;
		j = j->next;
	}
	return (j);
}

t_job		*get_last_job()
{
	t_job *j;

	j = f_job;
	while (j && j->next && j->next->next)
	{
		j = j->next;
	}
	return (j);
}