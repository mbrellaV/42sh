/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_upcursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:25:29 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/02 13:20:11 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_upcursor(t_readline *p)
{
	struct winsize	wins;
	int				i;

	if (ioctl(2, TIOCGWINSZ, &wins) == -1)
		return ;
	if (p->index <= wins.ws_col)
	{
		while (p->index > 0)
			do_left(p);
		p->index = 0;
	}
	else
	{
		i = p->index - wins.ws_col;
		while (p->index > i)
			do_left(p);
		p->index++;
	}
}
