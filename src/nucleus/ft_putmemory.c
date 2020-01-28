/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmemory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:52:54 by qmartina          #+#    #+#             */
/*   Updated: 2020/01/28 16:52:55 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

void		ft_putmemory(t_memory ***q, int sum, t_readline *p)
{
	static int		d = 0;


	if (**q && (**q)->back && (**q)->back->back == NULL && sum == 183)
		ft_dop_history(q, input, flag, 1);
	if (**q && sum == 183 && (**q)->back && (**q)->back->back)
	{
		if (d != 0)
			**q = (**q)->back;
		ft_dop_history(q, input, flag, 1);
		if ((**q)->next == NULL)
			d = 1;
	}
	if (**q && sum == 184 && (**q)->next)
	{
		if ((**q)->next == NULL)
			d = 0;
		**q = (**q)->next;
		ft_dop_history(q, input, flag, 1);
	}
	else if (sum == 184)
	{
		ft_dop_history(q, input, flag, 2);
		d = 0;
	}
}
