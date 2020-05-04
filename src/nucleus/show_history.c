/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:44:37 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/04 12:49:06 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int		show_history(void)
{
	int	s;
	int	len;
	int	max;
	int	*range;

	s = calc_h_size();
	max = ft_nbrlen(s) + 1;
	range = (int[2]){1, s};
	while (range[0] != range[1])
	{
		len = ft_nbrlen(range[0]);
		while (len++ < max)
			ft_dprintf(globals()->fd[1], " ");
		ft_dprintf(globals()->fd[1], "%d  %s\n", range[0],
				get_hist_by_id(range[0]));
		range[0] += (range[0] < range[1]) ? 1 : -1;
	}
	len = ft_nbrlen(range[0]);
	while (len++ < max)
		ft_dprintf(globals()->fd[1], " ");
	ft_dprintf(globals()->fd[1], "%d  %s\n", range[0],
			get_hist_by_id(range[0]));
	return (1);
}
