/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fun_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 19:04:16 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/13 20:04:23 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_fun_fork(char *path, char **arg, pid_t pgid, int foreground)
{
	pid_t pid;

	pid = getpid();
	if (pgid == 0) pgid = pid;
	setpgid (pid, pgid);
	if (foreground)
		tcsetpgrp (shell_terminal, pgid);
	signal (SIGINT, SIG_DFL);
	signal (SIGQUIT, SIG_DFL);
	signal (SIGTSTP, SIG_DFL);
	signal (SIGTTIN, SIG_DFL);
	signal (SIGTTOU, SIG_DFL);
	signal (SIGCHLD, SIG_DFL);
	execve(path, arg, g_env);
}

int		ft_norm_pipe(int p1, int *fd_in, int p0, t_exectoken **head)
{
	if (p0 == -404 && head == NULL)
	{
		dup2(p1, 1);
		close(p1);
	}
	else if (p1 == -404 && head == NULL)
	{
		dup2(*fd_in, 0);
		close(p0);
	}
	else if (head)
	{
		wait(NULL);
		close(p1);
		*fd_in = p0;
		*head = (*head)->left;
	}
	return (1);
}
