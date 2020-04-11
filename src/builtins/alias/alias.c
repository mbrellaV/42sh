/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 11:45:44 by plettie           #+#    #+#             */
/*   Updated: 2020/02/06 11:45:52 by plettie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/fshell.h"

void			ft_alias(void)
{
	if (!(g_alias = (char **)ft_memalloc(4 * sizeof(char *))))
		ft_error(15, "malloc error alias");
	g_alias[0] = ft_strdup("ll=ls");
	g_alias[1] = ft_strdup("l=ls");
	g_alias[2] = NULL;
}

char			*ft_get_alias(char *dop)
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

char			*ft_do_zam_alias(char *str)
{
	if (str == NULL)
		return (ft_memalloc(130000));
	if (ft_findenv(str, g_alias) != -404 &&
	ft_strcmp(str, "unalias") != 0 && ft_strcmp(str, "export") != 0 &&
	ft_strcmp(str, "unset") != 0 && ft_strcmp(str, "unexport") != 0
	&& ft_strcmp(str, "alias") != 0)
	{
		if (!(str = ft_get_alias(str)))
			return (ft_memalloc(130000));
	}
	return (str);
}

void			alias_usage(void)
{
	dprintf(2, "alias [alias-name[=string]...]\n");
}

int				ft_do_change_alias(char **mas)
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
			tmp2 = ft_strsub(mas[1], ft_strstr(mas[1], "=") - mas[1] + 1,
					ft_strlen(mas[1]));
			set_new_var(tmp1, tmp2, &g_alias);
			ft_strdel(&tmp1);
			ft_strdel(&tmp2);
		}
		else
			alias_usage();
	}
	else
		ft_error(15, "parse error");
	return (0);
}
