/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_memory.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 14:30:23 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/12 19:15:22 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

t_memory	*make_memmory_with_one_node(int fd, char *buf)
{
	t_memory *head;

	if (!(head = (t_memory *)ft_memalloc(sizeof(t_memory))))
		ft_error_q(2);
	head->inp = ft_strdup("authors");
	head->next = NULL;
	head->back = NULL;
	close(fd);
	ft_strdel(&buf);
	return (head);
}
