#include "fshell.h"

int				dop_lexer2(t_dop_str *tmp, char *line)
{
	if (tmp->tail_c && tmp->tail_c->prev &&
		ft_str_is_numeric(tmp->tail_c->prev->line) && (line[tmp->i_c + 1] == '>' ||
													   line[tmp->i_c + 1] == '<') && tmp->tail_c->prev->inhibitor_lvl == 0)
		tmp->tail_c->prev->is_near_opt = 1;
	tmp->tmp_c = ft_strsub(line, tmp->i_c, word_size(line + tmp->i_c));
	if (tmp->tail_c && needs_something_before(tmp->tail_c->operator_type) &&
		is_cmd_delim(get_op_type(tmp->tmp_c)))
		return (ft_error(5, tmp->tmp_c, tmp->tmp_c));
	if (tmp->i_c != 0 &&
		isword(line[tmp->i_c - 1]) == 1 && ft_str_is_numeric(tmp->tail_c->line)
		&& (get_op_type(tmp->tmp_c) >= 3 && get_op_type(tmp->tmp_c) <= 8))
		tmp->tail_c->is_near_opt = 1;
	tmp->tail_c = add_token(tmp->tail_c, tmp->tmp_c);
	tmp->tail_c->is_near_opt = 1;
	if (tmp->tail_c && get_op_type(tmp->tmp_c) == -1)
		return (ft_error(5, tmp->tail_c->line, NULL));
	if (needs_something_before(tmp->tail_c->operator_type) &&
		tmp->tail_c->prev == NULL)
		return (ft_error(5, tmp->tail_c->line, NULL));
	tmp->i_c += word_size(line + tmp->i_c);
	return (0);
}

int		dop_dop_lexer1(int *plus_to_word, t_dop_str *tmp, char *line)
{
	if (tmp->tail_c != NULL && (tmp->tail_c->operator_type > 2 &&
								(tmp->tail_c->operator_type < 9)))
		tmp->d_c = 1;
	if (!(tmp->tail_c = add_token(tmp->tail_c, tmp->tmp_c)))
		return (-1);
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
		if (!(tmp->tail_c = add_token(tmp->tail_c, tmp->tmp_c)))
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
	return (dop_dop_lexer1(&plus_to_word, tmp, line));
}