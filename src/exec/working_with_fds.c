/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   working_with_fds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 18:52:42 by wstygg            #+#    #+#             */
/*   Updated: 2020/06/03 20:13:48 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int		ft_find_in_fds(int *opened_fds, int fd_to_find)
{
	if (opened_fds == NULL)
		return (-1);
	if (fd_to_find < 0 || fd_to_find > 9)
		return (-1);
	if (opened_fds[fd_to_find] >= 0)
		return (1);
	return (0);
}

int		ft_add_to_fds(int *opened_fds, int fd_to_add)
{
	if (opened_fds == NULL)
		return (-1);
	if (fd_to_add < 0 || fd_to_add > 9)
		return (-1);
	opened_fds[fd_to_add] = 1;
	return (1);
}

int		ft_remove_from_fds(int *opened_fds, int fd_to_remove)
{
	if (opened_fds == NULL)
		return (-1);
	if (fd_to_remove < 0 || fd_to_remove > 9)
		return (-1);
	opened_fds[fd_to_remove] = -1;
	return (1);
}

int		*ft_create_opened_fds(void)
{
	int	*opened_fds;

	if (!(opened_fds = (int *)ft_memalloc(sizeof(int) * 10)))
		return (NULL);
	opened_fds[0] = 0;
	opened_fds[1] = 1;
	opened_fds[2] = 2;
	opened_fds[3] = -1;
	opened_fds[4] = -1;
	opened_fds[5] = -1;
	opened_fds[6] = -1;
	opened_fds[7] = -1;
	opened_fds[8] = -1;
	opened_fds[9] = -1;
	return (opened_fds);
}
