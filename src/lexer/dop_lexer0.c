/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_lexer0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:57:25 by mbrella           #+#    #+#             */
/*   Updated: 2019/12/16 18:57:26 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

int				ispar(char c)
{
	return (c == 34 || c == 39);
}

int				issc(char c)
{
	return (c == '(' || c == '{');
}

int				isoperator(char c)
{
	return (c == '<' || c == '&' || c == '|' || c == '>' || c == ';');
}

char			find_pair_sc(char c)
{
	if (c == '(')
		return (')');
	if (c == '{')
		return ('{');
	return (0);
}

int				isword(char c)
{
	if (ispar(c) == 1)
		return (2);
	if (issc(c) == 1)
		return (3);
	if (!isoperator(c) && c != ' ' && c != '\t')
		return (1);
	return (0);
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
	return (i + 1);
}
