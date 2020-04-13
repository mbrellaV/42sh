/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:25:00 by mbrella           #+#    #+#             */
/*   Updated: 2020/04/13 20:04:23 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval_expr.h"

static void	calc_next(int *stackos, t_int *str, int c)
{
	if ((c - 300) == ('!' + '='))
		stackos[str->stackoslast - 2] = stackos[str->stackoslast - 2] !=
										stackos[str->stackoslast - 1];
	if ((c - 300) == ('=' + '='))
		stackos[str->stackoslast - 2] = stackos[str->stackoslast - 2] ==
										stackos[str->stackoslast - 1];
	if ((c - 300) == ('>' + '='))
		stackos[str->stackoslast - 2] = stackos[str->stackoslast - 2] >=
										stackos[str->stackoslast - 1];
	if ((c - 300) == ('<' + '='))
		stackos[str->stackoslast - 2] = stackos[str->stackoslast - 2] <=
										stackos[str->stackoslast - 1];
	if ((c - 300) == ('&' + '&'))
		stackos[str->stackoslast - 2] = stackos[str->stackoslast - 2] &&
										stackos[str->stackoslast - 1];
	if ((c - 300) == ('|' + '|'))
		stackos[str->stackoslast - 2] = stackos[str->stackoslast - 2] ||
										stackos[str->stackoslast - 1];
	subos(stackos, str);
}

void		calc(int *stackos, t_int *str, int c)
{
	if ((c - 300) == '-')
		stackos[str->stackoslast - 2] = stackos[str->stackoslast - 2] -
				stackos[str->stackoslast - 1];
	if ((c - 300) == '+')
		stackos[str->stackoslast - 2] = stackos[str->stackoslast - 2] +
				stackos[str->stackoslast - 1];
	if ((c - 300) == '*')
		stackos[str->stackoslast - 2] = stackos[str->stackoslast - 2] *
				stackos[str->stackoslast - 1];
	if ((c - 300) == '/')
		stackos[str->stackoslast - 2] = stackos[str->stackoslast - 2] /
				stackos[str->stackoslast - 1];
	if ((c - 300) == '%')
		stackos[str->stackoslast - 2] = stackos[str->stackoslast - 2] %
				stackos[str->stackoslast - 1];
	if ((c - 300) == '>')
		stackos[str->stackoslast - 2] = stackos[str->stackoslast - 2] >
				stackos[str->stackoslast - 1];
	if ((c - 300) == '<')
		stackos[str->stackoslast - 2] = stackos[str->stackoslast - 2] <
				stackos[str->stackoslast - 1];
	calc_next(stackos, str, c);
}
