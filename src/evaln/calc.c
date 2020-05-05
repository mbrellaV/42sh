/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_request.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:25:00 by mbrella           #+#    #+#             */
/*   Updated: 2020/05/02 13:20:10 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval_expr.h"

static void	calc_next(int *stackos, t_int *str, int c)
{
	if ((c - 300) == ('!' + '='))
		stackos[str->ol - 2] = stackos[str->ol - 2] != stackos[str->ol - 1];
	else if ((c - 300) == ('=' + '='))
		stackos[str->ol - 2] = stackos[str->ol - 2] == stackos[str->ol - 1];
	else if ((c - 300) == ('>' + '='))
		stackos[str->ol - 2] = stackos[str->ol - 2] >= stackos[str->ol - 1];
	else if ((c - 300) == ('<' + '='))
		stackos[str->ol - 2] = stackos[str->ol - 2] <= stackos[str->ol - 1];
	else if ((c - 300) == ('&' + '&'))
		stackos[str->ol - 2] = stackos[str->ol - 2] && stackos[str->ol - 1];
	else if ((c - 300) == ('|' + '|'))
		stackos[str->ol - 2] = stackos[str->ol - 2] || stackos[str->ol - 1];
	subos(stackos, str);
}

void		make_request(int *stackos, t_int *str, int c)
{
	if ((c - 300) == '-')
		stackos[str->ol - 2] = stackos[str->ol - 2] - stackos[str->ol - 1];
	else if ((c - 300) == '+')
		stackos[str->ol - 2] = stackos[str->ol - 2] + stackos[str->ol - 1];
	else if ((c - 300) == '*')
		stackos[str->ol - 2] = stackos[str->ol - 2] * stackos[str->ol - 1];
	else if ((c - 300) == '/')
		stackos[str->ol - 2] = stackos[str->ol - 2] / stackos[str->ol - 1];
	else if ((c - 300) == '%')
		stackos[str->ol - 2] = stackos[str->ol - 2] % stackos[str->ol - 1];
	else if ((c - 300) == '>')
		stackos[str->ol - 2] = stackos[str->ol - 2] > stackos[str->ol - 1];
	else if ((c - 300) == '<')
		stackos[str->ol - 2] = stackos[str->ol - 2] < stackos[str->ol - 1];
	calc_next(stackos, str, c);
}
