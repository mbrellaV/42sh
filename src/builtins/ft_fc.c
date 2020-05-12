/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 22:11:46 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/12 17:28:00 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

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

static int			do_fc_l(t_fc flags)
{
	int				*range;

	range = flags.rng;
	while (range[0] != range[1])
	{
		ft_dprintf(globals()->fd[1], "%d\t%s\n", range[0],
				get_hist_by_id(range[0]));
		range[0] += (range[0] < range[1]) ? 1 : -1;
	}
	ft_dprintf(globals()->fd[1], "%d\t%s\n", range[0],
			get_hist_by_id(range[0]));
	return (1);
}

static int			do_fc_regular(int fd, t_fc flags)
{
	int				*range;

	range = flags.rng;
	if (!flags.rng[2])
		range[0] = range[1];
	else if (flags.rng[2] == 1)
		range[1] = range[0];
	while (range[0] != range[1])
	{
		if (!ft_dprintf(fd, "%s\n", get_hist_by_id(range[0])))
			return (ft_dprintf(globals()->fd[2], "fc write error!\n"));
		range[0] += (range[0] < range[1]) ? 1 : -1;
	}
	if (!ft_dprintf(fd, "%s\n", get_hist_by_id(range[0])))
		return (ft_dprintf(globals()->fd[2], "fc write error!\n"));
	close(fd);
	if (pick_launch(flags))
		return (-1);
	return (0);
}

static void			work_with_range(t_fc *fc)
{
	int				save;

	if (!fc->rng[2])
	{
		fc->rng[0] = fc->hi_s <= 16 ? 1 : fc->hi_s - 16;
		fc->rng[1] = fc->hi_s;
	}
	else if (!fc->rng[1])
		fc->rng[1] = fc->hi_s;
	if (fc->r)
	{
		save = fc->rng[0];
		fc->rng[0] = fc->rng[1];
		fc->rng[1] = save;
	}
}

int					do_fc(char **av)
{
	int				fd;
	t_fc			f;
	char			*command;

	f = (t_fc){.rng = {0, 0, 0}, .r = 0, .l = 0,
			.silent = 0, .editor = FC_VIM};
	if (check_flag(++av, &f))
		return ((f.rng[0] > f.hi_s) ? ft_dprintf(globals()->fd[2], FC_US) : 0);
	delete_fc_command();
	work_with_range(&f);
	if (f.l)
		return (do_fc_l(f));
	else if ((fd = open(".fc", O_CREAT | O_RDWR | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
			S_IROTH | S_IWOTH, 0644)) == -1)
		return (ft_dprintf(globals()->fd[2], "fc create error!\n"));
	if (do_fc_regular(fd, f))
		return (-1);
	if ((fd = open(".fc", O_RDONLY)) == -1)
		return (ft_dprintf(globals()->fd[2], "fc read error!\n"));
	command = read_fc(fd);
	if (launch(command, 1))
		return (-1);
	free(command);
	return (remove(".fc") ? ft_dprintf(globals()->fd[2], "delete err!\n") : 0);
}
