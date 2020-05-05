/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 02:59:46 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/04 13:59:37 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"
#include <stdio.h>

void		do_heredoc(t_pipe *p, char **av)
{
	if (p->flag == 4)
	{
		*p->infile = ft_heredoc(av[p->i + 2]);
		ft_redirect_one(*p->infile, STDIN_FILENO);
	}
}

int			do_simple_redirects(t_pipe *p, int *opened_fds, char **av, int type)
{
	if ((p->flag == 1 || p->flag == 2) && type != 0)
	{
		if (ft_open_flag(av[p->i + 2], p) == -1)
			return (-1);
		ft_redirect_one(*p->outfile, p->st);
		if (ft_find_in_fds(opened_fds, p->st) == 0)
			ft_add_to_fds(opened_fds, p->st);
	}
	if (p->flag == 3 && type != 0)
	{
		if (ft_open_flag(av[p->i + 2], p) == -1)
			return (-1);
		ft_redirect_one(*p->infile, p->st);
	}
	if (type == 0)
	{
		do_redir_into_file(p, av[p->i + 2], STDIN_FILENO, p->st);
		if (ft_find_in_fds(opened_fds, p->st) == 0)
			ft_add_to_fds(opened_fds, p->st);
		dup2(STDOUT_FILENO, STDERR_FILENO);
	}
	return (0);
}

int			do_hard_redirects(t_pipe *p, int *opened_fds, char **av)
{
	if ((ft_strcmp(av[p->i + 1], ">&") == 0 || ft_strcmp(av[p->i + 1], "<&")
		== 0) && ft_strcmp(av[p->i + 2], "-") == 0)
	{
		ft_remove_from_fds(opened_fds, p->st);
		close(p->st);
	}
	else if (ft_strcmp(av[p->i + 1], "<&") == 0)
	{
		if (ft_find_in_fds(opened_fds, p->st) == 0 ||
			ft_find_in_fds(opened_fds, ft_atoi(av[p->i + 2])) == 0)
			return (-10);
		if (isword(av[p->i + 2][0]) && !ft_isdigit(av[p->i + 2][0]))
			return (-9);
		dup2(p->st, p->fd);
	}
	else
	{
		if (isword(av[p->i + 2][0]) && !ft_isdigit(av[p->i + 2][0]))
			do_simple_redirects(p, opened_fds, av, 0);
		else if (ft_find_in_fds(opened_fds, p->st) == 0)
			return (-10);
		else
			dup2(p->fd, p->st);
	}
	return (1);
}

int			ft_fd_flag(char **av, int infile, int outfile, int errfile)
{
	t_pipe	p;
	int		*opened_fds;

	if (!(opened_fds = ft_create_opened_fds()))
		return (-1);
	p = (t_pipe){0, 0, 1, 0, 0, 0, &infile, &outfile, &errfile};
	while (p.i < ft_env_len(av) && av[(p.i)] != NULL)
	{
		if (!(av[p.i][0] >= '0' && av[p.i][0] <= '9'))
			break ;
		p.st = ft_atoi(av[p.i]);
		p.fd = ft_atoi(av[p.i + 2]);
		p.flag = ft_what_flag(av[p.i + 1]);
		if (do_simple_redirects(&p, opened_fds, av, 1) == -1)
			return (return_with_close(opened_fds, -1, NULL, 0));
		do_heredoc(&p, av);
		if (p.flag == 6)
			p.b = do_hard_redirects(&p, opened_fds, av);
		if (p.b < 0)
			return (return_with_close(opened_fds, -1,
				av[p.i + (p.b == -9 ? 2 : 0)], p.b * -1));
		p.i += 3;
		p = (t_pipe){0, p.i, 1, 0, 0, 0, &infile, &outfile, &errfile};
	}
	return (return_with_close(opened_fds, p.fd, NULL, 0));
}
