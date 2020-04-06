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
	int mypipe[2], infile, outfile;

	infile = j->stdinc;
	p = j->first_process;
	//j->pgid = 0;
	//dprintf(2, "\n\ndad12|%p|", p->file_args);

	rt = NULL;
	while (p)
	{
		if (p->file_args[0] != NULL && !(rt = hash_get(p->file_args[0], 0)))
		{
			//ft_putstr_fd("", 2)
			return (-2);
		}
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
			launch_process(p, j->pgid, infile, outfile, j->stderrc, foreground, rt);
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
				if (j->pgid <= 0)
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
		//outfile = mypipe[1];
		//dprintf(2, "\n\ndad13|%d|, |%d|", infile, outfile);

		p = p->next;
	}
	//format_job_info (j, "launched", 0);
	if (!shell_is_interactive)
		wait_for_job (j);
	if (foreground)
		put_job_in_foreground (j, 0);
	else
		put_job_in_background (j, 0);
	return (0);
}
