/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_back_slovo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:29:04 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/12 15:40:49 by pro              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_back_slovo(t_readline *p)
{
	if (p->buff[p->index] == ' ' || p->buff[p->index] == '\n')
	{
		do_left(p);
	}
	while (p->index > 0 && (p->buff[p->index] == ' ' ||
	p->buff[p->index] == '\n'))
	{
		do_left(p);
	}
	while (p->index > 0 && p->buff[p->index] != ' ' &&
	p->buff[p->index] != '\n')
	{
		do_left(p);
	}
	while (p->index > 0 && (p->buff[p->index] == ' ' ||
	p->buff[p->index] == '\n'))
	{
		do_left(p);
	}
	if (p->index != 0)
	{
		do_right(p);
	}
}
