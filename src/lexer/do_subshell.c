/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_subshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:44:42 by mbrella           #+#    #+#             */
/*   Updated: 2020/01/27 13:44:42 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

int					dop_subshell(char *str, t_memory *head)
{
	int		i;
	char	*newstr;

	i = 0;
	newstr = NULL;
	if (!ft_strstr(str, "("))
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '(')
		{
			newstr = ft_strsub(str, i + 1, sc_size(str, '(') - i - 3);
			break ;
		}
		i++;
	}
	if (newstr != NULL)
	{
		do_cmd(newstr, head);
		return (1);
	}
	else
		return (-1);
}

int					do_work_subshell(char **mas, t_memory *head)
{
	int		i;

	i = dop_subshell(mas[0], head);
	if (i == 0)
		return (0);
	else if (i == -1)
		return (-1);
	if (mas[1] != NULL)
		return (-1);
	return (1);
}
