/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_sc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 13:38:58 by wstygg            #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

static void		change_with_one_par(char *str, char *newstr, int *i)
{
	ft_strcat_char(newstr, str[(*i)++]);
	while (str[(*i)] != '\'')
	{
		if (str[(*i)] == -43)
		{
			ft_strcat_char(newstr, '\\');
			ft_strcat_char(newstr, '\n');
		}
		else
			ft_strcat_char(newstr, str[(*i)]);
		(*i)++;
	}
	ft_strcat_char(newstr, str[(*i)++]);
}

static void		change_with_two_par(char *str, char *newstr, int *i)
{
	ft_strcat_char(newstr, str[(*i)++]);
	while (str[(*i)] != '\"')
	{
		if (str[(*i)] == -43)
		{
			;
		}
		else if (str[*i] == '\\' && str[*i + 1] == '\n')
		{
			(*i) += 2;
		}
		else
			ft_strcat_char(newstr, str[(*i)]);
		(*i)++;
	}
	ft_strcat_char(newstr, str[(*i)++]);
}

static char		*change_slash_slashn(char *str)
{
	char	*newstr;
	int		i;

	i = 0;
	if (!(newstr = (char *)ft_memalloc(ft_strlen(str) + 2)))
		ft_error_q(2);
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			change_with_one_par(str, newstr, &i);
		else if (str[i] == '\"')
			change_with_two_par(str, newstr, &i);
		else if (str[i] == -43)
			i++;
		else if (str[i] == '\\' && str[i + 1] == '\n')
			i += 2;
		else
			ft_strcat_char(newstr, str[i++]);
	}
	return (newstr);
}

char			*ft_change_all_sc(char *str)
{
	int		i;
	int		size;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && (str[i + 1] == '(' || str[i + 1] == '{'))
			i += word_size(&str[i]);
		else if (ispar(str[i]))
		{
			size = c_size(&str[i], str[i]);
			if (size == -2)
				i += 2;
			else
				i += size + 2;
		}
		else if ((str[i] == '(' || str[i] == ')'))
			str[i] = ' ';
		else
			i++;
	}
	str = change_slash_slashn(str);
	return (str);
}
