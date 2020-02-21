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
	int mypipe[2], infile, outfile;

	status = 127;
	infile = j->stdinc;
	p = j->first_process;
	while (p)
	{
		dop = ft_whatis3(p);
		if (dop == -1)
			return (-1);
		if (p->next)
		{
			if (pipe (mypipe) < 0)
			{
				exit (1);
			}
			outfile = mypipe[1];
		}
		else
			outfile = j->stdoutc;
		//dprintf(2, "\n\ndad12|%d|, |%d|", infile, outfile);


		//dprintf(2, "\n\ndad22|%d|, |%d|", infile, outfile);

		/* Fork the child processes.  */
		pid = fork();
		if (pid == 0)
			launch_process(p, j->pgid, infile, outfile, j->stderrc, foreground, q, dop);
		else if (pid < 0)
			/* This is the child process.  */
		{
			exit(0);
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
		//	wait(&pid);
			//printf("%sstatus: %d%s\n", RED, pid, RESET);
//			if (WIFEXITED(status))
//			{
//				g_exit_code = WEXITSTATUS(status);
//				printf("%sExit status of the child was %d%s\n", YEL, g_exit_code, RESET);
//			}
		}
		if (infile != j->stdinc)
			close (infile);
		if (outfile != j->stdoutc)
			close (outfile);
		//close(fd);
		infile = mypipe[0];
		outfile = mypipe[1];
		//dprintf(2, "\n\ndad13|%d|, |%d|", infile, outfile);

		p = p->next;
	}
	dop = 0;
	//dop = waitpid(, &status, 0);
	format_job_info (j, "launched");
	if (!shell_is_interactive)
		wait_for_job (j);
	if (foreground)
		put_job_in_foreground (j, 0);
	else
		put_job_in_background (j, 0);
	return (0);
}
