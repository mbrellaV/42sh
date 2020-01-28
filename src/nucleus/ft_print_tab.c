/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 19:34:57 by qmartina          #+#    #+#             */
/*   Updated: 2020/01/27 19:34:58 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

int		ft_max_tab_len(t_readline *p)
{
	int 	len;
	int 	i;

	i = -1;
	len = 0;
	while (++i < p->tab_max)
	{
//		dprintf(2, "len[%d]: %zu\n", i, ft_strlen(p->tab[i]));
		if (len < ft_strlen(p->tab[i]))
			len = ft_strlen(p->tab[i]);
	}
//	dprintf(2, "retlen: %d\n", len);
	return (len);
}

void 	ft_print_tab(t_readline *p)
{
	struct winsize	wins;
	int 			i;

	if (ioctl(2, TIOCGWINSZ, &wins) == -1)
		return ;
	i = ft_max_tab_len(p) + 4;
	i = wins.ws_col / i;
	p->tab_i = -1;
	dprintf(2, "\n");
	while (++p->tab_i < p->tab_max)
	{
		if ((p->tab_i % i) == 0 && p->tab_i != 0)
			dprintf(2, "%s\n", p->tab[p->tab_i]);
		else
			dprintf(2, "%s\t", p->tab[p->tab_i]);
	}
	dprintf(2, "\n");
	p->len_hint = ft_printf_helper(p->mod);
	write(2, p->buff, p->len);
	ft_setcursor(p->index, p->len);
}
