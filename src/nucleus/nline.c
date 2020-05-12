/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nline.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:32:53 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/12 19:15:22 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	init_nline(t_readline *p, t_nline *l)
{
	int		i;
	int		len_str;

	i = p->index;
	while (p->buff[i] && p->buff[i] != '\n')
		i--;
	len_str = 0;
	while (p->buff[++i] && p->buff != '\n')
		len_str++;
}
