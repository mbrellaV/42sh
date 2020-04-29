/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 18:29:27 by wstygg            #+#    #+#             */
/*   Updated: 2020/04/29 20:01:50 by wstygg           ###   ########.fr       */
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


static int	cycle(char *str, int *i, char *newstr)
{
	char	*dopstr;
	char	*dop;
	int		size;

	dopstr = NULL;
	size = word_size(&str[*i]);
	if (size < 0)
		return (-1);
	if (ispar(str[*i]))
	{
		dop = ft_strsub(str, *i, size + 2);
		ft_strcat(newstr, dop);
		*i += size + 2;
	}
	else if (str[*i] == '$')
	{
		dop = ft_strsub(str, *i, size);
		ft_strcat(newstr, dop);
		(*i) += size;
	}
	else if (isword(str[*i]) == 1)
	{
		dop = ft_strsub(str, *i, size);
		if (!(dopstr = ft_get_alias(dop)))
			ft_strcat(newstr, dop);
		else
			ft_strcat(newstr, dopstr);
		*i += size;
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
	while (i < ft_strlen(newstr) && newstr[i] != '\0')
		if (cycle(newstr, &i, *str) == -1)
		{
			ft_strdel(&newstr);
			return (-1);
		}
	ft_strdel(&newstr);
	return (ft_strlen(*str));
}

int			alias_error(int error, char *tmp1, char *tmp2)
{
	put_error_to_shell(error);
	if (error == 15)
	{
		ft_error(15, "parse error");
		return (-1);
	}
	if (error == 14)
	{
		ft_dprintf(globals()->fd[2], "alias [alias-name[=string]...]\n");
		return (-1);
	}
	ft_dprintf(globals()->fd[2], "alias error: wrong argument: |%s|\n", tmp2);
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
	return (-1);
}

int			ft_do_change_alias(char **mas)
{
	char	*tmp1;
	char	*tmp2;

	if (mas[1] == NULL && ft_strcmp(mas[0], "alias") == 0)
		ft_show_env(globals()->g_alias);
	else if (ft_strcmp(mas[0], "unalias") == 0 && mas[1] != NULL &&
		mas[2] == NULL && ft_strstr(mas[1], "=") == NULL)
		unset_var(mas[1], &globals()->g_alias);
	else if (ft_strcmp(mas[0], "alias") == 0 && mas[1] && mas[2] == NULL)
	{
		if (ft_strstr(mas[1], "=") != NULL)
		{
			tmp1 = ft_strsub(mas[1], 0, ft_strstr(mas[1], "=") - mas[1]);
			tmp2 = ft_strsub(mas[1], ft_strstr(mas[1], "=") -
				mas[1] + 1, ft_strlen(mas[1]));
			if (is_system_symbol(*tmp2) == 1)
				return (alias_error(2, tmp1, tmp2));
			set_new_var(tmp1, tmp2, &globals()->g_alias);
			ft_strdel(&tmp1);
			ft_strdel(&tmp2);
		}
		else
			return (alias_error(14, NULL, NULL));
	}
	else
		return (alias_error(15, NULL, NULL));
	return (0);
}
