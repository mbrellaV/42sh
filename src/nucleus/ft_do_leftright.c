/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_leftright.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:22:19 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/12 19:15:22 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void		do_up_ifn(t_nline *l, t_readline *p)
{
	int				i;
	int				len;
	struct winsize	wins;

	if (ioctl(2, TIOCGWINSZ, &wins) == -1)
		return ;
	i = l->k;
	len = 0;
	while (--i >= 0 && p->buff[i] != '\n')
		len++;
	if (len % wins.ws_col != 0)
		len %= wins.ws_col;
	l->k -= len;
	while (len >= 0)
	{
		tputs(tgetstr("nd", NULL), 1, ft_c);
		len--;
	}
}

void		do_up_if_izero(t_readline *p)
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
		len += p->len_hint - 1;
	if (len >= wins.ws_col && len % wins.ws_col == 0)
	{
		tputs(tgetstr("up", NULL), 1, ft_c);
		i = 0;
		while (++i < wins.ws_col)
			tputs(tgetstr("nd", NULL), 1, ft_c);
	}
	else
		write(2, "\b", 1);
	p->index--;
}

void		do_left(t_readline *p)
{
	t_nline			l;

	if (p->index > 0 && p->buff[p->index - 1] == '\n')
	{
		l.k = p->index - 1;
		tputs(tgetstr("up", NULL), 1, ft_c);
		do_up_ifn(&l, p);
		if (l.k == 0)
		{
			while (++l.k < p->len_hint)
				tputs(tgetstr("nd", NULL), 1, ft_c);
		}
	}
	if (p->index > 0)
	{
		do_up_if_izero(p);
	}
}

void		do_right(t_readline *p)
{
	int				k;

	k = 0;
	if (p->index >= p->len)
		return ;
	if (p->buff[p->index] && p->buff[p->index] == '\n')
	{
		k = p->index - 1;
		tputs(tgetstr("do", NULL), 1, ft_c);
		while (k > 0 && p->buff[k] != '\n')
		{
			write(2, "\b", 1);
			k--;
		}
		write(2, "\b", 1);
	}
	else
		do_down_if_iwscol(p);
	p->index++;
}

void		ft_do_leftright(t_readline *p)
{
	if (p->sum_read == 186)
		do_left(p);
	else if (p->sum_read == 185)
		do_right(p);
}
