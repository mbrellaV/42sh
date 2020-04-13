/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:06:33 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/13 20:04:23 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	standart_redirect(int infile, int outfile, int errfile)
{
	if (infile != STDIN_FILENO)
	{
		//dprintf(2, "\ninfile: |%d|\n", *p.infile);
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	if (outfile != STDOUT_FILENO)
	{
		//dprintf(2, "\noutfile: |%d|\n", *p.outfile);
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
		//dprintf(1, "\noutfilef: |%d|\n", outfile);

	}
	if (errfile != STDERR_FILENO)
	{
		//dprintf(2, "\nerrfile: |%d|\n", *p.errfile);
		dup2(errfile, STDERR_FILENO);
		close(errfile);
	}
}

int		launch_process(t_process *p, pid_t pgid,
						   int infile, int outfile, int errfile,
						   int foreground, char *rt)
{
	pid_t		pid;
	int			dop1;

	dop1 = 0;
	if (shell_is_interactive)
	{
		pid = getpid();
		if (pgid == 0)
			pgid = pid;
		setpgid (pid, pgid);
		if (foreground)
			tcsetpgrp (shell_terminal, pgid);
		recover_normal_shell_signals();
		standart_redirect(infile, outfile, errfile);
		if (p->file_opt)
			dop1 = ft_fd_flag(p->file_opt, &infile, &outfile, &errfile);
		else
			standart_redirect(infile, outfile, errfile);
	}
	if (dop1 < 0)
		exit(1);
	dop1 = ft_whatis2(p);
	if (dop1 == 1)
		exit(0);
	if (dop1 == 0)
		execve(rt, p->file_args, g_env);
	exit(127);
}
