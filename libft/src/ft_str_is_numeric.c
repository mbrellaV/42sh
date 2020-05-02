/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:34:21 by mbrella           #+#    #+#             */
/*   Updated: 2020/05/02 13:20:11 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_str_is_numeric_2(char *s, int flag)
{
	int c;

	if (!s)
		return (0);
	c = 0;
	while (*s != '\0')
	{
		if (!ft_isdigit(*s))
		{
			if (flag)
			{
				c++;
				if ((*s == '+' || *s == '-') && c == 1)
				{
					s++;
					continue ;
				}
			}
			return (0);
		}
		s++;
	}
	return (1);
}

int		ft_str_is_numeric(char *s)
{
	if (!s)
		return (0);
	while (*s != '\0')
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}
