/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:39:43 by qmartina          #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_add_tab(t_readline *p, char *str)
{
	int		i;

	i = 0;
	while (p->tab[i] != NULL)
	{
		if (ft_strcmp(str, p->tab[i]) == 0)
			return ;
		i++;
	}
	if (p->tab_max == p->tab_size)
		ft_realloc_tab(p);
	p->tab[p->tab_max++] = ft_strdup(str);
}

int		is_add_str_tab(t_readline *p)
{
	int		i;
	int		k;

	k = 0;
	if (p->tab_max == 1)
		return (-100);
	while (p->tab[0] && p->tab[0][k])
	{
		i = 0;
		while (i < p->tab_max && p->tab[0][k] &&
		p->tab[i][k] && p->tab[0][k] == p->tab[i][k])
			i++;
		if (i != p->tab_max)
			return (k);
		else
			k++;
	}
	return (k);
}

void	dop_to_check_tab(t_readline *p, char **str, int *i)
{
	p->flag_tab = 1;
	p->flag_left_word = 0;
	while (p->index < p->len && isword(p->buff[p->index]) == 1)
	{
		tputs(tgetstr("nd", NULL), 1, ft_c);
		p->index++;
	}
	*i = p->index;
	while (--(*i) > 0 && (isword(p->buff[*i]) == 1 ||
	p->buff[*i] == '{' || p->buff[*i] == '$'))
		;
	p->i_dop = *i;
	while (--(p->i_dop) > 0 && isword(p->buff[p->i_dop]) != 1)
		;
	if (p->i_dop > 0)
		p->flag_left_word = 1;
	if (*i != 0)
		(*i)++;
	*str = ft_strndup(&(p->buff[*i]), p->index - *i);
	p->tab_max = 0;
}

void	dop_to_check_tab_delete(t_readline *p,
		char **name, char **str, char **dir)
{
	ft_arrdel(p->tab);
	p->tab_size = 8;
	p->tab = ft_arrnew(p->tab_size);
	p->tab_i = 0;
	free(*name);
	free(*str);
	free(*dir);
}
