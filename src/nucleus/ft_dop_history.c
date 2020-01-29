/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dop_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:52:07 by qmartina          #+#    #+#             */
/*   Updated: 2020/01/28 16:52:08 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

void		ft_dop_history(t_memory *q, t_readline *p, int k)
{
	if (k == 1)
	{
		free(p->buff);
		p->buff = ft_strdup((q)->inp);
		ft_cleanstr(p->index, p);
		p->index = (int)ft_strlen(p->buff);
		p->len = (int)ft_strlen(p->buff);
		ft_putstr_fd((q)->inp, 2);
	}
	else if (k == 2)
	{
		free(p->buff);
		p->buff = ft_strnew(1);
		ft_cleanstr(p->index, p);
		p->index = (int)ft_strlen(p->buff);
		p->len = ft_strlen(p->buff);
		ft_putstr_fd(p->buff, 2);
	}
}
