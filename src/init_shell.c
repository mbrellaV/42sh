/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 21:13:19 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/20 14:49:45 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

void	init_shell(void)
{
	globals()->g_shell_terminal = STDIN_FILENO;
	globals()->g_shell_is_interactive = isatty(globals()->g_shell_terminal);
	if (globals()->g_shell_is_interactive)
	{
		while (tcgetpgrp(globals()->g_shell_terminal) != (globals()->g_shell_pgid = getpgrp()))
			kill(-globals()->g_shell_pgid, SIGTTIN);
		disable_shell_signals();
		globals()->g_shell_pgid = getpid();
		if (setpgid(globals()->g_shell_pgid, globals()->g_shell_pgid) < 0)
		{
			perror("Couldn't put the shell in its own process group");
			exit(1);
		}
		tcsetpgrp(0, globals()->g_shell_pgid);
	}
}
