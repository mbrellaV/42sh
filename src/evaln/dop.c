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

t_int		*cr_new_el(char *s, int *error)
{
	t_int	*tmp;

	if (!(tmp = ft_memalloc(sizeof(t_int))))
		return (NULL);
	tmp = tmp_0(tmp, s);
	if (!(tmp->s = change_vars(s)))
	{
		*error = 1;
		ft_strdel(&tmp->s);
		free(tmp);
		return (NULL);
	}
	if (!check_calc_sc(tmp->s))
	{
		*error = 1;
		ft_strdel(&tmp->s);
		free(tmp);
		return (NULL);
	}
	if (!(tmp->stackos = (int*)ft_memalloc(4 * ft_strlen(tmp->s))))
		return (NULL);
	if (!(tmp->stackzn = (int*)ft_memalloc(4 * ft_strlen(tmp->s))))
		return (NULL);
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
		lastint->d = 1;
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
