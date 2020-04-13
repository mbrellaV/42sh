/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:09:59 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/13 20:04:23 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

int		launch_job(t_job *j, int foreground)
{
	t_process	*p;
	pid_t		pid;
	char		*rt;
	int mypipe[2], infile, outfile;

	infile = j->stdinc;
	p = j->first_process;
	rt = NULL;
	while (p)
	{
		if (p->file_args[0] != NULL && !(rt = hash_get(p->file_args[0], 0)))
			return (-2);
		if (p->next)
		{
			if (pipe(mypipe) < 0)
				exit (1);
			outfile = mypipe[1];
		}
		else
			outfile = j->stdoutc;
		pid = fork();
		if (pid == 0)
			launch_process(p, j->pgid, infile, outfile, j->stderrc, foreground, rt);
		else if (pid < 0)
			exit(0);
		else
		{
			p->pid = pid;
			if (shell_is_interactive)
			{
				if (j->pgid <= 0)
					j->pgid = pid;
				setpgid (pid, j->pgid);
			}
		}
		if (infile != j->stdinc)
			close (infile);
		if (outfile != j->stdoutc)
			close (outfile);
		infile = mypipe[0];
		p = p->next;
	}
	if (!shell_is_interactive)
		wait_for_job (j);
	if (foreground)
		put_job_in_foreground (j, 0);
	else
		put_job_in_background (j, 0);
	return (0);
}
