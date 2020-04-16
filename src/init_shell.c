/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 21:13:19 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/16 10:22:07 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

void	init_shell(void)
{
	/* See if we are running interactively.  */
	g_shell_terminal = STDIN_FILENO;
	g_shell_is_interactive = isatty (g_shell_terminal);

	if (g_shell_is_interactive)
	{
		/* Loop until we are in the foreground.  */
		while (tcgetpgrp(g_shell_terminal) != (g_shell_pgid = getpgrp ()))
			kill(- g_shell_pgid, SIGTTIN);

		/* Ignore interactive and job-control signals.  */
		disable_shell_signals();
		//signal(SIGCHLD, SIG_IGN);

		/* Put ourselves in our own process group.  */
		g_shell_pgid = getpid();
		if (setpgid(g_shell_pgid, g_shell_pgid) < 0)
		{
			perror("Couldn't put the shell in its own process group");
			exit(1);
		}
		/* Grab control of the terminal.  */
		tcsetpgrp(0, g_shell_pgid);

		/* Save default terminal attributes for shell.  */
//		tcgetattr(g_shell_terminal, &saved_attributes);
	}
}