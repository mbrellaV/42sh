/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 19:36:44 by mbrella           #+#    #+#             */
/*   Updated: 2020/05/12 17:28:00 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	add_dopstr(char *goodstr, t_readline *p)
{
	char	*dopstr;

	if (!(dopstr = ft_memalloc(ft_strlen(goodstr) + 5)))
		ft_error_q(2);
	ft_strcat(dopstr, "${");
	ft_strcat(dopstr, goodstr);
	ft_strcat(dopstr, "}");
	ft_add_tab(p, dopstr);
	ft_strdel(&dopstr);
}

void	ft_find_env(char *name, t_readline *p)
{
	char	**mas;
	int		i;
	char	*goodstr;
	char	*dop;

	i = -1;
	name = ft_strsub(name, (p->flag_tab == 2 ? 0 : 2), ft_strlen(name));
	mas = globals()->g_all_var;
	while (mas[++i] != NULL)
	{
		goodstr = ft_strsub(mas[i], 0, ft_strstr(mas[i], "=") - mas[i]);
		if (p->flag_tab == 2)
		{
			dop = goodstr;
			goodstr = ft_strjoin("$", goodstr);
			if (is_cmp(name, goodstr))
				ft_add_tab(p, goodstr);
			ft_strdel(&dop);
		}
		if (p->flag_tab == 3 && is_cmp(name, goodstr))
			add_dopstr(goodstr, p);
		ft_strdel(&goodstr);
	}
	ft_strdel(&name);
}
