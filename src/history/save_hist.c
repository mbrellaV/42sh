/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:53:08 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/12 19:15:22 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int			save_history(t_memory *q)
{
	int		fd;
	char	buf[1000000];
	char	*hashsum;

	ft_bzero(buf, 1000000);
	if ((fd = open("history/hist.txt", O_CREAT | O_RDWR | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) < 0)
		return (0);
	while (q->back != NULL)
		q = q->back;
	while (q != NULL)
	{
		if (q->inp != NULL)
		{
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
