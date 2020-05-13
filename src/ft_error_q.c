/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_q.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 14:47:54 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/12 22:36:30 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

void	ft_error_q(int er)
{
	if (er == 1)
	{
		ft_free_str(globals()->g_env);
		ft_dprintf(globals()->fd[2], "42sh: no env\n");
		exit(1);
	}
	else if (er == 2)
	{
		ft_free_str(globals()->g_env);
		free(globals()->g_cp);
		ft_dprintf(globals()->fd[2], "42sh: malloc error\n");
		exit(1);
	}
	if (er == 3)
	{
		ft_dprintf(globals()->fd[2], "is not a terminal\n");
		exit(1);
	}
}

int		ft_error_d(t_readline *p)
{
	free(p->buff);
	if (p->mod == 0 || p->mod == 2)
		p->buff = ft_strdup("exit");
	else if (p->mod == 1)
	{
		p->buff = ft_strnew(2);
		p->buff[0] = p->c;
	}
	else if (p->mod == 20)
	{
		ft_dprintf(globals()->fd[2],
				"Syntax error: end of file unexpected (expecting \")\")\n");
		ft_dprintf(globals()->fd[2], "exit\n");
		exit(1);
	}
	else
		p->buff = ft_strnew(1);
	return (1);
}

void	ft_error_pipe(int er, char *str)
{
	if (er == 1)
	{
		ft_putstr_fd("42sh: command not found: ", globals()->fd[2]);
		ft_putendl_fd(str, globals()->fd[2]);
	}
	if (er == 2)
	{
		ft_putstr_fd("42sh: permission denied: ", globals()->fd[2]);
		ft_putendl_fd(str, globals()->fd[2]);
	}
}

int		ft_error_args(t_exectoken *tmp)
{
	if (tmp->file_args == NULL && tmp->file_opt == NULL)
		return (0);
	else if (!(tmp->file_opt[1]))
	{
		ft_putendl_fd("42sh: parse error near `\\n'", globals()->fd[2]);
		return (0);
	}
	return (0);
}
