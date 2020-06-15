/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 15:23:39 by wstygg            #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

static int			check_flag_3(const char *str, t_fc *f)
{
	register int	i;
	char			c;

	if (str[0] != '-')
		return (-1);
	i = 0;
	while (str[++i])
	{
		c = str[i];
		if (c == 'n')
			f->n = 1;
		else if (c == 's')
			f->silent = 1;
		else if (c == 'l')
			f->l = 1;
		else if (c == 'r')
			f->r = 1;
		else
			return (-1);
	}
	return (0);
}

int					check_flag_2(int *i, char **av, t_fc *f)
{
	if (ft_strequ(av[*i], "-e"))
	{
		if (av[*i + 1] && ++*i)
		{
			if (ft_strequ(av[*i], "vim"))
				f->editor = FC_VIM;
			else if (ft_strequ(av[*i], "emacs"))
				f->editor = FC_EMACS;
			else if (ft_strequ(av[*i], "nano"))
				f->editor = FC_NANO;
			else
				return (-1);
			return (0);
		}
		else
			return (-1);
	}
	return (check_flag_3(av[*i], f));
}

int					calc_h_size(void)
{
	int				size;
	t_memory		*mem;

	size = 0;
	mem = globals()->g_memory_head;
	while (mem)
	{
		size++;
		mem = mem->back;
	}
	return (size);
}

char				*read_fc(int fd)
{
	char			*str;
	char			*ret;

	str = NULL;
	ret = ft_strnew(0);
	while (get_next_line(fd, &str))
	{
		if (*ret)
			ret = ft_strjoin_cd(ret, "\n", 1);
		ret = ft_strjoin_cd(ret, str, 3);
	}
	return (ret);
}

int					check_flag(char **av, t_fc *f)
{
	int				i;
	int				nb;

	i = -1;
	f->hi_s = calc_h_size() - 1;
	while (av[++i])
	{
		if (ft_str_is_numeric_2(av[i], 1))
		{
			nb = ft_atoi(av[i]);
			nb = (nb <= 0) ? f->hi_s + nb + 1 : nb;
			(nb > f->hi_s) ? nb = f->hi_s : 0;
			if (++f->rng[2] % 2)
				f->rng[0] = nb;
			else
				f->rng[1] = nb;
			continue ;
		}
		else if (av[i][0] == '-')
			if (!check_flag_2(&i, av, f))
				continue ;
		return (vivod(2) ? ft_dprintf(globals()->fd[2], FC_US) : 0);
	}
	return (0);
}
