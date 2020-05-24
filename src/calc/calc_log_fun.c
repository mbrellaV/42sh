/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_log_fun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:53:08 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/12 23:00:09 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

int					is_incr_sym(char c)
{
	return (c == '+' || c == '-');
}

static long long	calc_log_or(long long result, t_calc_tokens *s_tokens,
		size_t *index, t_calc_err *error)
{
	long long		next_result;

	next_result = calc_parent(s_tokens, index, error);
	if (error->status)
		return (0);
	return (result || next_result);
}

static long long	calc_log_next(long long result, t_calc_tokens *s_tokens,
		size_t *index, t_calc_err *error)
{
	t_calc_tkntype	oper;

	while (1)
	{
		oper = s_tokens->tokens[*index].type;
		if (oper == CALC_AND || oper == CALC_OR)
			(*index)++;
		if (oper == CALC_AND)
			result = result && calc_parent(s_tokens, index, error);
		else if (oper == CALC_OR)
			result = calc_log_or(result, s_tokens, index, error);
		else
			break ;
		if (error->status)
			return (0);
	}
	return (result);
}

t_calc_tkn			*calc_get_log_tkn(char *str, size_t pos)
{
	t_calc_tkn		*token;
	t_calc_tkntype	type;

	if (!str)
		return (NULL);
	type = (*str == '&') ? CALC_AND : CALC_OR;
	if (!(token = calc_newtkn(NULL, type)))
		return (NULL);
	token->start_pos = pos;
	token->end_pos = pos + 2;
	return (token);
}

long long			calc_log(t_calc_tokens *s_tokens, size_t *index,
		t_calc_err *error)
{
	long long		result;

	if (!s_tokens || !calc_check_index(s_tokens, *index))
		return (calc_error(error, CALC_ERR_NULL_OR_IND));
	result = calc_parent(s_tokens, index, error);
	if (error->status)
		return (0);
	result = calc_log_next(result, s_tokens, index, error);
	return (result);
}
