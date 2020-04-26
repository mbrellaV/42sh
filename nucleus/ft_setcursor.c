/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setcursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:13:17 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/20 14:49:46 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_setcursor(int i, int max, t_readline *p)
{
	int	k;

	k = p->index;
	p->index = p->len;
	while (max > i)
	{
//		write(2, "\b", 1);
		do_left(p);
		max--;
	}
	p->index = k;
}
