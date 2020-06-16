/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:53:40 by mbrella           #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int					dop_lexer(t_dop_str *tmp, char *line)
{
	if (isword(line[tmp->i_c]) > 0)
	{
		if (dop_lexer1(tmp, line) == -1)
			return (-1);
	}
	else if (isoperator(line[tmp->i_c]))
	{
		if (dop_lexer2(tmp, line) == -1)
			return (-1);
	}
	else
		tmp->i_c++;
	if (tmp->dop_c == 0 && tmp->tail_c != NULL)
	{
		tmp->doptail_c = tmp->tail_c;
		tmp->dop_c = 1;
	}
	return (0);
}

static t_lextoken	*lexer_error(t_dop_str *tmp)
{
	put_error_to_shell(2);
	if (tmp->doptail_c == NULL)
		ft_distr_lex(tmp->tail_c);
	ft_distr_lex(tmp->doptail_c);
	ft_kill_str_dop_lex(tmp, NULL);
	return (NULL);
}

t_lextoken			*do_lexer(char *line)
{
	t_dop_str	*tmp;

	if (!(tmp = cr_dop_str(&line)))
		return (NULL);
	if (line == NULL)
		return (NULL);
	while (line[tmp->i_c] != '\0')
	{
		if (dop_lexer(tmp, line) == -1)
			lexer_error(tmp);
	}
	if (tmp->tail_c != NULL && (tmp->tail_c->operator_type == 2 ||
	tmp->tail_c->operator_type == 10 || tmp->tail_c->operator_type == 11))
	{
		ft_distr_lex(tmp->doptail_c);
		ft_kill_str_dop_lex(tmp, tmp->doptail_c);
		return (ft_error(5, "\\n", NULL) == -1 ? NULL : 0);
	}
	tmp->tail_c = tmp->doptail_c;
	return (ft_kill_str_dop_lex(tmp, tmp->doptail_c));
}
