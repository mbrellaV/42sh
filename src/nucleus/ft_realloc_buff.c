/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_buff.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:08:51 by qmartina          #+#    #+#             */
/*   Updated: 2020/01/27 17:08:52 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_realloc_buff(t_readline *p)
{
	char	*tmp;
	int		i;

//	dprintf(2, "REMALLOC START\n");
	p->buff_size *= 2;
	tmp = ft_strnew(p->buff_size + 1);
	i = -1;
	while(++i <= p->len)
		tmp[i] = p->buff[i];
	free(p->buff);
	p->buff = tmp;
	/*
	tmp = p->buff;
	p->buff = ft_strnew(p->buff_size + 1);
//	p->buff = (char *)malloc(sizeof(p->buff_size) + 1);
	i = -1;
	while(++i <= p->len)
		p->buff[i] = tmp[i];
//	dprintf(2, "REMALLOC END\n");
	free(tmp);*/
}
