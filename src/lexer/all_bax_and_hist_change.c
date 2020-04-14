/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_bax_and_hist_change.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 17:52:35 by mbrella           #+#    #+#             */
/*   Updated: 2020/04/14 11:08:28 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

t_lextoken		*do_zam_join_par(t_lextoken *h)
{
    char        *tmp;
    t_lextoken  *lextmp;
	t_lextoken  *lextmp1;

	lextmp1 = h;
    while (h)
	{
    	if (h->next && h->next->is_near_word == 1)
		{
			tmp = h->next->line;
			h->next->inhibitor_lvl = h->inhibitor_lvl;
			h->next->line = ft_strjoin(h->line, h->next->line);
			ft_strdel(&tmp);
			tmp = h->line;
			if (h->prev != NULL)
			{
				h->prev->next = h->next;
				h->next->prev = h->prev;
			}
			else
			{
				h->next->prev = NULL;
				lextmp1 = h->next;
			}

			ft_strdel(&tmp);
			lextmp = h;
			h = h->next;
			free(lextmp);
			h->is_near_word = 0;
			h->inhibitor_lvl = 0;
		}
    	else
    		h = h->next;
	}
	return (lextmp1);
}

void        del_one_node_in_lextokens(t_lextoken *token_to_del)
{
	if (token_to_del->prev)
	{
		token_to_del->prev->next = token_to_del->next;
	}
	if (token_to_del->next)
	{
		token_to_del->next->prev = token_to_del->prev;
	}
	ft_strdel(&token_to_del->line);
	free(token_to_del);
}

t_lextoken		*do_zam_ravno(t_lextoken *h)
{
    char		*tmp1;
    char		*tmp2;
    t_lextoken	*dop;

    if (h != NULL && h->line != NULL && ft_strstr(h->line, "=") &&
    ((h->next == NULL || is_cmd_delim(get_op_type(h->next->line))) && h->prev == NULL))
    {
        tmp1 = ft_strsub(h->line, 0, ft_strstr(h->line, "=") - h->line);
        tmp2 = ft_strsub(h->line, ft_strstr(h->line, "=") - h->line + 1, ft_strlen(h->line));
        set_new_var(tmp1, tmp2, &g_all_var);
        ft_strdel(&tmp1);
		ft_strdel(&tmp2);
		dop = h->next;
		del_one_node_in_lextokens(h);
		return (dop);
    }
    else if (h != NULL && h->line != NULL && ft_strstr(h->line, "=") && h->prev == NULL)
	{
		dop = h->next;
		del_one_node_in_lextokens(h);
		return (dop);
	}
    if (h != NULL)
		return (h->next);
	return (NULL);
}

int				do_all_zams_with_inhibitor(t_lextoken *h, t_lextoken **doph, t_dop_str	*tmp)
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
		if (!(h->line = ft_do_zam_alias(h->line)))
			return (-1);
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
		if (h->operator_type == -1 && h->is_near_opt > 0)
		{
			ft_error(5, h->line);
			return (ft_kill_str_dop_lex(tmp, NULL));
		}
		if (*h->line == '\0')
		{
			h = h->next;
			continue ;
		}
		if (do_all_zams_with_inhibitor(h, &h, tmp) == -1)
			return (NULL);
	}
	return (ft_kill_str_dop_lex(tmp, htmp));
}
