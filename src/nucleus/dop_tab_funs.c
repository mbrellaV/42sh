/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_tab_funs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 19:36:44 by mbrella           #+#    #+#             */
/*   Updated: 2020/05/02 13:20:11 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_find_dir(char *dir, char *name, t_readline *p)
{
	DIR				*mydir;
	struct dirent	*myfile;

	mydir = opendir(dir);
	if (mydir != NULL)
	{
		while ((myfile = readdir(mydir)) != 0)
		{
			if (is_cmp(name, myfile->d_name) && myfile->d_name[0] != '.')
				ft_add_tab(p, myfile->d_name);
		}
		closedir(mydir);
	}
}

void	ft_add_builtins_in_tab(char *name, t_readline *p)
{
	char	**mas;
	int		i;
	char	*goodstr;

	i = 0;
	mas = globals()->g_builtins;
	while (mas[i] != NULL)
	{
		goodstr = mas[i];
		if (is_cmp(name, goodstr))
			ft_add_tab(p, goodstr);
		i++;
	}
}

void	ft_find_env(char *name, t_readline *p)
{
	char	**mas;
	int		i;
	char	*dopstr;
	char	*goodstr;

	i = 0;
	name = ft_strsub(name, 2, ft_strlen(name) - 1);
	mas = globals()->g_all_var;
	while (mas[i] != NULL)
	{
		goodstr = ft_strsub(mas[i], 0, ft_strstr(mas[i], "=") - mas[i]);
		if (p->flag_tab == 2 && is_cmp(name, goodstr))
			ft_add_tab(p, goodstr);
		if (p->flag_tab == 3 && is_cmp(name, goodstr))
		{
			if (!(dopstr = ft_memalloc(ft_strlen(goodstr) + 5)))
				ft_error_q(2);
			ft_strcat(dopstr, "${");
			ft_strcat(dopstr, goodstr);
			ft_strcat(dopstr, "}");
			ft_add_tab(p, dopstr);
			ft_strdel(&dopstr);
		}
		ft_strdel(&goodstr);
		i++;
	}
	ft_strdel(&name);
}

void	ft_find_path(t_readline *p, char *name)
{
	char	**path;
	int		i;
	char	*tmp;

	if (!*name)
	{
		return ;
	}
	if (!(tmp = ft_get_var("PATH", globals()->g_env)))
		return ;
	path = ft_strsplit1(tmp, ':');
	if (path == NULL)
		return ;
	i = -1;
	while (path[++i])
		ft_find_dir(path[i], name, p);
	ft_strdel(&tmp);
	ft_arrdel(path);
}

char	*ft_directory(char *str, int *flag_tab)
{
	int		k;
	char	*tmp;
	char	*hp;
	char	*tmp1;

	k = ft_strlen(str);
	while (--k >= 0)
		if (str[k] == '/')
		{
			if (str[0] == '~')
			{
				if (!(hp = ft_get_var("HOME", globals()->g_env)))
					ft_error_q(5);
				tmp = ft_strndup(&str[1], k - 1);
				tmp1 = ft_strjoin(hp, tmp);
				free(hp);
				ft_strdel(&tmp);
				return (tmp1);
			}
			else
				return (ft_strndup(str, k + 1));
		}
	*flag_tab = (*flag_tab <= 1 ? 0 : *flag_tab);
	return (ft_strdup("./"));
}

int		is_cmp(char *s1, char *s2)
{
	int	i;

	i = -1;
	if (s1[0] == '\0')
		return (1);
	while (s1[++i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
	}
	if (!s2[i] && s1[i])
		return (0);
	return (1);
}

char	*ft_name(char *str, t_readline *p)
{
	int		k;

	k = (int)ft_strlen(str) - 1;
	while (k > 0 && str[k] != '/' && (isword(str[k]) == 1 || str[k] == '{') &&
		str[k] != '$')
		k--;
	if (k >= 0 && str[k] == '$' && str[k + 1] != '{')
		p->flag_tab = 2;
	else if (k >= 0 && str[k] == '$' && str[k + 1] == '{')
		p->flag_tab = 3;
	return (ft_strdup(&str[k]));
}
