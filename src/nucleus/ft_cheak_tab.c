/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cheak_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:39:43 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/12 22:36:31 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_check_tab_addstr(t_readline *p, int i)
{
	if (i < is_add_str_tab(p))
		while (i < is_add_str_tab(p))
			ft_do_addch(p, p->tab[0][i++]);
	else if (is_add_str_tab(p) == -100)
	{
		while (p->tab[0][i])
			ft_do_addch(p, p->tab[0][i++]);
		ft_do_addch(p, ' ');
	}
	else
		ft_print_tab(p);
}

void	ft_cheak_tab(t_readline *p)
{
	int				i;
	char			*str;
	char			*name;
	char			*dir;

	dop_to_check_tab(p, &str, &i);
	if (!(name = ft_name(str, p)))
	{
		ft_strdel(&str);
		return ;
	}
	dir = ft_directory(str, &p->flag_tab);
	if (p->flag_tab == 0 && p->flag_left_word != 1)
		ft_find_path(p, str);
	else if (p->flag_tab < 2)
		ft_find_dir(dir, name, p);
	else if (p->flag_tab > 1)
		ft_find_env(name, p);
	ft_print_tab(p);
	if (p->flag_tab < 2 && p->flag_left_word != 1)
		ft_add_builtins_in_tab(name, p);
	i = ft_strlen(name);
	ft_check_tab_addstr(p, i);
	dop_to_check_tab_delete(p, &name, &str, &dir);
}
