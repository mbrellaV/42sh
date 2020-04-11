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
	char		*tmp;
	t_lextoken	*lextmp;
	t_lextoken	*lextmp1;

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

int				check_if_in_par(char *line, int i)
{
	int			d;
	int			marker;

	d = i;
	marker = 0;
	while (d > -1 && line[d])
	{
		if (ispar(line[d]))
			marker++;
		d--;
	}
	d = i;
	while (line[d])
	{
		if (ispar(line[d]))
			marker++;
		d++;
	}
	if (marker == 2)
		return (1);
	return (0);
}

void			change_enters_in_sc(char *line)
{
	int			i;

	i = 0;
	while (line[i] != '\0')
	{
		if (issc(line[i]) && !check_if_in_par(line, i))
			line[i] = ' ';
		i++;
	}
}

t_lextoken		*zam_ravno_h(t_lextoken *h, t_lextoken **htmp)
{
	char		*tmp1;
	char		*tmp2;
	t_lextoken	*dop;

	tmp1 = ft_strsub(h->line, 0, ft_strstr(h->line, "=") - h->line);
	tmp2 = ft_strsub(h->line, ft_strstr(h->line, "=") -
	h->line + 1, ft_strlen(h->line));
	set_new_var(tmp1, tmp2, &g_all_var);
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
	dop = h->next;
	if (h->prev)
		h->prev->next = h->next;
	if (h->next)
	{
		h->next->prev = h->prev;
		*htmp = h->next;
	}
	if (h->next == NULL && h->prev == NULL)
		*htmp = NULL;
	ft_strdel(&h->line);
	free(h);
	return (dop);
}

t_lextoken		*do_zam_ravno(t_lextoken *h, t_lextoken **htmp)
{
	char		*tmp1;
	char		*tmp2;
	t_lextoken	*dop;

	if (h != NULL && h->line && ft_strstr(h->line, "=") && ((!h->next
	|| is_cmd_delim(get_op_type(h->next->line))) && h->prev == NULL))
		return (zam_ravno_h(h, htmp));
	else if (h != NULL && h->line != NULL && ft_strstr(h->line, "=")
	&& h->prev == NULL)
	{
		dop = h->next;
		if (h->prev)
			h->prev->next = h->next;
		if (h->next)
		{
			h->next->prev = h->prev;
			*htmp = h->next;
		}
		if (h->next == NULL && h->prev == NULL)
			*htmp = NULL;
		ft_strdel(&h->line);
		free(h);
		return (dop);
	}
	return (h);
}
