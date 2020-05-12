/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:22:17 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/12 19:15:22 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*arr;
	size_t	i;

	i = 0;
	arr = (char*)ft_memalloc(sizeof(char) * (size + 1));
	if (!arr)
		return (NULL);
	while (i < size)
	{
		arr[i] = 0;
		i++;
	}
	arr[i] = '\0';
	return (arr);
}
