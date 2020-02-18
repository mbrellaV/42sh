/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:09:59 by qmartina          #+#    #+#             */
/*   Updated: 2020/02/18 17:10:01 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

int		launch_job (t_job *j, int foreground, t_memory *q)
{
	t_process	*p;
	pid_t		pid;
	int			dop;
	int			status;
	int mypipe[2], outfile;

	outfile = 0;
	p = j->first_process;
	while(p)
	{
		dop = ft_whatis2(p, q);
		if (dop == 1)
		{
			p = p->next;
			continue ;
		}
		if (dop == -2)
		{
			p = p->next;
			continue ;
		}
		if (dop == -1)
			return (-1);
		/* Fork the child processes.  */
		if (pipe(mypipe) == -1 || (pid = fork()) == -1)
			exit(1);
		else if (pid < 0)
			exit(1);
		else if (pid == 0)
			/* This is the child process.  */
		{
			if (p->next != NULL)
			{
				dup2(mypipe[1], 1);
				close(mypipe[1]);
			}
			dup2(outfile, 0);
			close(mypipe[0]);
			launch_process (p, j->pgid, foreground, q);
		}
		else
		{
			/* This is the parent process.  */
			p->pid = pid;
			if (shell_is_interactive)
			{
				if (!j->pgid)
					j->pgid = pid;
				setpgid (pid, j->pgid);
			}
			waitpid(pid, &status, 0);
			printf("%sstatus: %d%s\n", RED, status, RESET);
			if (WIFEXITED(status))
			{
				g_exit_code = WEXITSTATUS(status);
				printf("%sExit status of the child was %d%s\n", YEL, g_exit_code, RESET);
			}
			close(mypipe[1]);
			outfile = mypipe[0];
			p = p->next;
		}
	}
	format_job_info (j, "launched");

	if (!shell_is_interactive)
		wait_for_job (j);
	else if (foreground)
		put_job_in_foreground (j, 0);
	else
		put_job_in_background (j, 0);
	return (0);
}
