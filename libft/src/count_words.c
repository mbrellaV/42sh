/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 18:03:26 by qmartina          #+#    #+#             */
/*   Updated: 2020/06/03 20:13:49 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		count_words(char *str, char *delim)
{
	int		i;
	int		dop;

	i = 0;
	while (*str)
	{
		dop = word_size1(str, delim);
		if (dop > 0)
		{
			str += dop + (ispar1(*str) ? 2 : 0);
			i++;
		}
		else if (dop == -2)
			str += 2;
		else if (dop == -1)
			return (-1);
		else
			str++;
	}
	return (i);
}
