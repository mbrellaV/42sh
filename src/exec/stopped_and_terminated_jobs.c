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

int mark_process_status (pid_t pid, int status)
{
	t_job *j;
	t_process *p;
	t_process *ptmp;
	int job_count;
	char		*str_for_del;

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
						str_for_del = ft_itoa(WEXITSTATUS(status));
						set_new_var("?", str_for_del, &g_all_var);
						ft_strdel(&str_for_del);
						//dprintf(2, "\ndapoluch1: |%D|\n", WSTOPSIG(status));
					}
					else
					{
						p->completed = 1;
						p->status = WEXITSTATUS(status);
						str_for_del = ft_itoa(p->status);
						set_new_var("?", str_for_del, &g_all_var);
						ft_strdel(&str_for_del);
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
		return (-1);
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
	while (counter < pr_count)
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
		mark_process_status(pid, status);
		counter++;
	}
}

void	wait_for_job (t_job *j)
{
	int status = 0;
	pid_t pid;

	while (1)
	{
		if (job_is_stopped(j))
			break ;
		pid = waitpid (-j->pgid, &status, WUNTRACED);
		mark_process_status (pid, status);
	}
}

