/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:53:08 by wstygg            #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int			save_history(t_memory *q)
{
	int		fd;
	char	buf[1000000];
	char	*hashsum;

	ft_bzero(buf, 1000000);
	if ((fd = open_hist_file(0)) < 0)
		return (0);
	while (q->back != NULL)
		q = q->back;
	while (q != NULL)
	{
		if (q->inp != NULL)
		{
			cypher_str(q->inp);
			ft_strcat((char *)buf, q->inp);
			ft_strcat_char((char *)buf, -100);
		}
		q = q->next;
	}
	hashsum = ft_itoa(crc_32((unsigned char *)buf, ft_strlen((char *)buf)));
	ft_dprintf(fd, "%s%c%s%c", hashsum, -100, buf, 0);
	ft_strdel(&hashsum);
	close(fd);
	return (0);
}
