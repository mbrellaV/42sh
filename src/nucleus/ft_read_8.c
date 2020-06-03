/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_8.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:15:41 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/12 22:36:31 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

void			ft_cheak_sum(t_readline *p, t_memory **h)
{
	p->sum_read == 186 || p->sum_read == 185 ? ft_do_leftright(p) : NULL;
	p->sum_read == 183 || p->sum_read == 184 ? ft_putmemory(h, p) : NULL;
	p->sum_read == 341 ? ft_upcursor(p) : NULL;
	p->sum_read == 342 ? ft_downcursor(p) : NULL;
	p->sum_read == 297 || p->sum_read == 298 || p->sum_read == 190 ||
							p->sum_read == 188 ? ft_arrows(p) : NULL;
}

void			ft_add_his(t_readline *p, t_memory *h)
{
	find_history(p, h);
	ft_cleanstr(p->index, p);
	p->len_hint = ft_printf_helper(p->mod);
	ft_putstr_fd(p->buff, 2);
}

void			do_hist_add_with_slash_n(int mod, t_readline *p)
{
	if (globals()->g_memory_head->inp && mod != 0)
	{
		if (globals()->g_memory_head->inp[0] != '\0')
			ft_strcat(globals()->g_memory_head->inp, "\n");
		ft_strcat(globals()->g_memory_head->inp, p->buff);
	}
}

void			ft_read_8(t_readline *p, t_memory *head, int mod)
{
	char		buf[8];
	int			rt;
	t_memory	*h;

	p->mod = mod;
	h = head;
	while ((rt = read(0, buf, 8)) && buf[0] != '\n')
	{
		p->sum_read = ft_add_sumchar(buf, rt);
		if (!ft_read_helper(p, &h, rt, buf))
			return ;
	}
	do_hist_add_with_slash_n(mod, p);
	p->index = do_zamena_slash(p->buff, p);
	do_job_del();
}
