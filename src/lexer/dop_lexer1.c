/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_lexer1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:57:32 by mbrella           #+#    #+#             */
/*   Updated: 2019/12/16 18:57:33 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

char				*do_zam_str_by_str(int start, int end, char *str, char *zam_str)
{
	char	*newstr;
	int		i;
	int		dopi;

	i = 0;
	dopi = 0;
	if (zam_str == NULL)
		zam_str = ft_strdup("\0");
	//ft_printf("|%d %d %s|\n", start, end, zam_str);
	if (!(newstr = ft_memalloc((ft_strlen(str) + ft_strlen(zam_str) + 2) * sizeof(char))))
		return (NULL);
	while (str[i] != '\0' && i < start - 1)
	{
		//ft_printf("%s\n", newstr);
		newstr[i] = str[i];
		i++;
	}
	while (zam_str[dopi] != '\0')
	{
		//ft_printf("%s\n", newstr);
		newstr[i] = zam_str[dopi];
		dopi++;
		i++;
	}
	while (str[end] != '\0')
	{
		newstr[i] = str[end];
		end++;
		i++;
	}
	ft_strdel(&str);
	ft_strdel(&zam_str);
	return (newstr);
}

char				*do_zam_str_bax(char *str1)
{
	t_dop_bax	*t;
	int			start;
	int			end;
	int			dop;

	dop = 0;
	if (!(t = ft_memalloc(sizeof(t_dop_bax))))
		return (NULL);
	t->c = 0;
	t->i = 0;
	end = 0;
	t->str = str1;
	if (!(t->new = ft_strnew(1)))
		return (NULL);
	while (t->str[t->i])
	{
		if (t->str[t->i] == '$' && t->str[t->i - 1] != '\\' && t->str[t->i + 1] != '(')
		{
			if (t->str[t->i + 1] == '{')
				dop++;
			start = t->i + 1;
			while (t->str[t->i] != '\0' && isword(t->str[t->i]) != 0 && t->str[t->i] != '}')
			{
				//ft_printf("\nsas1: %s\n", &t->str[t->i]);
				t->i++;
			}
			end += t->i + (t->str[t->i] == '}');
		//	ft_printf("\nsas1: %d %d\n", end, dop);
			str1 = ft_strsub(t->str, start + (dop > 0 ? 1 : 0), end - (dop > 0 ? 2 : 0) - start);
		//	ft_printf("\nsas1: %s    %d\n", str1, end - (dop + (t->str[t->i] == '}')) - start);
			t->str = do_zam_str_by_str(start, end, t->str, ft_get_var(str1, g_all_var));
			ft_strdel(&str1);
		//	ft_printf("\nsas1: %s\n", t->str);
			return (ft_zach_dop_str(t->str, t));
		}
		t->i++;
	}
	//ft_printf("\nsas1: %s\n", t->str);
	return (ft_zach_dop_str(t->str, t));
}

char				*do_obr_zamena_sp(char *line)
{
	int		i;
	int		d;
	int		size;
	char	*new;

	i = 0;
	d = 0;
	size = 0;
	while (line[i++] != '\0')
		size++;
	if (!(new = ft_memalloc(size * sizeof(char) + 1)))
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] < 0)
			new[d++] = -1 * (line[i++]);
		else
			new[d++] = line[i++];
	}
	new[d] = '\0';
	ft_strdel(&line);
	return (new);
}

char				*do_zamena_sp(char *line)
{
	int		i;
	int		d;
	char	*new;

	i = 0;
	d = 0;
	if (!(new = ft_memalloc(ft_strlen(line) * sizeof(char) + 1)))
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\\' && line[i + 1] != '\0')
		{
			new[d] = -1 * (line[i + 1]);
			i++;
		}
		else
			new[d] = line[i];
		i++;
		d++;
	}
	new[d] = '\0';
	return (new);
}

int					c_size(char *str, char b)
{
	int i;

	i = 0;
	str++;
	if (*str == b)
		return (-2);
	while (*str && *str != b)
	{
		i++;
		str++;
	}
	return (i);
}
