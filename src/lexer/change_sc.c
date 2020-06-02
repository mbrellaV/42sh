/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_sc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 13:38:58 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/12 22:36:30 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

//int			check_if_in_par(char *line, int i)
//{
//	int		d;
//	int		marker;
//
//	d = i;
//	marker = 0;
//	while (d > -1 && line[d])
//	{
//		if (ispar(line[d]))
//		{
//			marker++;
//			break ;
//		}
//		d--;
//	}
//	d = i;
//	while (line[d])
//	{
//		if (ispar(line[d]))
//		{
//			marker++;
//			break ;
//		}
//		d++;
//	}
//	if (marker == 2)
//		return (1);
//	return (0);
//}

void		ft_change_all_sc(char *str)
{
	int		i;
	int		size;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && (str[i + 1] == '(' || str[i + 1] == '{'))
			i += word_size(&str[i]);
		if ((str[i] == '(' || str[i] == ')'))
			str[i] = ' ';
		if (ispar(str[i]))
		{
			size = c_size(&str[i], str[i]);
			if (size == -2)
				size = 2;
			if (size == -1)
				size = 1;
			i += size;
		}
		i++;
	}
}
