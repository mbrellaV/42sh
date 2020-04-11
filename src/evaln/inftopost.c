/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inftopost.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:26:44 by mbrella           #+#    #+#             */
/*   Updated: 2019/08/18 19:44:30 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval_expr.h"

void		calc_2(int *stackos, t_int *str, int c)
{
	if ((c - 300) == ('!' + '='))
		stackos[str->osl - 2] = stackos[str->osl - 2] !=
										stackos[str->osl - 1];
	if ((c - 300) == ('=' + '='))
		stackos[str->osl - 2] = stackos[str->osl - 2] ==
										stackos[str->osl - 1];
	if ((c - 300) == ('>' + '='))
		stackos[str->osl - 2] = stackos[str->osl - 2] >=
										stackos[str->osl - 1];
	if ((c - 300) == ('<' + '='))
		stackos[str->osl - 2] = stackos[str->osl - 2] <=
										stackos[str->osl - 1];
	if ((c - 300) == ('&' + '&'))
		stackos[str->osl - 2] = stackos[str->osl - 2] &&
										stackos[str->osl - 1];
	if ((c - 300) == ('|' + '|'))
		stackos[str->osl - 2] = stackos[str->osl - 2] ||
										stackos[str->osl - 1];
	subos(stackos, str);
}

int			opr_znak(char *dstr, int *marker)
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

int			eval_expr(char *str)
{
	int		*stackos;
	int		*stackzn;
	t_int	*l;
	int		i;

	i = 0;
	l = cr_new_el();
	if (!(stackos = (int*)ft_memalloc(4 * ft_strlen(str))) ||
			(!(stackzn = (int*)ft_memalloc(4 * ft_strlen(str)))))
		return (-1);
	while (i < ft_strlen(str) && str[i] != '\0')
	{
		if ((str[i] >= '0' && str[i] <= '9') || ((str[i] == '-' ||
		str[i] == '+') && str[i + 1] != '\0' && (str[i + 1] >= '0'
		&& str[i + 1] <= '9') && l->i == 1))
		{
			addos(stackos, ft_atoi_with(str + i, &i), l);
			l->i = 0;
		}
		if ((is_znak(str[i]) && l->i == 0) || (str[i] == '(' || str[i] == ')'))
			dostack(stackos, stackzn, opr_znak(str, &i), l);
		else
			i++;
	}
	return (calcend(&stackos, &stackzn, &l));
}

char		*calc_check(char *newstr, int i)
{
	if (i == 0)
	{
		ft_strdel(&newstr);
		return (NULL);
	}
	return (newstr);
}
