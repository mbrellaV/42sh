/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 14:33:38 by mbrella           #+#    #+#             */
/*   Updated: 2020/06/03 20:13:48 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval_expr.h"

t_int		*cr_new_el(char *s, int *error)
{
	t_int	*tmp;

	if (!(tmp = ft_memalloc(sizeof(t_int))))
		return (NULL);
	tmp = tmp_0(tmp, s);
	if (!(tmp->stackos = (int*)ft_memalloc(4 * ft_strlen(tmp->s))))
		return (NULL);
	if (!(tmp->stackzn = (int*)ft_memalloc(4 * ft_strlen(tmp->s))))
		return (NULL);
	return (tmp);
}

int			prior(int c)
{
	if (c == CALC_MUL)
		return (2);
	else if (c == CALC_DIV)
		return (2);
	else if (c == CALC_MOD)
		return (2);
	else if (c == CALC_FIR_SC || c == CALC_SEC_SC)
		return (0);
	else if (is_znak_type(c))
		return (1);
	else
		return (0);
}

int			is_znak(int c)
{
	if (c == '-' || c == '+' || c == '<' || c == '>' || c == '=' ||
	c == '&' || c == '|' || c == '*' || c == '/' || c == '%')
		return (1);
	else
		return (0);
}

int			calcend(int **stackos, int **stackzn, t_int **str, int *error)
{
	int		result;
	int		*dop_stackos;
	int		*dop_stackzn;

	dop_stackos = *stackos;
	dop_stackzn = *stackzn;
	while ((*str)->ol > 1)
	{
		if ((calc(dop_stackos, *str, dop_stackzn[(*str)->zl - 1],
				(*str)->s)) == -1)
			return (return_with_error(NULL, error, NULL, (*str)));
		subzn(dop_stackzn, *str);
	}
	if ((*str)->ol <= 0)
		result = 0;
	else
		result = dop_stackos[0];
	free_calc_tokens((*str)->first_token);
	free(dop_stackos);
	free(dop_stackzn);
	free(*str);
	return (result);
}
