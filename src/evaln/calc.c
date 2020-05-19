/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:25:00 by mbrella           #+#    #+#             */
/*   Updated: 2020/05/02 13:20:10 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval_expr.h"

static void	calc_next(int *stackos, t_int *str, t_calc_tkntype c)
{
	if (c == CALC_DIFF)
		stackos[str->ol - 2] = stackos[str->ol - 2] != stackos[str->ol - 1];
	else if (c == CALC_EQ)
		stackos[str->ol - 2] = stackos[str->ol - 2] == stackos[str->ol - 1];
	else if (c == CALC_MOREOREQ)
		stackos[str->ol - 2] = stackos[str->ol - 2] >= stackos[str->ol - 1];
	else if (c == CALC_LESSOREQ)
		stackos[str->ol - 2] = stackos[str->ol - 2] <= stackos[str->ol - 1];
	else if (c == CALC_AND)
		stackos[str->ol - 2] = stackos[str->ol - 2] && stackos[str->ol - 1];
	else if (c == CALC_OR)
		stackos[str->ol - 2] = stackos[str->ol - 2] || stackos[str->ol - 1];
	subos(stackos, str);
}

void		calc(int *stackos, t_int *str, t_calc_tkntype c)
{
	if (c == CALC_MINUS)
		stackos[str->ol - 2] = stackos[str->ol - 2] - stackos[str->ol - 1];
	else if (c == CALC_PLUS)
		stackos[str->ol - 2] = stackos[str->ol - 2] + stackos[str->ol - 1];
	else if (c == CALC_MUL)
		stackos[str->ol - 2] = stackos[str->ol - 2] * stackos[str->ol - 1];
	else if (c == CALC_DIV)
		stackos[str->ol - 2] = stackos[str->ol - 2] / stackos[str->ol - 1];
	else if (c == CALC_MOD)
		stackos[str->ol - 2] = stackos[str->ol - 2] % stackos[str->ol - 1];
	else if (c == CALC_MORE)
		stackos[str->ol - 2] = stackos[str->ol - 2] > stackos[str->ol - 1];
	else if (c == CALC_LESS)
		stackos[str->ol - 2] = stackos[str->ol - 2] < stackos[str->ol - 1];
	calc_next(stackos, str, c);
}
