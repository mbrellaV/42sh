/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 21:13:19 by qmartina          #+#    #+#             */
/*   Updated: 2020/02/12 21:13:21 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

void	init_shell(void)
{
	/* See if we are running interactively.  */
	shell_terminal = STDIN_FILENO;
	shell_is_interactive = isatty (shell_terminal);

	if (shell_is_interactive)
	{
		/* Loop until we are in the foreground.  */
		while (tcgetpgrp(shell_terminal) != (shell_pgid = getpgrp ()))
			kill(- shell_pgid, SIGTTIN);

		/* Ignore interactive and job-control signals.  */
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
		//signal(SIGCHLD, SIG_IGN);

		/* Put ourselves in our own process group.  */
		shell_pgid = getpid();
		if (setpgid(shell_pgid, shell_pgid) < 0)
		{
			perror("Couldn't put the shell in its own process group");
			exit(1);
		}
		/* Grab control of the terminal.  */
		tcsetpgrp(0, shell_pgid);

		/* Save default terminal attributes for shell.  */
//		tcgetattr(shell_terminal, &saved_attributes);
	}
}

//void	launch_process (process *p, pid_t pgid,
//				int infile, int outfile, int errfile,
//				int foreground)
//{
//	pid_t pid;
//
//	if (shell_is_interactive)
//	{
//		/* Put the process into the process group and give the process group
//		   the terminal, if appropriate.
//		   This has to be done both by the shell and in the individual
//		   child processes because of potential race conditions.  */
//		pid = getpid ();
//		if (pgid == 0) pgid = pid;
//		setpgid (pid, pgid);
//		if (foreground)
//			tcsetpgrp (shell_terminal, pgid);
//
//		/* Set the handling for job control signals back to the default.  */
//		signal (SIGINT, SIG_DFL);
//		signal (SIGQUIT, SIG_DFL);
//		signal (SIGTSTP, SIG_DFL);
//		signal (SIGTTIN, SIG_DFL);
//		signal (SIGTTOU, SIG_DFL);
//		signal (SIGCHLD, SIG_DFL);
//	}
//
//	/* Set the standard input/output channels of the new process.  */
//	if (infile != STDIN_FILENO)
//	{
//		dup2 (infile, STDIN_FILENO);
//		close (infile);
//	}
//	if (outfile != STDOUT_FILENO)
//	{
//		dup2 (outfile, STDOUT_FILENO);
//		close (outfile);
//	}
//	if (errfile != STDERR_FILENO)
//	{
//		dup2 (errfile, STDERR_FILENO);
//		close (errfile);
//	}
//
//	/* Exec the new process.  Make sure we exit.  */
//	execvp (p->argv[0], p->argv);
//	perror ("execvp");
//	exit (1);
//}