/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:53:40 by mbrella           #+#    #+#             */
/*   Updated: 2020/04/20 14:49:46 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

int				dop_lexer2(t_dop_str *tmp, char *line)
{
	if (tmp->tail_c && tmp->tail_c->prev &&
	ft_str_is_numeric(tmp->tail_c->prev->line) && (line[tmp->i_c + 1] == '>' ||
	line[tmp->i_c + 1] == '<') && tmp->tail_c->prev->inhibitor_lvl == 0)
		tmp->tail_c->prev->is_near_opt = 1;
	tmp->tmp_c = ft_strsub(line, tmp->i_c, word_size(line + tmp->i_c));
	if (tmp->tail_c && needs_something_before(tmp->tail_c->operator_type) &&
	get_op_type(tmp->tmp_c) == 2)
		return (ft_error(5, tmp->tmp_c));
	if (tmp->i_c != 0 &&
		isword(line[tmp->i_c - 1]) == 1 && ft_str_is_numeric(tmp->tail_c->line)
		&& (get_op_type(tmp->tmp_c) >= 3 && get_op_type(tmp->tmp_c) <= 8))
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

static int		dop_dop_lexer1(int *plus_to_word, t_dop_str *tmp, char *line)
{
	if (ispar(line[(tmp)->i_c]) && (tmp)->i_c > 0 &&
			isword(line[(tmp)->i_c - 1]))
		(tmp)->tail_c->is_near_word = 1;
	if (isword(line[(tmp)->i_c]) && (tmp)->i_c > 0 &&
			ispar(line[(tmp)->i_c - 1]))
		(tmp)->tail_c->is_near_word = 1;
	if (isword(line[(tmp)->i_c]) && (tmp)->i_c > 0 &&
			isword(line[(tmp)->i_c - 1]))
		(tmp)->tail_c->is_near_word = 1;
	if (ispar(line[(tmp)->i_c]))
		(tmp)->tail_c->inhibitor_lvl = line[(tmp)->i_c] == '"' ? 1 : 2;
	(tmp)->tail_c->is_near_opt = (tmp)->d_c;
	if (*plus_to_word != 0)
		*plus_to_word += ispar(line[(tmp)->i_c]) == 1 ? 1 : -2;
	(tmp)->i_c += word_size(line + (tmp)->i_c) + (*plus_to_word);
	(tmp)->d_c = 0;
	return (0);
}

int				dop_lexer1(t_dop_str *tmp, char *line)
{
	int			plus_to_word;

	plus_to_word = (issc(line[tmp->i_c]) || ispar(line[tmp->i_c]));
	if (word_size(line + tmp->i_c) == -2)
	{
		tmp->tmp_c = ft_strdup("");
		if (!(tmp->tail_c = add_token(tmp->tail_c, tmp->tmp_c, 1)))
			return (-1);
		if (ispar(line[tmp->i_c]) && tmp->i_c > 0 && isword(line[tmp->i_c - 1]))
			tmp->tail_c->is_near_word = 1;
		if (isword(line[tmp->i_c]) && tmp->i_c > 0 && ispar(line[tmp->i_c - 1]))
			tmp->tail_c->is_near_word = 1;
		tmp->i_c += 2;
		return (0);
	}
	if (word_size(line + tmp->i_c) == -1)
		return (-1);
	tmp->tmp_c = ft_strsub(line, tmp->i_c + (plus_to_word),
		word_size(line + tmp->i_c) - (issc(line[tmp->i_c]) == 1 ? 3 : 0));
	if (tmp->tail_c != NULL && (tmp->tail_c->operator_type > 2 &&
		(tmp->tail_c->operator_type < 9)))
		tmp->d_c = 1;
	if (!(tmp->tail_c = add_token(tmp->tail_c, tmp->tmp_c, 1)))
		return (-1);
	return (dop_dop_lexer1(&plus_to_word, tmp, line));
}

int				dop_lexer(t_dop_str *tmp, char *line)
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

t_lextoken		*do_lexer(char *line)
{
	t_dop_str	*tmp;

	if (!(tmp = cr_dop_str(&line)))
		return (NULL);
	if (line == NULL)
		return (NULL);
	while (line[tmp->i_c] != '\0')
	{
		if (dop_lexer(tmp, line) == -1)
		{
			if (tmp->doptail_c == NULL)
				ft_distr_lex(tmp->tail_c);
			ft_distr_lex(tmp->doptail_c);
			ft_kill_str_dop_lex(tmp, NULL);
			return (NULL);
		}
	}
	if (tmp->tail_c != NULL && tmp->tail_c->operator_type == 2)
	{
		ft_kill_str_dop_lex(tmp, tmp->doptail_c);
		return (ft_error(5, "\\n") == -1 ? NULL : 0);
	}
	tmp->tail_c = tmp->doptail_c;
	return (ft_kill_str_dop_lex(tmp, tmp->doptail_c));
}
