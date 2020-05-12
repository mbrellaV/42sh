/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:53:03 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/12 22:36:31 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long double			ft_pow(long double base, long double exp)
{
	long double		i;
	long double		a;

	i = 1.0;
	a = base;
	if (exp == 1.0)
		return (base);
	if (exp == 0.0)
		return (1.0);
	if (exp < 0.0)
	{
		while (i > exp)
		{
			base /= a;
			i--;
		}
		return (base);
	}
	while (i < exp)
	{
		base *= a;
		i++;
	}
	return (base);
}

int64_t				ft_floor(long double base)
{
	int64_t			d;

	d = (int64_t)base;
	if (base < 0.0)
		d--;
	return (d);
}

int64_t				ft_log10(long double base)
{
	int64_t			a;
	int64_t			i;

	a = 10;
	if (base <= 1.0)
		return (0);
	i = 0;
	while (a < base)
	{
		a *= 10;
		i++;
	}
	return (i);
}
