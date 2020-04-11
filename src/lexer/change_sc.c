/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_sc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 11:45:44 by plettie           #+#    #+#             */
/*   Updated: 2020/02/06 11:45:52 by plettie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int				dop_lexer2(t_dop_str *tmp, char *line)
{
	if (tmp->tail_c && tmp->tail_c->prev &&
		ft_str_is_numeric(tmp->tail_c->prev->line) && (line[tmp->i_c + 1] == '>'
		|| line[tmp->i_c + 1] == '<') && tmp->tail_c->prev->inhibitor_lvl == 0)
		tmp->tail_c->prev->is_near_opt = 1;
	tmp->tmp_c = ft_strsub(line, tmp->i_c, word_size(line + tmp->i_c));
	if (tmp->tail_c && needs_something_before(tmp->tail_c->operator_type) &&
		get_op_type(tmp->tmp_c) == 2)
		return (ft_error(5, tmp->tmp_c));
	if (tmp->i_c != 0 &&
		isword(line[tmp->i_c - 1]) == 1 && (get_op_type(tmp->tmp_c) > 6 &&
											get_op_type(tmp->tmp_c) < 8))
		tmp->tail_c->is_near_opt = 1;
	tmp->tail_c = add_token(tmp->tail_c, tmp->tmp_c, 0);
	tmp->tail_c->is_near_opt = 1;
	if (tmp->tail_c && get_op_type(tmp->tmp_c) == -1)
		return (ft_error(5, tmp->tail_c->line));
	if (needs_something_before(tmp->tail_c->operator_type) &&
		tmp->tail_c->prev == NULL)
		return (ft_error(5, tmp->tail_c->line));
	tmp->i_c += word_size(line + tmp->i_c);
	return (0);
}

void			ft_change_all_sc(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '(' || str[i] == ')')
			str[i] = ' ';
		i++;
	}
}
