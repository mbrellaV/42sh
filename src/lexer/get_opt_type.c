/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:45:34 by mbrella           #+#    #+#             */
/*   Updated: 2020/05/12 22:36:30 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

int				get_op_type(char *operator)
{
	int			i;
	static char	operators[12][5] = {";;", ";", "|",\
		"<<", "<", ">>", ">", ">&", "<&", "&", "&&", "||"};

	i = 0;
	if (ft_strstr(operator, operators[i]) || ft_strstr(operator, "<>") != NULL
	|| ft_strstr(operator, "<<-") != NULL || ft_strstr(operator, "<<<") != NULL
	|| ft_strstr(operator, "|||") != NULL || ft_strstr(operator, ">|") != NULL
	|| ft_strstr(operator, ">>>") != NULL || ft_strstr(operator, "&&&") != NULL)
		return (-1);
	i++;
	while (i < 12)
	{
		if (ft_strcmp(operator, operators[i]) == 0)
			return (i);
		i++;
	}
	return (-2);
}

int				needs_something_before(int n)
{
	return (n == 2 || n == 9 || n == 10 || n == 11);
}
