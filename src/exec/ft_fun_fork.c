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

/*int		ft_path_while(char **path, char **argum, pid_t pid)
{
	int			k;
	struct stat mystat;
	char		*tmp;

	k = -1;
	while (path[++k])
	{
		tmp = ft_strjoin(path[k], argum[0]);
		if (lstat(tmp, &mystat) != -1)
		{
			if (mystat.st_mode & S_IXUSR)
			{
				ft_fun_fork(ft_strdup(tmp), argum, pid);
				ft_free_str(path);
				free(tmp);
				return (1);
			}
			ft_putstr_fd("21sh: permission denied: ", 2);
			ft_putendl_fd(tmp, 2);
			free(tmp);
			return (1);
		}
		free(tmp);
	}
	return (0);
}

int		ft_fun_lstat(struct stat mystat, char **argum, pid_t pid)
{
	if (mystat.st_mode & S_IXUSR && !S_ISDIR(mystat.st_mode))
	{
		ft_fun_fork(ft_strdup(argum[0]), argum, pid);
		return (1);
	}
	ft_printf("21sh: permission denied: %s\n", argum[0]);
	return (1);
}

int		ft_path_fork(char **argum, pid_t pid)
{
	char		**path;
	char		*tmp;
	struct stat mystat;

	if (lstat(argum[0], &mystat) != -1)
		return (ft_fun_lstat(mystat, argum, pid));
	else
	{
		if (ft_findenv("PATH=", g_env) == -404)
			return (-1);
		path = ft_strsplit(&g_env[ft_findenv("PATH=", g_env)][5], ":");
		tmp = argum[0];
		argum[0] = ft_strjoin("/", tmp);
		free(tmp);
		if (ft_path_while(path, argum, pid) == 1)
			return (1);
		ft_free_str(path);
	}
	return (-1);
}*/

void	ft_norm_pipe(int p1, int *fd_in, int p0, t_exectoken **head)
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
}
