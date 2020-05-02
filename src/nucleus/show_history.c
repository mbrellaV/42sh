/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:44:37 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/29 23:22:06 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

int		show_history()
{
	int	s;
	int	len;
	int	max;
	int	*range;
	int dop;

	s = calc_h_size();
	dop = 0;
	max = ft_nbrlen(s) + 1;
	range = (int[2]){0, s};
	while (get_hist_by_id(range[0]) == NULL)
	{
		dop++;
		range[0]++;
	}
	while (range[0] != range[1])
	{
		len = ft_nbrlen(range[0]);
		while (len++ < max)
			ft_dprintf(globals()->fd[1], " ");
		ft_dprintf(globals()->fd[1], "%d  %s\n", range[0] - dop, get_hist_by_id(range[0]));
		range[0] += (range[0] < range[1]) ? 1 : -1;
	}
	len = ft_nbrlen(range[0]);
	while (len++ < max)
		ft_dprintf(globals()->fd[1], " ");
	ft_dprintf(globals()->fd[1], "%d  %s\n", range[0] - dop, get_hist_by_id(range[0]));
	return (1);
}
