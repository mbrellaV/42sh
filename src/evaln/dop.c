/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 14:33:38 by mbrella           #+#    #+#             */
/*   Updated: 2020/04/14 11:21:45 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval_expr.h"

t_int		*cr_new_el(void)
{
	t_int	*tmp;

	if (!(tmp = malloc(sizeof(t_int))))
		return (NULL);
	tmp->ol = 0;
	tmp->zl = 0;
	tmp->i = 1;
	return (tmp);
}

int			prior(int c)
{
	if ((c - 300) == '*')
		return (2);
	else if ((c - 300) == '/')
		return (2);
	else if ((c - 300) == '%')
		return (2);
	else if (issc((char)(c - 300)))
		return (0);
	else if (c > 300 && c < 800)
		return (1);
	else
		return (0);
}

int			is_znak(int c)
{
	if (c == '-' || c == '+' || c == '<' || c == '>' || c == '=' ||
	c == '&' || c == '|' || c == '*' || c == '/' || c == '%' ||
	(c >= 300 && c < 800))
		return (1);
	else
		return (0);
}

void		dostack(int *stackos, int *stackzn, int c, t_int *lastint)
{
	if ((c - 300) == '(')
		addzn(stackzn, c, lastint);
	else if ((c - 300) == ')')
	{
		while (stackzn[lastint->zl - 1] != ('(' + 300))
		{
			calc(stackos, lastint, stackzn[lastint->zl - 1]);
			subzn(stackzn, lastint);
		}
		subzn(stackzn, lastint);
	}
	else if (lastint->zl != 0 && prior(stackzn[lastint->zl - 1]) < prior(c))
		addzn(stackzn, c, lastint);
	else
	{
		while (lastint->zl > 0 && prior(stackzn[lastint->zl - 1]) >= prior(c))
		{
			calc(stackos, lastint, stackzn[lastint->zl - 1]);
			subzn(stackzn, lastint);
		}
		addzn(stackzn, c, lastint);
	}
	if (is_znak(c))
		lastint->i = 1;
}

int			calcend(int **stackos, int **stackzn, t_int **str)
{
	int		result;
	int		*dop_stackos;
	int		*dop_stackzn;

	dop_stackos = *stackos;
	dop_stackzn = *stackzn;
	while ((*str)->ol > 1)
	{
		calc(dop_stackos, *str, dop_stackzn[(*str)->zl - 1]);
		subzn(dop_stackzn, *str);
	}
	result = dop_stackos[0];
	free(dop_stackos);
	free(dop_stackzn);
	free(*str);
	return (result);
}
