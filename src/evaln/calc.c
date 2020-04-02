/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:25:00 by mbrella           #+#    #+#             */
/*   Updated: 2019/08/18 17:28:31 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval_expr.h"

void	calc(int *stackos, t_int *str, int c)
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

void	addos(int *stackos, int c, t_int *lastint)
{
	int i = 0;
	while (stackos[i])
	{
		dprintf(2, "dadadda: |%d|\n", stackos[i]);
		i++;
	}
	dprintf(2, "plus1: |%d|\n", c);
	stackos[lastint->stackoslast] = c;
	(lastint->stackoslast)++;
}

void	subos(int *stackos, t_int *lastint)
{
	int i = 0;
	while (stackos[i])
	{
		dprintf(2, "dadadda: |%d|\n", stackos[i]);
		i++;
	}
	dprintf(2, "drop2: |%d|\n", stackos[lastint->stackoslast - 1]);
	stackos[lastint->stackoslast - 1] = 0;
	(lastint->stackoslast)--;
}

void	addzn(int *stackzn, int c, t_int *lastint)
{
	int i = 0;
	while (stackzn[i])
	{
		dprintf(2, "dadadda: |%d|\n", stackzn[i]);
		i++;
	}
	dprintf(2, "drop3: |%d|\n", c);
	stackzn[lastint->stackznlast] = c;
	(lastint->stackznlast)++;
}

void	subzn(int *stackzn, t_int *lastint)
{
	int i = 0;
	while (stackzn[i])
	{
		dprintf(2, "dadadda: |%d|\n", stackzn[i]);
		i++;
	}
	dprintf(2, "drop4: |%d|\n", stackzn[lastint->stackznlast - 1]);
	stackzn[lastint->stackznlast - 1] = 0;
	(lastint->stackznlast)--;
}
