/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_bax_and_hist_change.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 17:52:35 by mbrella           #+#    #+#             */
/*   Updated: 2020/02/01 17:52:37 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

int				do_all_zams_with_inhibitor(t_lextoken *h, t_lextoken **doph, t_dop_str	*tmp)
{
	if (h->inhibitor_lvl != 2)
	{
		h->line = do_zam_str_bax(h->line, tmp);
		h->line = ft_do_zam_eval(h->line);
	}
	if (h->inhibitor_lvl == 0)
	{
		h->line = do_zam_str_with_tilda(h->line);
		h->line = ft_do_zam_alias(h->line);
		*doph = do_zam_ravno(h);
	}
	else
	{
		*doph = h->next;
	}
	return (1);
}

t_lextoken		*do_zam_bax_and_hist_full(t_lextoken *h)
{
	t_dop_str	*tmp;
	t_lextoken  *htmp;

	if (!h)
		return (NULL);
	if (!(tmp = ft_memalloc(sizeof(t_dop_str))))
		ft_error_q(2);
	h = do_zam_join_par(h);
	htmp = h;
	while (h != NULL)
	{
		tmp->c_b = 0;
		tmp->i_b = -1;
		tmp->str_b = h->line;
		if (*h->line == '\0')
		{
			h = h->next;
			continue ;
		}
		do_all_zams_with_inhibitor(h, &h, tmp);
	}
	ft_kill_str_dop_lex(tmp, NULL);
	return (htmp);
}
