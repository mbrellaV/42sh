/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 18:29:27 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/02 13:20:11 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/fshell.h"

void		ft_alias(void)
{
	if (!(globals()->g_alias = (char **)ft_memalloc(4 * sizeof(char *))))
		ft_error(15, "malloc error alias");
	globals()->g_alias[0] = ft_strdup("ll=ls");
	globals()->g_alias[1] = ft_strdup("l=ls");
	globals()->g_alias[2] = NULL;
}

char		*ft_get_alias(char *dop)
{
	int		i;
	char	*dopd;

	i = 0;
	dopd = ft_strjoin(dop, "=");
	while (globals()->g_alias[i])
	{
		if (ft_strstr(globals()->g_alias[i], dopd) == globals()->g_alias[i])
		{
			if (!(dop = ft_strsub(globals()->g_alias[i], ft_strlen(dopd),
			ft_strlen(globals()->g_alias[i]) - ft_strlen(dopd))))
				return (NULL);
			ft_strdel(&dopd);
			return (dop);
		}
		i++;
	}
	ft_strdel(&dopd);
	return (NULL);
}

static int	size_0(char *str, int *i, char *newstr, char *dopstr)
{
	char	*dop;
	int		size;

	size = word_size(&str[*i]);
	dop = ft_strsub(str, *i, size);
	if ((isword(str[*i]) == 1 && (!(dopstr = ft_get_alias(dop)))) ||
		str[*i] == '$')
		ft_strcat(newstr, dop);
	else
		ft_strcat(newstr, dopstr);
	(*i) += size;
	ft_strdel(&dopstr);
	ft_strdel(&dop);
	return (1);
}

static int	cycle(char *str, int *i, char *newstr)
{
	char	*dopstr;
	char	*dop;
	int		size;

	dopstr = NULL;
	size = word_size(&str[*i]);
	if (size > 0 && ispar(str[*i]))
	{
		dop = ft_strsub(str, *i, size + 2);
		ft_strcat(newstr, dop);
		*i += size + 2;
	}
	else if (size > 0 && (str[*i] == '$' || isword(str[*i]) == 1))
		return (size_0(str, i, newstr, dopstr));
	else
	{
		dop = ft_strdup(" ");
		dop[0] = str[*i];
		ft_strcat(newstr, dop);
		(*i)++;
	}
	ft_strdel(&dopstr);
	ft_strdel(&dop);
	return (1);
}

int			ft_do_zam_alias(char **str)
{
	int		i;
	char	*newstr;

	i = 0;
	newstr = *str;
	if (!(*str = ft_strnew(130000)))
		ft_error_q(2);
	while (i < (int)ft_strlen(newstr) && newstr[i] != '\0')
		if (cycle(newstr, &i, *str) == -1)
		{
			ft_strdel(&newstr);
			return (-1);
		}
	ft_strdel(&newstr);
	return (ft_strlen(*str));
}
