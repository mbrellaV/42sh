/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:44:37 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/12 22:36:31 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int		show_history(t_memory *q)
{
	t_memory	*tmp;
	int			i;
	int			sum;
	t_memory	*dop;

	i = 0;
	sum = 0;
	tmp = q;
	if (!vivod(1))
		return (1);
	while (tmp->back)
		tmp = tmp->back;
	dop = tmp;
	while (tmp != NULL)
	{
		sum++;
		tmp = tmp->next;
	}
	tmp = dop;
	while (tmp->next)
	{
		if (sum - i < 16)
			ft_dprintf(globals()->fd[1], "%d\t%s\n", i, tmp->inp);
		tmp = tmp->next;
		i++;
	}
	return (1);
}
