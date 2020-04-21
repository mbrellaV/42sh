/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_q.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 14:47:54 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/20 14:49:45 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

void	ft_error_q(int er)
{
	if (er == 1)
	{
		ft_free_str(globals()->g_env);
		ft_dprintf(globals()->all_opened_fds[2], "42sh: no env\n");
		exit(1);
	}
	else if (er == 2)
	{
		ft_free_str(globals()->g_env);
		free(globals()->g_cp);
		ft_dprintf(globals()->all_opened_fds[2], "42sh: malloc error\n");
		exit(1);
	}
}

void	ft_error_pipe(int er, char *str)
{
	if (er == 1)
	{
		ft_putstr_fd("42sh: command not found: ", globals()->all_opened_fds[2]);
		ft_putendl_fd(str, globals()->all_opened_fds[2]);
	}
	if (er == 2)
	{
		ft_putstr_fd("42sh: permission denied: ", globals()->all_opened_fds[2]);
		ft_putendl_fd(str, globals()->all_opened_fds[2]);
	}
}

int		ft_error_args(t_exectoken *tmp)
{
	if (tmp->file_args == NULL && tmp->file_opt == NULL)
		return (0);
	else if (!(tmp->file_opt[1]))
	{
		ft_putendl_fd("42sh: parse error near `\\n'", globals()->all_opened_fds[2]);
		return (0);
	}
	return (0);
}
