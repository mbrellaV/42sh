/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_sc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 13:38:58 by wstygg            #+#    #+#             */
/*   Updated: 2020/06/03 20:13:49 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

void		ft_change_all_sc(char *str)
{
	int		i;
	int		size;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && (str[i + 1] == '(' || str[i + 1] == '{'))
			i += word_size(&str[i]);
		else if ((str[i] == '(' || str[i] == ')'))
			str[i] = ' ';
		else if (ispar(str[i]))
		{
			size = c_size(&str[i], str[i]);
			if (size == -2)
				size = 2;
			if (size == -1)
				size = 1;
			i += size;
		}
		else
			i++;
	}
}
