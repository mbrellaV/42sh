/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 17:18:08 by wstygg            #+#    #+#             */
/*   Updated: 2020/06/03 20:13:49 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int			ft_free(void *memory)
{
	if (!memory)
		return (0);
	free(memory);
	return (0);
}

void		*ft_malloc(size_t size)
{
	char	*ret;
	size_t	i;

	ret = malloc(size);
	if (!ret)
		exit(228);
	i = 0;
	while (i < size)
		ret[i++] = 0;
	return ((void*)ret);
}
