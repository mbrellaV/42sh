/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_hist_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:46:28 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/12 22:36:31 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int			open_hist_file(int type)
{
	int			fd;
	char		*home_dir;
	char		*tmp;

	if (!(home_dir = ft_get_var("HOME", globals()->g_env)))
		return (-1);
	tmp = ft_strjoin(home_dir, "/.42hist");
	dprintf(2, "\n|%s|\n", tmp);
	if (type == 0 && (fd = open(tmp, O_CREAT | O_RDWR | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) < 0)
	{
		ft_strdel(&home_dir);
		ft_strdel(&tmp);
		return (-1);
	}
	if (type == 1 && (fd = open(tmp, O_RDWR)) < 0)
	{
		ft_strdel(&home_dir);
		ft_strdel(&tmp);
		return (-1);
	}
	ft_strdel(&home_dir);
	ft_strdel(&tmp);
	return (fd);
}
