/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_bax_other.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 11:45:44 by plettie           #+#    #+#             */
/*   Updated: 2020/02/06 11:45:52 by plettie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void			del_one_node(char **str, int node_to_del)
{
	int			i;
	int			tmp;
	int			to_del;

	i = 0;
	tmp = 0;
	to_del = 0;
	while (str[i])
	{
		if (node_to_del == i)
		{
			tmp = 1;
			to_del = 1;
		}
		if (to_del == 1)
		{
			ft_strdel(&str[i]);
			to_del = 0;
		}
		if (tmp)
			str[i] = str[i + 1];
		i++;
	}
}

t_lextoken		*bax_full_h(t_lextoken *h, t_dop_str *tmp)
{
	char		*str_for_del;

	if (h->line[0] != '\0')
		h->line = do_zam_str_bax(h->line, tmp);
	str_for_del = h->line;
	if (h->line[0] != '\0')
		h->line = ft_do_zam_eval(h->line);
	if (h->line != str_for_del)
		ft_strdel(&str_for_del);
	return (h);
}

t_lextoken		*bax_full_h2(t_lextoken *h, char *str_for_del, t_lextoken *htmp)
{
	t_lextoken	*save_token;

	if (h->line[0] != '\0')
		h->line = do_zam_str_with_tilda(h->line);
	if (h->line != str_for_del)
		ft_strdel(&str_for_del);
	str_for_del = h->line;
	if (h->line[0] != '\0')
		h->line = ft_do_zam_alias(h->line);
	if (h->line != str_for_del)
		ft_strdel(&str_for_del);
	save_token = h;
	h = do_zam_ravno(h, &htmp);
	if (htmp == NULL)
		return (NULL);
	if (h != save_token)
		h = h->prev;
	return (h);
}

t_dop_str		*add_tmp(t_dop_str *tmp, t_lextoken *h)
{
	tmp->c_b = 0;
	tmp->i_b = -1;
	tmp->str_b = h->line;
	return (tmp);
}

t_lextoken		*do_zam_bax_and_hist_full(t_lextoken *h)
{
	t_dop_str	*tmp;
	t_lextoken	*htmp;
	char		*str_for_del;

	if (!h)
		return (NULL);
	if (!(tmp = ft_memalloc(sizeof(t_dop_str))))
		ft_error_q(2);
	h = do_zam_join_par(h);
	htmp = h;
	while (h != NULL)
	{
		tmp = add_tmp(tmp, h);
		if (h->inhibitor_lvl != 2)
			h = bax_full_h(h, tmp);
		str_for_del = h->line;
		if (h->inhibitor_lvl == 0 && (!(h = bax_full_h2(h, str_for_del, htmp))))
			return (NULL);
		if (h == NULL)
			h = htmp;
		else
			h = h->next;
	}
	ft_kill_str_dop_lex(tmp, NULL);
	return (htmp);
}
