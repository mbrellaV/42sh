/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_and_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:49:02 by wstygg            #+#    #+#             */
/*   Updated: 2020/04/13 19:49:02 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval_expr.h"

void	addos(int *stackos, int c, t_int *lastint)
{
	stackos[lastint->ol] = c;
	(lastint->ol)++;
}

void	subos(int *stackos, t_int *lastint)
{
	stackos[lastint->ol - 1] = 0;
	(lastint->ol)--;
}

void	addzn(int *stackzn, int c, t_int *lastint)
{
	stackzn[lastint->zl] = c;
	(lastint->zl)++;
}

void	subzn(int *stackzn, t_int *lastint)
{
	stackzn[lastint->zl - 1] = 0;
	(lastint->zl)--;
}
