/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:04:08 by qmartina          #+#    #+#             */
/*   Updated: 2020/01/27 17:04:09 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_do_addstr(t_readline *p, char *str)
{
	int i;

	i = -1;
	while (str[++i])
		ft_do_addch(p, str[i]);
}

void	ft_do_addch(t_readline *p, char c)
{
	char 	tmp;
	char 	tmp2;
	int		i;

	p->len++;
	if (p->len == p->buff_size)
		ft_realloc_buff(p);
	if ((p->len - 1) == p->index)
		p->buff[p->index++] = c;
	else
	{
		i = p->index + 1;
		tmp = p->buff[p->index];
		p->buff[p->index++] = c;
		tmp2 = p->buff[p->index];
		while (p->index < p->len)
		{
			p->buff[p->index++] = tmp;
			tmp = tmp2;
			tmp2 = p->buff[p->index];
		}
		p->buff[p->index] = tmp2;
		p->index = i;
	}
	ft_cleanstr(p->index + p->len_hint, p);
	p->len_hint = ft_printf_helper(p->mod);
	write(2, p->buff, p->len);
	ft_setcursor(p->index, p->len);
}
