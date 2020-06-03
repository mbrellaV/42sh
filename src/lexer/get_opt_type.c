/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:45:34 by mbrella           #+#    #+#             */
/*   Updated: 2020/06/03 20:13:49 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int				get_op_type(char *operator)
{
	int			i;
	static char	operators[12][5] = {";;", ";", "|",\
		"<<", "<", ">>", ">", ">&", "<&", "&", "&&", "||"};

	i = 0;
	if (operator == NULL)
		return (-2);
	if (operator && (ft_strstr(operator, operators[i]) ||
	ft_strstr(operator, "<>") != NULL || ft_strstr(operator, "<<-") != NULL
	|| ft_strstr(operator, "<<<") != NULL || ft_strstr(operator, "|||") != NULL
	|| ft_strstr(operator, ">|") != NULL || ft_strstr(operator, ">>>") != NULL
	|| ft_strstr(operator, "&&&") != NULL))
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
