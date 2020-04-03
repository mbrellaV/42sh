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

int		launch_job(t_job *j, int foreground)
{
	t_process	*p;
	pid_t		pid;
	char		*rt;
	int mypipe[2], infile;

	infile = j->stdinc;
	p = j->first_process;
	rt = NULL;
	while (p)
	{
		if (is_builtin(p->file_args[0]) == 0 && !(rt = hash_get(p->file_args[0], 0)))
        {
		    p->completed = 1;
            p = p->next;
		    continue ;
        }
		if (pipe(mypipe) <= -1 || (pid = fork()) <= -1)
			exit (1);
		else if (pid == 0)
		{
			if (p->next != NULL)
			{
				dup2(mypipe[1], 1);
				close(mypipe[1]);
			}
			if (p->file_opt)
				ft_fd_flag(p->file_opt, &infile);
			dup2(infile, 0);
			close(mypipe[0]);
			launch_process(p, j->pgid, foreground, rt);
		}
		else
		{
			/* This is the parent process.  */
			p->pid = pid;
			if (shell_is_interactive)
			{
				if (j->pgid <= 0)
					j->pgid = pid;
				setpgid (pid, j->pgid);
			}
		}
		close(mypipe[1]);
		infile = mypipe[0];
		p = p->next;
	}
	if (j->foreground == 0)
		format_job_info(j, "launched", 1);
	if (!shell_is_interactive)
		wait_for_job (j);
	if (foreground)
		put_job_in_foreground (j, 0);
	else
		put_job_in_background (j, 0);
	return (0);
}
