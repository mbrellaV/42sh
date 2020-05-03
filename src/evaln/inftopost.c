/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inftopost.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:26:44 by mbrella           #+#    #+#             */
/*   Updated: 2020/05/02 13:20:11 by wstygg           ###   ########.fr       */
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
	if (issc(str[i]))
	{
		sum += str[i];
		(*marker)++;
		return (sum);
	}
	while (str[i] && (is_znak(str[i]) || issc(str[i])))
	{
		sum += str[i];
		(*marker)++;
		i++;
	}
	return (sum);
}

t_int	*eval_help(t_int *l)
{
	if ((is_znak(l->s[l->i]) && (l->last_token++) && l->d == 0) ||
		(l->s[l->i] == '(' || l->s[l->i] == ')'))
		dostack(l->stackos, l->stackzn, opr_znak(l->s, &l->i), l);
	else
		l->i++;
	return (l);
}

int		eval_expr(char *s, int *error)
{
	t_int	*l;

	if (!(l = cr_new_el(s, error)))
		return (calc_error(NULL, NULL, NULL, error, NULL));
	while (l->i < (int)ft_strlen(l->s) && l->s[l->i] != '\0')
	{
		if (check_calc_str(&l->s[l->i]) == -1)
			return (calc_error(l->stackos, l->stackzn, l, error, l->s));
		if ((l->s[l->i] >= '0' && l->s[l->i] <= '9') ||
		((l->s[l->i] == '-' || l->s[l->i] == '+') && l->s[l->i + 1] != '\0' &&
		(l->s[l->i + 1] >= '0' && l->s[l->i + 1] <= '9') && l->d == 1))
		{
			if (l->last_token == 1)
				return (calc_error(l->stackos, l->stackzn, l, error, l->s));
			l->last_token = 1;
			addos(l->stackos, ft_atoi_with(l->s + l->i, &l->i), l);
			l->d = 0;
		}
		l = eval_help(l);
		if (l->last_token >= 3)
			return (calc_error(l->stackos, l->stackzn, l, error, l->s));
	}
	ft_strdel(&l->s);
	return (calcend(&l->stackos, &l->stackzn, &l));
}
