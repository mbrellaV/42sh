/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_8.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:15:41 by qmartina          #+#    #+#             */
/*   Updated: 2020/01/16 18:41:16 by qmartina         ###   ########.fr       */
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

//	dprintf(2, "\ndir: !%s!\nname: !%s!\n", dir, name);
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

	if (!*name)
	{
		return ;
	}
	path = ft_strsplit1("/Users/qmartina/.brew/bin:/Users/qmartina/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/go/bin:/usr/local/munki", ':');
	i = -1;
	while (path[++i])
		ft_find_dir(path[i], name, p);
}

char	*ft_directory(char *str)
{
	int 	k;

	k = ft_strlen(str);
	while (--k >= 0)
	{
		if (str[k] == '/')
		{
			if (str[0] == '/')
				return(ft_strjoin(".", ft_strndup(str, k + 1)));
			else if ((str[0] == '.' || str[0] == '~') && str[1] == '/')
				return(ft_strndup(str, k + 1));
			else if (str[0] == '.' && str[1] != '/')
				return(ft_strjoin("./", ft_strndup(&str[1], k + 1)));
			else if (str[0] == '~' && str[1] != '/')
				return(ft_strjoin("~/", ft_strndup(&str[1], k + 1)));
			else
				return(ft_strjoin("./", ft_strndup(str, k + 1)));
		}
	}
	return (ft_strdup("./"));
}

char	*ft_name(char *str)
{
	int		k;

	k = ft_strlen(str);
	while (--k >= 0 && str[k] != '/')
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
	while (p->tab[0][k])
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

	while (p->index < p->len && p->buff[p->index] != ' ' && p->buff[p->index] != '|' && p->buff[p->index] != ';')
	{
		tputs(tgetstr("nd", NULL), 1, ft_c);
		p->index++;
	}
	i = p->index;
	while (--i > 0 && p->buff[i] != ' ' && p->buff[i] != ';' && p->buff[i] != '|')
		;
	if (i != 0)
		i++;
	str = ft_strndup(&(p->buff[i]), p->index - i);
//	dprintf(2, "str: !%s!\n", str);
	while (--i > 0 && p->buff[i] == ' ')
		;
	p->tab_max = 0;
	name = ft_name(str);
	dir = ft_directory(str);
	if (i == -1 || i == 0 || p->buff[i] == ';' || p->buff[i] == '|')
		ft_find_path(p, str);
	else
	{
		ft_find_dir(dir, name, p);
	}
//	dprintf(2, "\n");
	if ((int)ft_strlen(name) < is_add_str_tab(p))
	{
		i = ft_strlen(name);
		while (i < is_add_str_tab(p))
		{
//			dprintf(2, "add: !%c!\n", p->tab[0][i]);
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

void	ft_read_8(t_readline *p, t_memory *head, int mod)
{
	char 		buf[8];
	int			rt;
	t_memory	*h;

	p->mod = mod;
	p->len_hint = ft_printf_helper(p->mod);
	h = head;
	while ((rt = read(0, buf, 8)) && buf[0] != '\n')
	{
		p->sum_read = ft_add_sumchar(buf, rt);
		if (rt > 1)
		{
			p->sum_read == 186 || p->sum_read == 185 ? ft_do_leftright(p) : NULL;
			p->sum_read == 183 || p->sum_read == 184 ? ft_putmemory(&h, p) : NULL;
			p->sum_read == 341 ? ft_upcursor(p) : NULL;
			p->sum_read == 342 ? ft_downcursor(p) : NULL;
			p->sum_read == 297 || p->sum_read == 298 || p->sum_read == 190 || p->sum_read == 188 ? ft_arrows(p) : NULL;
		}
		else if (p->sum_read == 9)
			ft_cheak_tab(p);
		else if (p->sum_read == 18)
		{
			find_history(p, h);
			p->len_hint = ft_printf_helper(p->mod);
			ft_putstr_fd(p->buff, 2);
		}
		else if (p->sum_read == 25 || p->sum_read == 23 || p->sum_read == 21 || p->sum_read == 127)
			ft_cut_copy(p);
		else if (ft_signal(p->sum_read, p) == 1)
			return ;
		else if (p->sum_read == 27 || (p->sum_read == 119 && p->esc == 1))
			ft_do_copy(p);
		else if (ft_signal(p->sum_read, p) == 404)
			ft_do_addch(p, buf[0]);
	}
//	p->buff[p->len] = '\0';
}
