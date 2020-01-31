/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:39:43 by qmartina          #+#    #+#             */
/*   Updated: 2020/01/31 18:39:45 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_add_tab(t_readline *p, char *str)
{
	if (p->tab_max == p->tab_size)
		ft_realloc_tab(p);
	p->tab[p->tab_max++] = ft_strdup(str);
}

int 	is_cmp(char *s1, char *s2)
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
			{
				ft_add_tab(p, myfile->d_name);
//				dprintf(2, "%s: %s\n", dir, p->tab[p->tab_max - 1]);
			}
		}
		closedir(mydir);
	}
}

void	ft_find_path(t_readline *p, char *name)
{
	char 	**path;
	int 	i;
	char	*tmp;

	if (!*name)
	{
		return ;
	}
	tmp = ft_get_var("PATH", g_env);
	path = ft_strsplit1(tmp, ':');
	i = -1;
	while (path[++i])
		ft_find_dir(path[i], name, p);
	ft_strdel(&tmp);
	ft_arrdel(path);
}

char	*ft_directory(char *str, int *flag_dir)
{
	int 	k;
	char	*tmp;
	char	*hp;
	char	*tmp1;

	k = ft_strlen(str);
	while (--k >= 0)
	{
		if (str[k] == '/')
		{
			if (str[0] == '~')
			{
				if (!(hp = ft_get_var("HOME", g_env)))
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
	}
	*flag_dir = 0;
	return (ft_strdup("./"));
}

char	*ft_name(char *str)
{
	int		k;

	k = ft_strlen(str);
	while (--k >= 0 && str[k] != '/' && isword(str[k]) == 1)
		;
	return (ft_strdup(&str[k + 1]));
}

int		is_add_str_tab(t_readline *p)
{
	int 	i;
	int		k;

	k = 0;
	if (p->tab_max == 1)
		return (-100);
	while (p->tab[0] && p->tab[0][k])
	{
		i = 0;
		while (i < p->tab_max && p->tab[0][k] && p->tab[i][k] && p->tab[0][k] == p->tab[i][k])
			i++;
		if (i != p->tab_max)
			return (k);
		else
			k++;
	}
	return (k);
}

void	ft_cheak_tab(t_readline *p)
{
	int				i;
	char			*str;
	char 			*name;
	char 			*dir;
	int				flag_dir;
	int				flag_left_word;
	int				i_dop;

	flag_dir = 1;
	flag_left_word = 0;
	while (p->index < p->len && isword(p->buff[p->index]) == 1)
	{
		tputs(tgetstr("nd", NULL), 1, ft_c);
		p->index++;
	}
	i = p->index;
	while (--i > 0 && isword(p->buff[i]) == 1)
		;
	i_dop = i;
	while (--i_dop > 0 && isword(p->buff[i_dop]) != 1)
		;
	if (i_dop > 0)
		flag_left_word = 1;
	if (i != 0)
		i++;
	str = ft_strndup(&(p->buff[i]), p->index - i);
	p->tab_max = 0;
	name = ft_name(str);
	dir = ft_directory(str, &flag_dir);
	if (flag_dir == 0 && flag_left_word != 1)
		ft_find_path(p, str);
	else
	{
		ft_find_dir(dir, name, p);
	}
	if ((int)ft_strlen(name) < is_add_str_tab(p))
	{
		i = ft_strlen(name);
		while (i < is_add_str_tab(p))
		{
			ft_do_addch(p, p->tab[0][i]);
			i++;
		}
	}
	else if (is_add_str_tab(p) == -100)
	{
		i = ft_strlen(name);
		while (p->tab[0][i])
		{
			ft_do_addch(p, p->tab[0][i]);
			i++;
		}
	}
	else
		ft_print_tab(p);
	ft_arrdel(p->tab);
	p->tab_size = 8;
	p->tab = ft_arrnew(p->tab_size);
	p->tab_i = 0;
	free(name);
	free(str);
	free(dir);
}
