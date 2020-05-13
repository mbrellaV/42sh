/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmemory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:52:54 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/12 22:36:31 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

static void		ft_dop_history(t_memory *q, t_readline *p, int k)
{
	if (k == 1)
	{
		ft_cleanstr(p->index, p);
		free(p->buff);
		p->buff_size = 8 + (int)ft_strlen((q)->inp);
		p->buff = ft_strnew(p->buff_size);
		ft_strcpy(p->buff, (q)->inp);
		p->index = (int)ft_strlen(p->buff);
		p->len = (int)ft_strlen(p->buff);
		p->len_hint = ft_printf_helper(p->mod);
		ft_putstr_fd((q)->inp, 2);
	}
	else if (k == 2)
	{
		ft_cleanstr(p->index, p);
		free(p->buff);
		p->buff_size = 64;
		p->buff = ft_strnew(p->buff_size);
		p->index = 0;
		p->len = 0;
		p->len_hint = ft_printf_helper(p->mod);
		ft_putstr_fd(p->buff, 2);
	}
}

void			ft_putmemory(t_memory **q, t_readline *p)
{
	if (*q && (*q)->back && (*q)->back->back == NULL && p->sum_read == 183)
		ft_dop_history((*q), p, 1);
	else if ((*q) && p->sum_read == 183 && (*q)->back && (*q)->back->back)
	{
		if (globals()->g_his_d != 0)
			*q = (*q)->back;
		ft_dop_history(*q, p, 1);
		if ((*q)->next == NULL)
			globals()->g_his_d = 1;
	}
	else if ((*q) && p->sum_read == 184 && (*q)->next)
	{
		if ((*q)->next == NULL)
			globals()->g_his_d = 0;
		(*q) = (*q)->next;
		ft_dop_history((*q), p, 1);
	}
	else if (p->sum_read == 184)
	{
		ft_dop_history((*q), p, 2);
		globals()->g_his_d = 0;
	}
}
