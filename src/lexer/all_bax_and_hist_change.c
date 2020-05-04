/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_bax_and_hist_change.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 17:52:35 by mbrella           #+#    #+#             */
/*   Updated: 2020/05/02 13:20:11 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

static void		do_join(t_lextoken **doph, t_lextoken **lextmp1)
{
	t_lextoken	*lextmp;
	char		*tmp;
	t_lextoken	*h;

	h = *doph;
	tmp = (h)->next->line;
	(h)->next->is_near_word = 0;
	(h)->next->line = ft_strjoin((h)->line, (h)->next->line);
	ft_strdel(&tmp);
	tmp = (h)->line;
	if ((h)->prev != NULL)
	{
		(h)->prev->next = (h)->next;
		(h)->next->prev = (h)->prev;
	}
	else
	{
		(h)->next->prev = NULL;
		*lextmp1 = (h)->next;
	}
	ft_strdel(&tmp);
	lextmp = h;
	*doph = (h)->next;
	free(lextmp);
}

t_lextoken		*do_zam_join_par(t_lextoken *h)
{
	t_lextoken	*lextmp1;

	lextmp1 = h;
	while (h)
	{
		if (h->next && h->next->is_near_word == 1)
			do_join(&h, &lextmp1);
		else
			h = h->next;
	}
	return (lextmp1);
}

int				do_all_zams_with_inhibitor(t_lextoken *h, t_lextoken
					**doph, t_dop_str *tmp, t_lextoken **first_token)
{
	if (h->inhibitor_lvl != 2)
	{
		if (!(h->line = do_zam_str_bax(h->line, tmp)))
			return (-1);
		if (!(h->line = ft_do_zam_eval(h->line)))
			return (-1);
	}
	if (h->inhibitor_lvl == 0)
	{
		if (!(h->line = do_zam_str_with_tilda(h->line)))
			return (-1);
		*doph = do_zam_ravno(h, first_token);
	}
	else
		*doph = h->next;
	return (1);
}

t_lextoken		*do_zam_bax_and_hist_full(t_lextoken *h, t_lextoken **save_tmp)
{
	t_dop_str	*tmp;
	t_lextoken	*first_token;

	if (!h)
		return (NULL);
	*save_tmp = h;
	if (!(tmp = ft_memalloc(sizeof(t_dop_str))))
		ft_error_q(2);
	h = do_zam_join_par(h);
	first_token = h;
	while (h != NULL)
	{
		if (h->operator_type == -1 && h->is_near_opt > 0 &&
		ft_error(5, h->line))
			return (ft_kill_str_dop_lex(tmp, NULL));
		if (*h->line == '\0')
		{
			h = h->next;
			continue ;
		}
		if (do_all_zams_with_inhibitor(h, &h, tmp, &first_token) == -1)
			return (ft_kill_str_dop_lex(tmp, NULL));
	}
	*save_tmp = first_token;
	return (ft_kill_str_dop_lex(tmp, first_token));
}
