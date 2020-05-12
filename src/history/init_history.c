/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_head_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:46:28 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/12 19:15:22 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

t_memory	*create_first_hist_token(char *line, char *buf)
{
	t_memory *head;

	if (!(head = (t_memory *)ft_memalloc(sizeof(t_memory))))
		ft_error_q(2);
	if (!(head->inp = ft_memalloc(ft_strlen(line) + 1000)))
		ft_error_q(2);
	if (line != NULL)
		ft_strcat(head->inp, line);
	if (line != NULL)
		ft_strcat((char *)(buf), line);
	ft_strcat_char((char *)(buf), -100);
	ft_strdel(&line);
	head->next = NULL;
	head->back = NULL;
	return (head);
}

static void	zap_history(t_memory **head, char **line, char **buf)
{
	if (*head == NULL)
	{
		*head = create_first_hist_token(*line, *buf);
		return ;
	}
	if (!((*head)->next = (t_memory *)ft_memalloc(sizeof(t_memory))))
		ft_error_q(2);
	if (!((*head)->next->inp = ft_memalloc(ft_strlen((*line)) + 1000)))
		ft_error_q(2);
	if (*line != NULL)
		ft_strcat((*head)->next->inp, (*line));
	ft_strcat((char *)(*buf), (*line));
	ft_strcat_char((char *)(*buf), -100);
	ft_strdel(line);
	(*head)->next->next = NULL;
	(*head)->next->back = (*head);
	(*head) = (*head)->next;
}

static int	norme_help(t_memory **head, char **line, char **hashsum, char **buf)
{
	ft_dprintf(globals()->fd[2], "history has changed not in terminal\n");
	ft_distruct_memory((*head));
	ft_strdel(line);
	ft_strdel(hashsum);
	ft_strdel(buf);
	return (1);
}

t_memory	*ft_head_memory(void)
{
	t_memory	*head;
	int			fd;
	char		*line;
	char		*buf;
	char		*hashsum;

	buf = ft_malloc(20000);
	fd = open("history/hist.txt", O_RDWR);
	if (get_next_line_with_sym(fd, &line, -100) <= 0)
		return (make_memmory_with_one_node(fd, buf));
	head = NULL;
	hashsum = line;
	while (get_next_line_with_sym(fd, &line, -100))
		zap_history(&head, &line, &buf);
	line = ft_itoa(crc_32((unsigned char *)buf, ft_strlen((char *)buf)));
	close(fd);
	if (ft_strcmp(hashsum, line) != 0 &&
		norme_help(&head, &line, &hashsum, &buf))
		return (make_memmory_with_one_node(fd, buf));
	ft_strdel(&hashsum);
	ft_strdel(&line);
	ft_strdel(&buf);
	return (head);
}
