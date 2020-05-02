/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_head_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:46:28 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/02 13:20:11 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

t_memory	*dop_memmory(int fd)
{
	t_memory *head;

	if (!(head = (t_memory *)ft_memalloc(sizeof(t_memory))))
		ft_error_q(2);
	head->inp = NULL;
	head->next = NULL;
	head->back = NULL;
	close(fd);
	return (head);
}

void		ft_strcat_char(char *buf, char c)
{
	char	*dopstr;

	dopstr = ft_strdup(" ");
	dopstr[0] = c;
	ft_strcat((char *)buf, dopstr);
	ft_strdel(&dopstr);
}

t_memory	*ft_head_memory(void)
{
	t_memory	*head;
	int			fd;
	char		*line;
	char		*buf[200000];
	char		*hashsum;

	ft_bzero(buf, 200000);
	fd = open("history/hist.txt", O_RDWR);
	if (get_next_line_with_sym(fd, &line, -100) <= 0)
		return (dop_memmory(fd));
	if (!(head = (t_memory *)ft_memalloc(sizeof(t_memory))))
		ft_error_q(2);
	hashsum = line;
	while (get_next_line_with_sym(fd, &line, -100))
	{
		if (!(head->next = (t_memory *)ft_memalloc(sizeof(t_memory))))
			ft_error_q(2);
		if (!(head->next->inp = ft_memalloc(ft_strlen(line) + 1000)))
			ft_error_q(2);
		if (line != NULL)
			ft_strcat(head->next->inp, line);
		ft_strcat((char *)buf, line);
		ft_strcat_char((char *)buf, -100);
		ft_strdel(&line);
		head->next->next = NULL;
		head->next->back = head;
		head = head->next;
	}
	line = ft_itoa(crc_32((unsigned char *) buf, ft_strlen((char *) buf)));
	close(fd);
	if (ft_strcmp(hashsum, line) != 0)
	{
		ft_dprintf(2, "history has changed not in terminal\n");
		ft_distruct_memory(head);
		ft_strdel(&line);
		ft_strdel(&hashsum);
		return (dop_memmory(fd));
	}
	ft_strdel(&hashsum);
	ft_strdel(&line);
	return (head);
}

int			save_history(t_memory *q)
{
	int		fd;
	char	buf[1000000];
	char	*hashsum;

	ft_bzero(buf, 1000000);
	fd = open("history/hist.txt", O_CREAT | O_RDWR | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
			S_IROTH | S_IWOTH);
	if (fd < 0)
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
	hashsum = ft_itoa(crc_32((unsigned char *) buf, ft_strlen((char *) buf)));
	write(fd, hashsum, ft_strlen(hashsum));
	ft_putchar_fd(-100, fd);
	write(fd, buf, ft_strlen((char *)buf));
	ft_putchar_fd(0, fd);
	ft_strdel(&hashsum);
	close(fd);
	return (0);
}
