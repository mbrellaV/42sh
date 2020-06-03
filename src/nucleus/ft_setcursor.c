/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setcursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:13:17 by qmartina          #+#    #+#             */
/*   Updated: 2020/06/03 20:13:49 by wstygg           ###   ########.fr       */
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
		do_left(p);
		max--;
	}
	p->index = k;
}
