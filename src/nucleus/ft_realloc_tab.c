/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 19:36:34 by qmartina          #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_realloc_tab(t_readline *p)
{
	char	**tmp;
	int		i;

	tmp = p->tab;
	p->tab_size += 10;
	if (!(p->tab = ft_arrnew(p->tab_size)))
		exit(2);
	i = -1;
	while (++i <= p->tab_max)
		p->tab[i] = ft_strdup(tmp[i]);
	ft_arrdel(tmp);
}
