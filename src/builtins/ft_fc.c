/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 22:11:46 by wstygg            #+#    #+#             */
/*   Updated: 2020/04/29 00:50:43 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

static int			check_flag(char **av, t_fc *f)
{
	register int	i;

	i = -1;
	while (av[++i])
	{
		if (av[i][0] == '-')
		{
			if (ft_strequ(av[i], "-s") && (f->silent = 1))
				continue ;
			else if (ft_strequ(av[i], "-e"))
				if (av[i + 1] && ++i)
				{
					if (ft_strequ(av[i], "vim") && (f->editor = FC_VIM))
						continue ;
					if (ft_strequ(av[i], "emacs") && (f->editor = FC_EMACS))
						continue ;
					if (ft_strequ(av[i], "nano") && (f->editor = FC_NANO))
						continue ;
				}
		}
		return (ft_dprintf(globals()->all_opened_fds[2], FC_US));
	}
	return (0);
}


static char			*read_fc(int fd)
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

static int			pick_launch(t_fc flags)
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

int					do_fc(char **av)
{
	int				fd;
	t_fc			flags;
	char			*command;

	flags = (t_fc){.silent = 0, .editor = FC_VIM};
	if (check_flag(++av, &flags))
		return (-1);
	delete_fc_command();
	if ((fd = open(".fc", O_RDWR | O_CREAT, 0644)) == -1)
		return (ft_dprintf(globals()->all_opened_fds[2], "fc create error!\n"));
	if (!ft_dprintf(fd, "%s", globals()->g_memory_head->inp))
		return (ft_dprintf(globals()->all_opened_fds[2], "fc write error!\n"));
	close(fd);
	if (pick_launch(flags))
		return (-1);
	if ((fd = open(".fc", O_RDONLY)) == -1)
		return (ft_dprintf(globals()->all_opened_fds[2], "fc read error!\n"));
	command = read_fc(fd);
	if (launch(command, 1))
		return (-1);
	free(command);
	if (remove(".fc"))
		return (ft_dprintf(globals()->all_opened_fds[2], "fc delete error!\n"));
	return (0);
}
