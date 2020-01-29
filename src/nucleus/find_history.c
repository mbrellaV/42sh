/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:45:21 by qmartina          #+#    #+#             */
/*   Updated: 2020/01/29 21:45:27 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

void 	find_history(t_readline *p, t_memory *q)
{
	t_readline	r;
	int			rt;
	char 		buf[8];
	char 		*tmp;

	ft_start_read(&r);
	ft_cleanstr(p->index + p->len_hint, p);
//	if (p->buff[0] == '\0')
//	{
//		dprintf(2, "(reverse-i-search)`': %s", p->buff);
//		rt = read(0, buf, 8);
//	}
//	dprintf(2, "(reverse-i-search)`': %s");//////////////////////////////
	ft_putstr_fd(GRN, 2);
	ft_putstr_fd("(reverse-i-search)`':", 2);
	ft_putstr_fd(RESET, 2);
	write(2, "\b\b", 2);
	r.len_hint = (int)ft_strlen("(reverse-i-search)`");
	tmp = NULL;
	while ((rt = read(0, buf, 8)) && buf[0] != '\n')
	{
		r.sum_read = ft_add_sumchar(buf, rt);
		if (rt > 1)
		{
			if (tmp != NULL)
			{
				free(p->buff);
				p->buff = ft_strdup(tmp);
				p->index = ft_strlen(tmp);
				p->len = p->index;
				free(tmp);
			}
			ft_cleanstr(r.index + r.len_hint, &r);
			return ;;
		}
		else if (r.sum_read >= 32 && r.sum_read <= 127)
		{
			if (r.len == r.buff_size)
				ft_realloc_buff(&r);
			if (r.sum_read == 127)
			{
				if (r.index > 0)
				{
					r.buff[--r.index] = 0;
					write(2, "\b", 1);
				}
			}
			else
				r.buff[r.index++] = buf[0];
			tmp = get_num_from_hist_cons(q, r.buff);
			ft_cleanstr(r.index + r.len_hint, &r);
			ft_putstr_fd(GRN, 2);
			ft_putstr_fd("(reverse-i-search)`", 2);
			ft_putstr_fd(RESET, 2);
			ft_putstr_fd(BLU, 2);
			ft_putstr_fd(r.buff, 2);
			ft_putstr_fd(RESET, 2);
			ft_putstr_fd(GRN, 2);
			ft_putstr_fd("': ", 2);
			ft_putstr_fd(RESET, 2);
			ft_putstr_fd(tmp, 2);
			ft_setcursor(0, (int)ft_strlen(tmp) + 3);
		}
		else
		{
			if (tmp != NULL)
			{
				free(p->buff);
				p->buff = ft_strdup(tmp);
				p->index = ft_strlen(tmp);
				p->len = p->index;
				free(tmp);
			}
			ft_cleanstr(r.index + r.len_hint, &r);
			return ;
		}
	}
}
