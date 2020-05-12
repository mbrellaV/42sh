/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:06:33 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/02 13:20:10 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void		standart_redirect(int infile, int outfile, int errfile)
{
	if (infile != STDIN_FILENO)
	{
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	if (outfile != STDOUT_FILENO)
	{
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	if (errfile != STDERR_FILENO)
	{
		dup2(errfile, STDERR_FILENO);
		close(errfile);
	}
}

int			launch_process(t_process *p, t_job *j, t_jobl jobl, int fg)
{
	pid_t		pid;
	int			dop1;

	dop1 = 0;
	if (globals()->g_shell_is_interactive)
	{
		pid = getpid();
		if (j->pgid == 0)
			j->pgid = pid;
		setpgid(pid, j->pgid);
		if (fg)
			tcsetpgrp(globals()->g_shell_terminal, j->pgid);
		recover_normal_shell_signals();
		standart_redirect(jobl.infile, jobl.outfile, j->stderrc);
		if (p->file_opt)
			dop1 = ft_fd_flag(p->file_opt, jobl.infile,
					jobl.outfile, j->stderrc);
		else
			standart_redirect(jobl.infile, jobl.outfile, j->stderrc);
	}
	(dop1 < 0) ? exit(1) : 0;
	dop1 = do_builtin(p->file_args, p->file_opt, 1);
	(dop1 == 1) ? exit(0) : 0;
	(dop1 == 0) ? execve(jobl.rt, p->file_args, globals()->g_env) : 0;
	exit(127);
}
