/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_whtsp_end.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 18:13:36 by mbrella           #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_whtsp_end(char const *s)
{
	unsigned int cn;
	unsigned int count;

	cn = ft_strlen(s) - 1;
	count = 0;
	while ((s[cn] == '\t' || s[cn] == '\n' || s[cn] == ' ') && s[cn])
	{
		cn--;
		count++;
	}
	return (count);
}
