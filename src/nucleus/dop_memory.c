/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_memory.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 14:30:23 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/04 14:30:23 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

t_memory	*dop_memmory(int fd)
{
	t_memory *head;

	if (!(head = (t_memory *)ft_memalloc(sizeof(t_memory))))
		ft_error_q(2);
	head->inp = ft_strdup("authors");
	head->next = NULL;
	head->back = NULL;
	close(fd);
	return (head);
}
