/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 18:29:17 by wstygg            #+#    #+#             */
/*   Updated: 2020/04/15 18:36:54 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

char	*do_reverse_zamena(char *str)
{
	int		i;
	char	*newstr;
	char	*tmp;

	i = -1;
	if (!(newstr = ft_memalloc(ft_strlen(str) * 2 + 1)))
		ft_error_q(15);
	while (str[++i] != '\0')
	{
		if (str[i] < 0)
		{
			tmp = ft_strdup("\\ ");
			tmp[1] = -1 * str[i];
		}
		else
		{
			tmp = ft_strdup(" ");
			tmp[0] = str[i];
		}
		ft_strcat(newstr, tmp);
		ft_strdel(&tmp);
	}
	ft_strdel(&str);
	return (newstr);
}

char	*ck_br_faf(char *s)
{
	int		i;
	char	c;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			c = s[i];
			s[i] = 'F';
			while (s[++i] != c)
				s[i] = 'a';
			s[i] = 'F';
		}
	}
	return (s);
}

char	*ck_br_cycle(char *s, int k, int i)
{
	while (1)
	{
		i = -1;
		while (s[++i])
			if (s[i] == '(')
				k = i;
		if (s[k] && s[k] == '(')
		{
			i = k;
			while (s[++i] && s[i] != ')')
				;
		}
		else
			break ;
		if (s[i] && s[i] == ')')
		{
			s[k] = 'A';
			s[i] = 'A';
		}
		else if (strdelr(&s))
			return (NULL);
	}
	return (s);
}

int		ck_br(const char *str)
{
	char	*s;
	int		i;
	int		k;

	k = 0;
	s = ft_strdup(str);
	s = ck_br_faf(s);
	if ((i = check_bracket(s)) && i != 1 && strdelr(&s))
		return (i);
	if ((s = ck_br_cycle(s, k, i)) == NULL)
		return (0);
	i = -1;
	while (s[++i])
		if (s[i] == ')')
		{
			ft_strdel(&s);
			return (-2);
		}
	ft_strdel(&s);
	return (1);
}
