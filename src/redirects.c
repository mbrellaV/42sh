/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_whatis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 18:29:17 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/04 13:17:20 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

void	do_heredoc_in_builtins(int *opened_fds, char *av, int flag)
{
	int		infile;

	if (flag == 4)
	{
		infile = ft_heredoc(av);
		opened_fds[0] = infile;
	}
}

int		do_simple_redir(int *opened_fds, char **av, int flag, int i)
{
	int		infile;
	int		outfile;

	infile = 0;
	outfile = 1;
	if (flag == 1 || flag == 2)
	{
		if (ft_open_flag_in_builtins(av[i + 2], flag, &infile, &outfile) == -1)
			return (-1);
		opened_fds[ft_atoi(av[i])] = outfile;
	}
	if (flag == 3)
	{
		if (ft_open_flag_in_builtins(av[i + 2], flag, &infile, &outfile) == -1)
			return (-1);
		opened_fds[0] = infile;
	}
	return (0);
}

int		do_hard_redir(int *opened_fds, char **av, int i, int flag)
{
	if ((ft_strcmp(av[i + 1], ">&") == 0 || ft_strcmp(av[i + 1], "<&") == 0)
		&& ft_strcmp(av[i + 2], "-") == 0)
	{
		ft_remove_from_fds(opened_fds, ft_atoi(av[i]));
	}
	else if (ft_strcmp(av[i + 1], "<&") == 0)
	{
		if (ft_find_in_fds(opened_fds, ft_atoi(av[i + 2])) == 0)
			return (-10);
		if (isword(av[i + 2][0]) && !ft_isdigit(av[i + 2][0]))
			return (-9);
		opened_fds[ft_atoi(av[i + 2])] = ft_atoi(av[i]);
	}
	else
	{
		if (isword(av[i + 2][0]) && !ft_isdigit(av[i + 2][0]))
			do_simple_redir(opened_fds, av, flag, i);
		else if (ft_find_in_fds(opened_fds, ft_atoi(av[i])) == 0)
			return (-10);
		else
			opened_fds[ft_atoi(av[i])] = ft_atoi(av[i + 2]);
	}
	return (1);
}

int		set_b(int *fd, int i, int flag, char **av)
{
	int		b;

	b = 0;
	do_heredoc_in_builtins(fd, av[i + 2], flag);
	if (flag == 6)
		b = do_hard_redir(fd, av, i, flag);
	return (b);
}

int		set_redirects_for_builtins(char **av)
{
	int		*opened_fds;
	int		i;
	int		flag;
	int		b;

	if (!(opened_fds = ft_create_opened_fds()))
		return (-1);
	i = 0;
	while (i < ft_env_len(av) && av[(i)] != NULL)
	{
		if (!(av[i][0] >= '0' && av[i][0] <= '9'))
			break ;
		flag = ft_what_flag(av[i + 1]);
		if (do_simple_redir(opened_fds, av, flag, i) == -1)
			return (return_with_close(opened_fds, -1, NULL, 0));
		b = set_b(opened_fds, i, flag, av);
		if (b < 0)
			return (return_with_close(opened_fds, -1,
					ft_strdup(av[i + (b == -9 ? 2 : 0)]), b * -1));
			i += 3;
	}
	free(globals()->fd);
	globals()->fd = opened_fds;
	return (1);
}
