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
		stackos[str->osl - 2] = stackos[str->osl - 2] -
										stackos[str->osl - 1];
	if ((c - 300) == '+')
		stackos[str->osl - 2] = stackos[str->osl - 2] +
										stackos[str->osl - 1];
	if ((c - 300) == '*')
		stackos[str->osl - 2] = stackos[str->osl - 2] *
										stackos[str->osl - 1];
	if ((c - 300) == '/')
		stackos[str->osl - 2] = stackos[str->osl - 2] /
										stackos[str->osl - 1];
	if ((c - 300) == '%')
		stackos[str->osl - 2] = stackos[str->osl - 2] %
										stackos[str->osl - 1];
	if ((c - 300) == '>')
		stackos[str->osl - 2] = stackos[str->osl - 2] >
										stackos[str->osl - 1];
	if ((c - 300) == '<')
		stackos[str->osl - 2] = stackos[str->osl - 2] <
										stackos[str->osl - 1];
	calc_2(stackos, str, c);
}

void	addos(int *stackos, int c, t_int *lastint)
{
	stackos[lastint->osl] = c;
	(lastint->osl)++;
}

void	subos(int *stackos, t_int *lastint)
{
	stackos[lastint->osl - 1] = 0;
	(lastint->osl)--;
}

void	addzn(int *stackzn, int c, t_int *lastint)
{
	stackzn[lastint->znl] = c;
	(lastint->znl)++;
}

void	subzn(int *stackzn, t_int *lastint)
{
	stackzn[lastint->znl - 1] = 0;
	(lastint->znl)--;
}
