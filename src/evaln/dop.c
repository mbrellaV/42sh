/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 14:33:38 by mbrella           #+#    #+#             */
/*   Updated: 2019/08/18 20:35:15 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval_expr.h"

t_int	*cr_new_el(void)
{
	t_int	*tmp;

	if (!(tmp = malloc(sizeof(t_int))))
		return (NULL);
	tmp->stackoslast = 0;
	tmp->stackznlast = 0;
	tmp->i = 1;
	return (tmp);
}

int		prior(int c)
{
	if ((c - 300) == '*')
		return (2);
	else if ((c - 300) == '/')
		return (2);
	else if ((c - 300) == '%')
		return (2);
	else if (c > 300 && c < 800)
		return (1);
	else
		return (0);
}

int		is_znak(int c)
{
	if (c == '-' || c == '+' || c == '<' || c == '>' || c == '=' ||
	c == '&' || c == '|' || c == '*' || c == '/' || c == '%' || (c >= 300 && c < 800))
		return (1);
	else
		return (0);
}

void	dostack(int *stackos, int *stackzn, int c, t_int *lastint)
{
	if ((c - 300) == '(')
		addzn(stackzn, c, lastint);
	else if ((c - 300) == ')')
	{
		while (stackzn[lastint->stackznlast - 1] != ('(' + 300))
		{
			calc(stackos, lastint, stackzn[lastint->stackznlast - 1]);
			subzn(stackzn, lastint);
		}
		subzn(stackzn, lastint);
	}
	else if (prior(stackzn[lastint->stackznlast - 1]) < prior(c))
		addzn(stackzn, c, lastint);
	else
	{
		while (prior(stackzn[lastint->stackznlast - 1]) >= prior(c))
		{
			calc(stackos, lastint, stackzn[lastint->stackznlast - 1]);
			subzn(stackzn, lastint);
		}
		addzn(stackzn, c, lastint);
	}
	if (is_znak(c))
		lastint->i = 1;
}

int		calcend(int **stackos, int **stackzn, t_int **str)
{
	int		result;


	while ((*str)->stackoslast > 1)
	{
		calc(*stackos, *str, *stackzn[(*str)->stackznlast - 1]);
		subzn(*stackzn, *str);
	}
	result = *stackos[0];
	free(*stackos);
	free(*stackzn);
	free(*str);
	return (result);
}
