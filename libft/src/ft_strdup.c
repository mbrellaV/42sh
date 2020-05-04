/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 12:38:31 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/02 13:20:11 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*count;
	int		k;

	k = 0;
	if (s1 == NULL)
		return (NULL);
	count = ft_strnew(ft_strlen(s1) + 1);
	if (count == NULL)
		return (NULL);
	while (s1[k] != '\0')
	{
		count[k] = s1[k];
		k++;
	}
	count[k] = '\0';
	return (count);
}
