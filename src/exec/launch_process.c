/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:06:33 by qmartina          #+#    #+#             */
/*   Updated: 2020/06/03 20:13:48 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

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

static int	check_file_opt(t_process *p, t_job *j, t_jobl *jobl)
{
	int			dop1;

	dop1 = 0;
	if (p->file_opt)
		dop1 = ft_fd_flag(p->file_opt, jobl->infile,
				jobl->outfile, j->stderrc);
	else
		standart_redirect(jobl->infile, jobl->outfile, j->stderrc);
	return (dop1);
}

int			launch_process(t_process *p, t_job *j, t_jobl *jobl, int fg)
{
	pid_t		pid;
	int			dop1;

	dop1 = 0;
	if (globals()->g_shell_is_interactive)
	{
		if (jobl->infile != j->stdinc && jobl->mypipe[1] != 0 &&
		jobl->outfile == j->stdoutc)
			close(jobl->mypipe[1]);
		if (jobl->outfile != j->stdoutc && jobl->mypipe[0] != 0 &&
		jobl->infile == j->stdinc)
			close(jobl->mypipe[0]);
		pid = getpid();
		j->pgid == 0 ? j->pgid = pid : 0;
		setpgid(pid, j->pgid);
		fg ? tcsetpgrp(globals()->g_shell_terminal, j->pgid) : 0;
		recover_normal_shell_signals();
		standart_redirect(jobl->infile, jobl->outfile, j->stderrc);
		dop1 = check_file_opt(p, j, jobl);
	}
	(dop1 < 0) ? exit(1) : 0;
	dop1 = do_builtin(p->file_args, p->file_opt, 1, p->inhibitor_args);
	(dop1 == 1) ? exit(0) : 0;
	(dop1 == 0) ? execve(jobl->rt, p->file_args, globals()->g_env) : 0;
	exit(127);
}
