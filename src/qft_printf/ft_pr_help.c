/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pr_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 06:29:43 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/02 13:20:11 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			cheak_zvezd(t_printf *p)
{
	if (*p->str == '*')
	{
		p->accuracy = -4242;
		p->str++;
	}
}

void			init_printf(t_printf *p, const char *format, int fd)
{
	p->fd = fd;
	p->buff_size = 64;
	if (!(p->buff = ft_strnew(p->buff_size)))
		exit(1);
	p->buff_index = 0;
	p->str = (char *)format;
}

int				return_print(t_printf *p)
{
	write(p->fd, p->buff, p->buff_index);
	free(p->buff);
	return (p->buff_index);
}
