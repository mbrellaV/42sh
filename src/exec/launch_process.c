/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:06:33 by qmartina          #+#    #+#             */
/*   Updated: 2020/02/18 17:06:34 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

int		launch_process (t_process *p, pid_t pgid,
						   int infile, int outfile, int errfile,
						   int foreground, char *rt)
{
	pid_t		pid;
	int dop1;

	do_zam_str_with_tilda(p->file_args);
	if (shell_is_interactive)
	{
		//if (ft_whatis2(p, q) == 1)
		//	exit(0);
		if (p->file_opt)
		{
			ft_fd_flag(p->file_opt, &infile, &infile, &outfile);
		}
		/* Put the process into the process group and give the process group
		   the terminal, if appropriate.
		   This has to be done both by the shell and in the individual
		   child processes because of potential race conditions.
		   Поместите процесс в группу процессов и при необходимости дайте
		   группе процессов терминал. Это должно быть сделано как оболочкой,
		   так и в отдельных дочерних процессах из-за возможных состояний гонки.*/
		pid = getpid();
		if (pgid == 0)
			pgid = pid;
		setpgid (pid, pgid);
		if (foreground)
			tcsetpgrp (shell_terminal, pgid);

		/* Set the handling for job control signals back to the default.  */
		signal (SIGINT, SIG_DFL);
		signal (SIGQUIT, SIG_DFL);
		signal (SIGTSTP, SIG_DFL);
		signal (SIGTTIN, SIG_DFL);
		signal (SIGTTOU, SIG_DFL);
		//signal (SIGCHLD, SIG_DFL);

		if (infile != STDIN_FILENO)
		{
			dup2 (infile, STDIN_FILENO);
			close (infile);
		}
		if (outfile != STDOUT_FILENO)
		{
			dup2 (outfile, STDOUT_FILENO);
			close (outfile);
		}
		if (errfile != STDERR_FILENO)
		{
			dup2 (errfile, STDERR_FILENO);
			close (errfile);
		}
	}
	/* Exec the new process.  Make sure we exit.  */
	dop1 = ft_whatis2(p);
	if (dop1 == 1)
		exit(0);
	if (dop1 == 0)
		execve(rt, p->file_args, g_env);
	exit(127);
}
