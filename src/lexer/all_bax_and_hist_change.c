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
		}
    	else
    		h = h->next;
	}
	return (lextmp1);
}

void        del_one_node(char **str, int node_to_del)
{
    int i;
    int tmp;

    i = 0;
    tmp = 0;
    while (str[i])
    {
        if (node_to_del == i)
            tmp = 1;
        if (tmp)
            str[i] = str[i + 1];
        i++;
    }
}

void        do_zam_ravno(t_exectoken *h)
{
    char		*tmp1;
    char		*tmp2;

    if (h != NULL && h->file_args != NULL && ft_strstr(h->file_args[0], "="))
    {
        tmp1 = ft_strsub(h->file_args[0], 0, ft_strstr(h->file_args[0], "=") - h->file_args[0]);
        tmp2 = ft_strsub(h->file_args[0], ft_strstr(h->file_args[0], "=") - h->file_args[0] + 1, ft_strlen(h->file_args[0]));
        set_new_var(tmp1, tmp2, &g_all_var);
        del_one_node(h->file_args, 0);
        do_zam_ravno(h->right);
        do_zam_ravno(h->left);
    }
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
			//h->line = do_zam_str_bax(h->line, tmp);
			//h->line = do_obr_zamena_bax(h->line);
			//h->line = ft_do_zam_eval(h->line);
		}
		if (h->inhibitor_lvl == 0)
			h->line = ft_do_zam_alias(h->line);
		h = h->next;
	}
    h = do_zam_join_par(htmp);
	ft_kill_str_dop_lex(tmp, NULL);
	return (h);
}
