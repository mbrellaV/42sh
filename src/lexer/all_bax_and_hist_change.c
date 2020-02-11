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

			tmp = h->line;
			h->next->line = ft_strjoin(h->line, h->next->line);
			ft_strdel(&tmp);
			lextmp = h;
			h = h->next;
			lextmp1 = h;
			free(lextmp);
			h->is_near_word = 0;
			h->inhibitor_lvl = 0;
			//dprintf(2, "\nsas: |%s|\n", h->line);
		}
    	else
    		h = h->next;
	}
  //  dprintf(2, "\ndopsas: |%p|, |%s|\n", lextmp1->next, lextmp1->line);
	return (lextmp1);
}

t_lextoken		*do_zam_ravno(t_lextoken *h)
{
    t_lextoken  *lextmp1;
    char		*tmp1;
    char		*tmp2;

    lextmp1 = h;
    while (h)
    {
        if (ft_strstr(h->line, "="))
        {
        	dprintf(2, "sas1");
        	tmp1 = ft_strsub(h->line, 0, ft_strstr(h->line, "=") - h->line);
			dprintf(2, "sas2");
        	tmp2 = ft_strsub(h->line, ft_strstr(h->line, "=") - h->line + 1, ft_strlen(h->line));
			dprintf(2, "sas3");
        	set_new_var(tmp1, tmp2, &g_all_var);
			dprintf(2, "sas4");
            lextmp1 = h->next;
            ft_strdel(&h->line);
            free(h);
            h = lextmp1;
        }
        else
        	h = h->next;
    }
    return (lextmp1);
}

t_lextoken		*do_zam_bax_and_hist_full(t_lextoken *h)
{
	t_dop_str	*tmp;
	t_lextoken  *htmp;

	if (!h)
		return (NULL);
	htmp = h;
	if (!(tmp = ft_memalloc(sizeof(t_dop_str))))
		ft_error_q(2);
	while (h != NULL)
	{
		tmp->c_b = 0;
		tmp->i_b = -1;
		tmp->str_b = h->line;
		if (h->inhibitor_lvl != 2)
		{
			h->line = do_zamena_sp(h->line);
			h->line = do_zam_str_bax(h->line, tmp);
			h->line = do_obr_zamena_bax(h->line);
		}
		if (h->inhibitor_lvl == 0)
			h->line = ft_do_zam_alias(h->line);
		h = h->next;
	}
    h = do_zam_join_par(htmp);
	h = do_zam_ravno(h);
	//dprintf(2, "\n|%p|\n", h);
	ft_kill_str_dop_lex(tmp, NULL);
	return (h);
}
