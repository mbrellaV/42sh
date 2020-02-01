/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_q.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 14:47:54 by qmartina          #+#    #+#             */
/*   Updated: 2019/12/11 14:47:56 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

void	ft_error_q(int er)
{
	if (er == 1)
	{
		ft_free_str(g_env);
		ft_printf("21sh: no env\n");
		exit(1);
	}
	else if (er == 2)
	{
		ft_free_str(g_env);
		free(g_cp);
		ft_printf("21sh: malloc error\n");
		exit(1);
	}
}

void	ft_error_pipe(int er, char *str)
{
	if (er == 1)
	{
		ft_putstr_fd("21sh: command not found: ", 2);
		ft_putendl_fd(str, 2);
	}
	if (er == 2)
	{
		ft_putstr_fd("21sh: permission denied: ", 2);
		ft_putendl_fd(str, 2);
	}
}

int		ft_error_args(t_exectoken *tmp)
{
	if (tmp->file_args == NULL && tmp->file_opt == NULL)
		return (0);
	else if (!(tmp->file_opt[1]))
	{
		ft_putendl_fd("21sh: parse error near `\\n'", 2);
		return (0);
	}
	return (0);
}
