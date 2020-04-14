/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_buff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 21:13:27 by qmartina          #+#    #+#             */
/*   Updated: 2020/02/16 21:13:28 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_add_buff(t_printf *p)
{
	if (p->buff_index == p->buff_size)
		ft_realloc_buff(p);
	p->buff[p->buff_index++] = *p->str;
	return (1);
}

int			ft_add_buff_char(t_printf *p, char c)
{
	if (p->buff_index == p->buff_size)
		ft_realloc_buff(p);
	p->buff[p->buff_index++] = c;
	return (1);
}

int			ft_add_buff_str(t_printf *p, char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		ft_add_buff_char(p, s[i]);
	return (i);
}

void		ft_realloc_buff(t_printf *p)
{
	char	*tmp;
	int		i;

	p->buff_size *= 2;
	i = -1;
	if (!(tmp = ft_strnew(p->buff_size)))
		exit(1);
	while (++i < p->buff_index)
		tmp[i] = p->buff[i];
	free(p->buff);
	p->buff = tmp;
}
