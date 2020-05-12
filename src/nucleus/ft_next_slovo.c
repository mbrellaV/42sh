/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next_slovo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:32:53 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/12 15:40:49 by pro              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_next_slovo(t_readline *p)
{
	if (p->buff[p->index] == ' ' || p->buff[p->index] == '\n')
	{
		do_right(p);
	}
	while ((p->buff[p->index] == ' ' || p->buff[p->index] == '\n') &&
		p->index < p->len)
	{
		do_right(p);
	}
	while (p->buff[p->index] != '\n' && p->buff[p->index] != ' ' &&
		p->index < p->len)
	{
		do_right(p);
	}
}
