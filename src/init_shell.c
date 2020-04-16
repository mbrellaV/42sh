/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 21:13:19 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/16 17:20:11 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

void	init_shell(void)
{
	g_shell_terminal = STDIN_FILENO;
	g_shell_is_interactive = isatty(g_shell_terminal);
	if (g_shell_is_interactive)
	{
		while (tcgetpgrp(g_shell_terminal) != (g_shell_pgid = getpgrp()))
			kill(-g_shell_pgid, SIGTTIN);
		disable_shell_signals();
		g_shell_pgid = getpid();
		if (setpgid(g_shell_pgid, g_shell_pgid) < 0)
		{
			perror("Couldn't put the shell in its own process group");
			exit(1);
		}
		tcsetpgrp(0, g_shell_pgid);
	}
}
