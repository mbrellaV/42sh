/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_zamena.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 09:38:59 by qmartina          #+#    #+#             */
/*   Updated: 2019/11/15 16:17:33 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

char			*do_reverse_zamena(char *str)
{
	int			i;
	char		*newstr;
	char		*tmp;

	i = 0;
	if (!(newstr = ft_memalloc(ft_strlen(str) * 2 + 1)))
		ft_error_q(15);
	while (str[i] != '\0')
	{
		if (str[i] < 0)
		{
			tmp = ft_strdup("\\ ");
			tmp[1] = -1 * str[i];
		}
		else
		{
			tmp = ft_strdup(" ");
			tmp[0] = str[i];
		}
		ft_strcat(newstr, tmp);
		ft_strdel(&tmp);
		i++;
	}
	ft_strdel(&str);
	return (newstr);
}
