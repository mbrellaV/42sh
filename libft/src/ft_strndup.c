/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:12:04 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/02 13:20:11 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, int n)
{
	char	*count;
	int		k;

	k = 0;
	count = (char*)ft_strnew(sizeof(char) * ft_strlen(s1) + 1);
	if (count == NULL)
		return (NULL);
	while (s1[k] != '\0' && k < n)
	{
		count[k] = s1[k];
		k++;
	}
	count[k] = '\0';
	return (count);
}
