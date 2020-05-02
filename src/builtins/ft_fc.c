/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 22:11:46 by wstygg            #+#    #+#             */
/*   Updated: 2020/04/29 23:20:08 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

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
		}
		else
			return (-1);
	}
	else if (ft_strequ(av[*i], "-s"))
		f->silent = 1;
	else if (ft_strequ(av[*i], "-l"))
		f->l = 1;
	else if (ft_strequ(av[*i], "-r"))
		f->r = 1;
	else
		return (-1);
	return (0);
}

int					calc_h_size()
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

int					check_flag(char **av, t_fc *f)
{
	int				i;
	int				nb;

	i = -1;
	f->h_size = calc_h_size();
	while (av[++i])
	{
		if (ft_str_is_numeric_2(av[i], 1) && av[i][0] &&av[i][1])
		{
			nb = ft_atoi(av[i]);
			nb = (nb <= 0) ? f->h_size - nb + 1 : nb;
			if (nb > f->h_size)
				return (ft_dprintf(globals()->fd[2], "fc range error\n"));
			if (++f->range[2] % 2)
				f->range[0] = nb;
			else
				f->range[1] = nb;
			continue ;
		}
		else if (av[i][0] == '-')
			if (!check_flag_2(&i, av, f))
				continue ;
		return (ft_dprintf(globals()->fd[2], FC_US));
	}
	return (0);
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

int					pick_launch(t_fc flags)
{
	if (flags.silent)
		return (0);
	if (flags.editor == FC_VIM)
		if (launch("vim .fc", 0))
			return (-1);
	if (flags.editor == FC_EMACS)
		if (launch("emacs .fc", 0))
			return (-1);
	if (flags.editor == FC_NANO)
		if (launch("nano .fc", 0))
			return (-1);
	return (0);
}

char				*get_hist_by_id(int id, int len)
{
	int				i;
	char			*ret;
	t_memory		*last;

	i = len;
	if (id < 0)
		return (NULL);
	last = globals()->g_memory_head;
	while (i != id)
	{
		if (last == NULL)
			return (NULL);
		i--;
		last = last->back;
	}
	if (last == NULL)
		return (NULL);
	ret = last->inp;
	return (ret);
}

int					do_fc_l(t_fc flags)
{
	int				*range;
	int				dop;

	dop = 0;
	if (!flags.range[2])
		range = (int[2]){flags.h_size - 16, flags.h_size};
	else if (flags.range[0])
		range = (int[2]){flags.range[0], flags.h_size};
	else
		range = (int[2]){flags.range[0], flags.range[1]};
	if (range[0] < 0)
		range = (int[2]){0, range[1]};
	while (get_hist_by_id(range[0], flags.h_size) == NULL)
	{
		dop++;
		range[0]++;
	}
	if (flags.r)
		range = (int[2]){range[1], range[0]};
	while (range[0] != range[1])
	{
		ft_dprintf(globals()->fd[1], "%d\t%s\n", range[0] - dop, get_hist_by_id(range[0], flags.h_size));
		range[0] += (range[0] < range[1]) ? 1 : -1;
	}
	ft_dprintf(globals()->fd[1], "%d\t%s\n", range[0] - dop, get_hist_by_id(range[0], flags.h_size));
	return (1);
}

int					do_fc_regular(int fd, t_fc flags)
{
	if (!ft_dprintf(fd, "%s", globals()->g_memory_head->inp))
		return (ft_dprintf(globals()->fd[2], "fc write error!\n"));
	close(fd);
	if (pick_launch(flags))
		return (-1);
	return (0);
}

int					do_fc(char **av)
{
	int				fd;
	t_fc			f;
	char			*command;

	f = (t_fc){.range = {0, 0, 0}, .r = 0, .l = 0, .silent = 0, .editor = FC_VIM};
	if (check_flag(++av, &f) || f.range[0] > f.h_size)
		return ((f.range[0] > f.h_size) ? ft_dprintf(globals()->fd[2], "fc range error!\n") : 0);
	delete_fc_command();
	if ((fd = open(".fc", O_CREAT | O_RDWR | O_TRUNC,
				   S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
				   S_IROTH | S_IWOTH, 0644)) == -1)
		return (ft_dprintf(globals()->fd[2], "fc create error!\n"));
	if (f.l)
		return (do_fc_l(f));
	else
	{
		if (do_fc_regular(fd, f))
			return (-1);
		if ((fd = open(".fc", O_RDONLY)) == -1)
			return (ft_dprintf(globals()->fd[2], "fc read error!\n"));
		command = read_fc(fd);
		if (launch(command, 1))
			return (-1);
		free(command);
		return (remove(".fc") ? ft_dprintf(globals()->fd[2], "delete error!\n") : 0);
	}
}
