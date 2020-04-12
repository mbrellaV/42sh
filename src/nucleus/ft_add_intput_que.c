/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_intput_que.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:02:36 by qmartina          #+#    #+#             */
/*   Updated: 2020/01/28 17:02:39 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

void	ft_add_intput_que(t_readline *p, t_memory *head, int mod)
{
	t_readline	q;
	int			i;

	q.mod = mod;
	ft_start_read(&q);
	if (p->len >= p->buff_size)
		ft_realloc_buff(p);
	mod == 1 ? p->buff[p->index++] = '\n' : 0;
	mod == 1 ? p->len++ : 0;
	mod == 11? p->index-- : 0;
	mod == 20 ? p->buff[p->index++] = ' ' : 0;
	mod == 20 ? p->buff[p->index++] = ';' : 0;
	mod == 20 ? p->len += 2 : 0;
	ft_read_8(&q, head, mod);
//	dprintf(2, "\nGG111\n");
//	dprintf(open("start_que.txt", O_CREAT | O_RDWR | O_TRUNC,
//			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
//					S_IROTH | S_IWOTH), "startADD:\n%s", p->buff);
//	dprintf(open("buf_que.txt", O_CREAT | O_RDWR | O_TRUNC,
//			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
//					S_IROTH | S_IWOTH), "startADD:\n%s", q.buff);
	i = -1;
	while (q.buff[++i])
	{
		if (p->index >= p->buff_size)
			ft_realloc_buff(p);
		p->buff[p->index++] = q.buff[i];
		p->len++;
	}
//	dprintf(2,"\ni=%d\n", i);
	del_readline(&q);
//	dprintf(open("que.txt", O_CREAT | O_RDWR | O_TRUNC,
//			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
//					S_IROTH | S_IWOTH), "ENDADD:\n%s", p->buff);
	write(2, "\n", 1);
}
