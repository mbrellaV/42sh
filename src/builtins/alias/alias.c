/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 18:29:27 by wstygg            #+#    #+#             */
/*   Updated: 2020/04/14 11:11:54 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/fshell.h"

void		ft_alias(void)
{
	if (!(g_alias = (char **)ft_memalloc(4 * sizeof(char *))))
		ft_error(15, "malloc error alias");
	g_alias[0] = ft_strdup("ll=ls");
	g_alias[1] = ft_strdup("l=ls");
	g_alias[2] = NULL;
}

char		*ft_get_alias(char *dop)
{
	int		i;
	char	*dopd;

	i = 0;
	dopd = ft_strjoin(dop, "=");
	while (g_alias[i])
	{
		if (ft_strstr(g_alias[i], dopd) == g_alias[i])
		{
			if (!(dop = ft_strsub(g_alias[i], ft_strlen(dopd),
			ft_strlen(g_alias[i]) - ft_strlen(dopd))))
				return (NULL);
			ft_strdel(&dopd);
			return (dop);
		}
		i++;
	}
	ft_strdel(&dopd);
	return (NULL);
}


static void	cycle(char *str, int *i, char *newstr)
{
	char	*dopstr;
	char	*dop;

	dopstr = NULL;
	dop = NULL;
	if (ispar(str[*i]))
	{
		dopstr = ft_strsub(str, *i, c_size(&str[*i], str[*i]) + 2);
		ft_strcat(newstr, dopstr);
		*i += c_size(&str[*i], str[*i]) + 2;
	}
	else if (isword(str[*i]) == 1)
	{
		dop = ft_strsub(str, *i, word_size(&str[*i]));
		if (!(dopstr = ft_get_alias(dop)))
		{
			ft_strcat(newstr, dop);
			*i += word_size(&str[*i]);
		}
		else
		{
			ft_strcat(newstr, dopstr);
			*i += word_size(&str[*i]);
		}
	}
	else
	{
		dop = ft_strdup(" ");
		dop[0] = str[*i];
		ft_strcat(newstr, dop);
		(*i)++;
	}
	ft_strdel(&dopstr);
	ft_strdel(&dop);
}

int			ft_do_zam_alias(char *str, t_readline *p)
{
	int		i;

	i = 0;
	if (!(p->buff = ft_strnew(130000)))
		ft_error_q(2);
	while (i < ft_strlen(str) && str[i] != '\0')
		cycle(str, &i, p->buff);
	ft_strdel(&str);
	return (ft_strlen(p->buff));
}
//char		*ft_do_zam_alias(char *str)
//{
//	char	*tmp;
//	int		i;
//
//	i = 0;
//	if (str == NULL)
//		return (NULL);
//	if (*str == '\0')
//		return (str);
//	while (str[i])
//	{
//
//		i++;
//	}
//	if (ft_findenv(str, g_alias) != -404 && ft_strcmp(str, "unalias") != 0
//		&& ft_strcmp(str, "export") != 0 &&
//	ft_strcmp(str, "unset") != 0 && ft_strcmp(str, "unexport") != 0
//		&& ft_strcmp(str, "alias") != 0)
//	{
//		tmp = str;
//		if (!(str = ft_get_alias(str)))
//			return (ft_memalloc(130000));
//		ft_strdel(&tmp);
//	}
//	return (str);
//}

int			ft_do_change_alias(char **mas)
{
	char	*tmp1;
	char	*tmp2;

	if (mas[1] == NULL && ft_strcmp(mas[0], "alias") == 0)
		ft_show_env(g_alias);
	else if (ft_strcmp(mas[0], "unalias") == 0 && mas[1] != NULL &&
		mas[2] == NULL && ft_strstr(mas[1], "=") == NULL)
		unset_var(mas[1], &g_alias);
	else if (ft_strcmp(mas[0], "alias") == 0 && mas[1] && mas[2] == NULL)
	{
		if (ft_strstr(mas[1], "=") != NULL)
		{
			tmp1 = ft_strsub(mas[1], 0, ft_strstr(mas[1], "=") - mas[1]);
			tmp2 = ft_strsub(mas[1], ft_strstr(mas[1], "=") -
				mas[1] + 1, ft_strlen(mas[1]));
			set_new_var(tmp1, tmp2, &g_alias);
			ft_strdel(&tmp1);
			ft_strdel(&tmp2);
		}
		else
			ft_putstr_fd("alias [alias-name[=string]...]\n", 2);
	}
	else
		ft_error(15, "parse error");
	return (0);
}
