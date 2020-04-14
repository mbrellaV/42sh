/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inftopost.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:26:44 by mbrella           #+#    #+#             */
/*   Updated: 2020/04/14 11:37:41 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval_expr.h"

int		opr_znak(char *dstr, int *marker)
{
	int		i;
	int		sum;
	char	*str;

	i = *marker;
	str = dstr;
	sum = 300;
	while (str[i] && (is_znak(str[i]) || issc(str[i])))
	{
		sum += str[i];
		(*marker)++;
		i++;
	}
	return (sum);
}

int		eval_expr(char *s)
{
	int		*stackos;
	int		*stackzn;
	t_int	*l;
	int		i;

	i = 0;
	l = cr_new_el();
	if (!(stackos = (int*)ft_memalloc(4 * ft_strlen(s))))
		return (-1);
	if (!(stackzn = (int*)ft_memalloc(4 * ft_strlen(s))))
		return (-1);
	while (i < ft_strlen(s) && s[i] != '\0')
	{
		if ((s[i] >= '0' && s[i] <= '9') || ((s[i] == '-' || s[i] == '+') &&
		s[i + 1] != '\0' && (s[i + 1] >= '0' && s[i + 1] <= '9') && l->i == 1))
		{
			addos(stackos, ft_atoi_with(s + i, &i), l);
			l->i = 0;
		}
		if ((is_znak(s[i]) && l->i == 0) || (s[i] == '(' || s[i] == ')'))
			dostack(stackos, stackzn, opr_znak(s, &i), l);
		else
			i++;
	}
	return (calcend(&stackos, &stackzn, &l));
}
