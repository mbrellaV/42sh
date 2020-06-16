/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_sizes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:47:39 by mbrella           #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int				operator_size(char *str)
{
	int i;

	i = 0;
	while (*str != 0 && isoperator(*str) > 0)
	{
		str++;
		i++;
	}
	return (i);
}

int				size_with_bax(char *str)
{
	int i;

	i = 0;
	str++;
	while (*str)
	{
		if (isword(*str) != 1 || *str == '}')
			return (i + 1);
		i++;
		str++;
	}
	return (i + 1);
}

int				word_size(char *str)
{
	int i;

	i = 0;
	if (isoperator(*str) > 0)
		return (operator_size(str));
	if (isword(*str) == 2)
		return (c_size(str, *str));
	if (*str == '$' && issc(*(str + 1)) == 1)
		return (sc_size(str + 1, *(str + 1)));
	else if (*str == '$')
		return (size_with_bax(str));
	if (*str == ')')
		return (1);
	if (issc(*str))
		return (1);
	while (*str)
	{
		if (isword(*str) != 1)
			return (i);
		i++;
		str++;
	}
	return (i);
}

int				c_size(char *str, char b)
{
	int		i;

	i = 0;
	str++;
	if (*str == b)
		return (-2);
	while (*str && *str != b)
	{
		i++;
		str++;
	}
	if (*str == '\0')
		return (-1);
	return (i);
}

int				sc_size(char *str, char b)
{
	int		i;
	int		cn;
	char	dop;

	i = 0;
	dop = b;
	cn = 1;
	b = find_pair_sc(b);
	if (*str == b)
		return (-2);
	while (*str != '\0' && cn != 0)
	{
		i++;
		str++;
		if (*str == dop)
			cn++;
		if (*str == b)
			cn--;
	}
	if (*str == '\0' && cn != 0)
		return (-1);
	return (i + 2);
}
