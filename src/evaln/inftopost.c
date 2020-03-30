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

int		opr_znak(char **dstr)
{
	int		i;
	char	*newstr;
	int		sum;
	char	*str;

	i = 0;
	str = *dstr;
	sum = 300;
	while (str[i] != '\0' && is_znak(str[i]))
		i++;
	newstr = ft_strsub(str, 0, i);
	i = 0;
	while (newstr[i])
	{
		sum += newstr[i];
		(*dstr)++;
		i++;
	}
	ft_strdel(&newstr);
	return (sum);
}

int		eval_expr(char *str)
{
	int		*stackos;
	int		*stackzn;
	t_int	*l;
	char	**strp;

	l = cr_new_el();
	if (!(stackos = (int*)ft_memalloc(4 * ft_strlen(str))))
		return (-1);
	if (!(stackzn = (int*)ft_memalloc(4 * ft_strlen(str))))
		return (-1);
	strp = &str;
	while (*str != '\0')
	{
		if ((*str >= '0' && *str <= '9') || ((*str == '-' || *str == '+') &&
			(*(str + 1) >= '0' && *(str + 1) <= '9') && l->i == 1))
		{
			addos(stackos, ft_atoi_with(strp), l);
			l->i = 0;
		}
		if ((is_znak(*str) && l->i == 0) || (*str == '(' || *str == ')'))
			dostack(stackos, stackzn, opr_znak(&str), l);
		str++;
	}
	calcend(&stackos, &stackzn, &l);
	return (stackos[0]);
}

