/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_intput_que.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:02:36 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/12 17:28:00 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

void	ft_add_intput_que(t_readline *p, t_memory *head, int mod)
{
	t_readline	q;
	int			i;

	q.mod = mod;
	q.c = ft_cheak_quote_c(p->buff);
	ft_start_read(&q);
	if (p->len >= p->buff_size)
		ft_realloc_buff(p);
	mod == 1 ? p->buff[p->index++] = '\n' : 0;
	mod == 1 ? p->len++ : 0;
	mod == 11 ? p->index-- : 0;
	mod == 20 ? p->buff[p->index++] = ' ' : 0;
	mod == 20 ? p->buff[p->index++] = ';' : 0;
	mod == 20 ? p->len += 2 : 0;
	ft_read_8(&q, head, mod);
	i = -1;
	while (q.buff[++i])
	{
		if (p->index >= p->buff_size)
			ft_realloc_buff(p);
		p->buff[p->index++] = q.buff[i];
		p->len++;
	}
	del_readline(&q);
	write(2, "\n", 1);
}
