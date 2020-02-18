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
						   int foreground, t_memory *q)
{
	pid_t		pid;
	char		*rt;

	rt = NULL;
	do_zam_str_with_tilda(p->file_args);
	if (shell_is_interactive)
	{
		if (ft_whatis2(p, q) == 1)
			exit(0);
		if (!(rt = hash_get(p->file_args[0], 0)))
			exit(1);
		/* Put the process into the process group and give the process group
		   the terminal, if appropriate.
		   This has to be done both by the shell and in the individual
		   child processes because of potential race conditions.  */
		pid = getpid();
		if (pgid == 0) pgid = pid;
		setpgid (pid, pgid);
		if (foreground)
			tcsetpgrp (shell_terminal, pgid);

		/* Set the handling for job control signals back to the default.  */
		signal (SIGINT, SIG_DFL);
		signal (SIGQUIT, SIG_DFL);
		signal (SIGTSTP, SIG_DFL);
		signal (SIGTTIN, SIG_DFL);
		signal (SIGTTOU, SIG_DFL);
		signal (SIGCHLD, SIG_DFL);
	}
	/* Exec the new process.  Make sure we exit.  */
	execve(rt, p->file_args, g_env);
	perror ("execve");
	exit(1);
}
