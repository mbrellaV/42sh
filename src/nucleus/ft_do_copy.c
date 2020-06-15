/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:50:52 by qmartina          #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_do_copy(t_readline *p)
{
	if (p->sum_read == 27)
		p->esc = 1;
	else if (p->sum_read == 119)
	{
		free(globals()->g_cp);
		globals()->g_cp = ft_strdup(p->buff);
		p->esc = 0;
	}
}
