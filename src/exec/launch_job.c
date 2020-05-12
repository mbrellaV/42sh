/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:09:59 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/12 19:15:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

static void		do_fork(t_jobl *jobl, t_job *j, int foreground)
{
	jobl->pid = fork();
	if (jobl->pid == 0)
		launch_process(jobl->p, j, *jobl, foreground);
	else if (jobl->pid < 0)
		exit(0);
	else
	{
		jobl->p->pid = jobl->pid;
		if (globals()->g_shell_is_interactive)
		{
			if (j->pgid <= 0)
				j->pgid = jobl->pid;
			setpgid(jobl->pid, j->pgid);
		}
	}
	if (jobl->infile != j->stdinc)
		close(jobl->infile);
	if (jobl->outfile != j->stdoutc)
		close(jobl->outfile);
	jobl->infile = jobl->mypipe[0];
	jobl->p = jobl->p->next;
}

int				launch_job(t_job *j, int foreground)
{
	t_jobl		jobl;

	jobl.infile = j->stdinc;
	jobl.p = j->first_process;
	jobl.rt = NULL;
	while (jobl.p)
	{
		if (jobl.p->file_args[0] != NULL &&
			!(jobl.rt = hash_get(jobl.p->file_args[0], 0)))
			return (-2);
		if (jobl.p->next)
		{
			if (pipe(jobl.mypipe) < 0)
				exit(1);
			jobl.outfile = jobl.mypipe[1];
		}
		else
			jobl.outfile = j->stdoutc;
		do_fork(&jobl, j, foreground);
	}
	if (!globals()->g_shell_is_interactive)
		wait_for_job(j);
	(foreground) ? put_job_in_foreground(j, 0) :
		put_job_in_background(j, 0);
	return (0);
}
