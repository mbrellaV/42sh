/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:11:44 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/20 14:49:46 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_cleanstr(int i, t_readline *p)
{
	struct winsize	wins;
	int				k;
	int				j;

//	k = 0;
	j = p->index;
//	while (p->buff[++j])
//	{
//		if (p->buff[j] == '\n')
//			k++;
//	}
	if (ioctl(2, TIOCGWINSZ, &wins) == -1)
		return ;
//	k = p->index;
	while (p->index > 0)
	{
		do_left(p);
//		k--;
	}
	p->index = j;
	k = wins.ws_col + i;
//	k = p->len_hint;
	while (--k >= 0)
	{
		write(2, "\b", 1);
	}
//	while (k >= 0)
//	{
//		j = wins.ws_col + i;
//		while (--j >= 0)
//			write(2, "\b", 1);
//		if (k != 0)
//			tputs(tgetstr("up", NULL), 1, ft_c);
//		k--;
//	}
//	tputs(tgetstr("do", NULL), 1, ft_c);
	tputs(tgetstr("cd", NULL), 1, ft_c);
}
