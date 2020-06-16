/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_hist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:12:00 by mbrella           #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

void		del_hist(void)
{
	ft_distruct_memory(globals()->g_memory_head);
	globals()->g_memory_head = make_memmory_with_one_node(-1, NULL);
}
