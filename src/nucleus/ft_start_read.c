/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:56:09 by qmartina          #+#    #+#             */
/*   Updated: 2020/01/28 16:56:12 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

void	ft_start_read(t_readline *p)
{
	p->buff_size = 64;
	p->buff = ft_strnew(p->buff_size);
	p->index = 0;
	p->len = 0;
	p->esc = 0;
	p->tab_size = 8;
	p->tab = ft_arrnew(p->tab_size);
}