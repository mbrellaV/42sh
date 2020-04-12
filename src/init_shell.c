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
		disable_shell_signals();
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