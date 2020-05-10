/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ltoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:53:08 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/04 13:53:14 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

static int	calc_digit(long long num)
{
	int	digit;

	digit = 1;
	if (!num)
		return (digit);
	while ((num /= 10) > 0)
		digit++;
	return (digit);
}

static void	calc_ltoa_rec(long num, char *str, int index)
{
	if (num >= 10)
		calc_ltoa_rec(num / 10, str, index - 1);
	str[index] = (num % 10) + '0';
}

char		*calc_ltoa(long long num)
{
	int		str_size;
	char	*new_str;
	short	sign;

	sign = (num < 0) ? -1 : 1;
	num *= sign;
	str_size = calc_digit(num);
	if (sign == -1)
		str_size++;
	if (!(new_str = (char *)ft_memalloc(sizeof(char) * (str_size + 1))))
		return (NULL);
	new_str[str_size] = '\0';
	if (sign == -1)
		new_str[0] = '-';
	calc_ltoa_rec(num, new_str, str_size - 1);
	return (new_str);
}
