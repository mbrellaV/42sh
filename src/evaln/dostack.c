/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 14:33:38 by mbrella           #+#    #+#             */
/*   Updated: 2020/05/02 13:20:10 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval_expr.h"

int			help_dos(int *stackos, int *stackzn, t_calc_token *c,
		t_int *lastint)
{
	while (lastint->zl > 0 &&
	prior(stackzn[lastint->zl - 1]) >= prior(c->type))
	{
		if ((calc(stackos, lastint,
				stackzn[lastint->zl - 1], c->var)) == -1)
			return (-1);
		subzn(stackzn, lastint);
	}
	addzn(stackzn, c->type, lastint);
	return (0);
}

int			dostack(int *stackos, int *stackzn, t_calc_token *c, t_int *lastint)
{
	if ((c->type == CALC_FIR_SC || (lastint->zl != 0 &&
	prior(stackzn[lastint->zl - 1])
	< prior(c->type))) && c->type != CALC_SEC_SC)
		addzn(stackzn, c->type, lastint);
	else if (c->type == CALC_SEC_SC)
	{
		while (stackzn[lastint->zl - 1] != CALC_FIR_SC)
		{
			if ((calc(stackos, lastint, stackzn[lastint->zl - 1],
					c->var)) == -1)
				return (-1);
			subzn(stackzn, lastint);
		}
		subzn(stackzn, lastint);
	}
	else if (help_dos(stackos, stackzn, c, lastint) == -1)
		return (-1);
	return (1);
}
