/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:38:32 by qmartina          #+#    #+#             */
/*   Updated: 2019/04/05 09:49:49 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_sqrt(int nb)
{
	int k;

	k = 0;
	while (k < 46341 && k < nb)
	{
		if ((k * k) == nb)
			return (k);
		else
			k++;
	}
	return (0);
}
