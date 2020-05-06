/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_downcursor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:27:19 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/20 14:49:46 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_downcursor(t_readline *p)
{
	int i;
	int len;
	struct winsize	wins;

	if (ioctl(2, TIOCGWINSZ, &wins) == -1)
		return ;
	i = p->index;
	len = 0;
	while (++i < p->len && p->buff[i] != '\n')
		len++;
	if (i == p->len)
	{
		i = -1;
		while (++i < wins.ws_col)
			do_right(p);
	}
	else
	{
		i = p->index;
		while (--i > 0 && p->buff[i] != '\n')
			len++;
		if (i == -1)
			len += p->len_hint;
		i = -1;
		while (++i < len + 2)
			do_right(p);
	}
}
