/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_buff.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 18:29:17 by wstygg            #+#    #+#             */
/*   Updated: 2020/04/16 10:22:07 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_realloc_buff(t_readline *p)
{
	char	*tmp;
	int		i;

	p->buff_size *= 2;
	if (!(tmp = ft_strnew(p->buff_size + 1)))
		exit(1);
	i = -1;
	while (++i <= p->len)
		tmp[i] = p->buff[i];
	free(p->buff);
	p->buff = tmp;
}
