/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_downcursor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:27:19 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/02 13:20:11 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_downcursor(t_readline *p)
{
	struct winsize	wins;
	int				i;

	if (ioctl(2, TIOCGWINSZ, &wins) == -1)
		return ;
	if ((p->len - p->index) > wins.ws_col)
	{
		i = -1;
		while (++i < wins.ws_col)
		{
			do_right(p);
		}
	}
	else
	{
		while (p->index < p->len)
		{
			do_right(p);
		}
	}
}
