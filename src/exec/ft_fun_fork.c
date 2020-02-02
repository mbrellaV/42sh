/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fun_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 19:04:16 by qmartina          #+#    #+#             */
/*   Updated: 2019/10/30 19:04:17 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_fun_fork(char *path, char **arg, pid_t pid)
{
	signal(SIGINT, ft_fork_signal);
	if (pid == 0)
		execve(path, arg, g_env);
	else if (pid < 0)
	{
		free(path);
		ft_putendl_fd("Fork failed to create a new process.", 2);
		return ;
	}
	if (path)
		free(path);
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
