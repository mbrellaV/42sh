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
	int			s;
	t_memory	*dop;

	tmp = q;
	s = 0;
	if (((i = 1)) && !vivod(1))
		return (1);
	while (tmp->back)
		tmp = tmp->back;
	dop = tmp;
	while (tmp != NULL)
	{
		s++;
		tmp = tmp->next;
	}
	tmp = dop;
	while (tmp->next)
	{
		ft_dprintf(globals()->fd[1], "%d\t%s\n", i, tmp->inp);
		tmp = tmp->next;
		i++;
	}
	return (0);
}
