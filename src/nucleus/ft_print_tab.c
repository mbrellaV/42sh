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

int					find_max(char **tab)
{
	register int	i;
	int				max;

	i = -1;
	max = 0;
	while (tab[++i])
		if ((int)ft_strlen(tab[i]) > max)
			max = (int)ft_strlen(tab[i]);
	return (max);
}

void				ft_print_tab(t_readline *p)
{
	struct winsize	wins;
	int				curr_w;
	int				times;
	int				one_w;
	int				i;

	if (ioctl(2, TIOCGWINSZ, &wins) == -1)
		return ;
	write(2, "\n", 1);
	one_w = (find_max(p->tab) / 8 + 1) * 8;
	curr_w = 0;
	i = -1;
	while (p->tab[++i])
	{
		ft_putstr_fd(p->tab[i], 2);
		curr_w += one_w;
		if (curr_w + one_w >= wins.ws_col)
		{
			write(2, "\n", 1);
			curr_w = 0;
			continue ;
		}
		times = ft_strlen(p->tab[i]);
		while (times++ < one_w)
			write(2, " ", 1);
	}
	write(2, "\n", 1);
	p->len_hint = ft_printf_helper(p->mod);
	write(2, p->buff, p->len);
	ft_setcursor(p->index, p->len);
}
