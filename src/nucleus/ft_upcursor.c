/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_upcursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:25:29 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/12 17:28:00 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_upcursor_else(t_readline *p, int len, int i)
{
	int				len2;

	len2 = 0;
	while (--i >= 0 && p->buff[i] != '\n')
		len2++;
	if (i == -1)
		len2 += p->len_hint - 1;
	if (len2 > len)
		len2++;
	else
		len2 = len + 1;
	i = -1;
	while (++i < len2)
		do_left(p);
}

void	ft_upcursor(t_readline *p)
{
	int				i;
	int				len;
	struct winsize	wins;

	if (ioctl(2, TIOCGWINSZ, &wins) == -1)
		return ;
	i = p->index;
	len = 0;
	while (--i >= 0 && p->buff[i] != '\n')
		len++;
	if (i == -1)
	{
		while (++i < wins.ws_col)
			do_left(p);
	}
	else
		ft_upcursor_else(p, len, i);
}
