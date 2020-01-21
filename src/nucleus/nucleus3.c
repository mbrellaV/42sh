/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nucleus3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 18:26:34 by qmartina          #+#    #+#             */
/*   Updated: 2019/12/05 18:26:36 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

int			ft_put_n(int len, int i, int max)
{
	struct winsize wins;

	if (ioctl(2, TIOCGWINSZ, &wins) == -1)
		return (-1);
	if ((len + i) == wins.ws_col && i != max)
	{
		write(2, "\n", 1);
		return (1);
	}
	else
	{
		if (((len + i - wins.ws_col) % wins.ws_col) == 0 && i != max)
		{
			write(2, "\n", 1);
			return (1);
		}
	}
	return (-1);
}

t_memory	*ft_head_memory(void)
{
	t_memory	*head;
	int			fd;
	char		*line;

	fd = open("/Users/mbrella/Desktop/projects/21beta/42start/history/hist", 'r');
	ft_printf("sas0/// %d\n", fd);
	if (get_next_line(fd, &line) == -1)
	{
		ft_printf("sas1///");
		if (!(head = (t_memory *)malloc(sizeof(t_memory))))
			ft_error_q(2);
		head->inp = NULL;
		head->next = NULL;
		head->back = NULL;
		close (fd);
		return (head);
	}
	ft_printf("sas2///");
	if (!(head = (t_memory *)malloc(sizeof(t_memory))))
		ft_error_q(2);
	head->inp = ft_strdup(line);
	ft_strdel(&line);
	head->back = NULL;
	while (get_next_line(fd, &line) != -1)
	{
		if (!(head->next = (t_memory *)malloc(sizeof(t_memory))))
			ft_error_q(2);
		head->next->inp = ft_strdup(line);
		ft_strdel(&line);
		head->next->back = head;
		head = head->next;
	}
	close (fd);
	return (head);
}

t_memory	*ft_memory(t_memory *back, char *str)
{
	t_memory *tmp;
	t_memory *p;


	tmp = (t_memory *)malloc(sizeof(t_memory));
	if (!tmp)
		return (NULL);
	p = back->next;
	back->next = tmp;
	tmp->inp = ft_strdup(str);
	tmp->next = p;
	tmp->back = back;
	if (p != NULL)
		p->back = tmp;
	ft_printf("\n///////////1 %s\n", (back)->inp);
	(back)->inp = do_zam_str_hist_var((back)->inp, back);
	//ft_printf("\n///////////2 %s\n", (back)->next->inp);
	return (tmp);
}

void		ft_dop_history(t_memory ***q, char ***input, t_flag **flag, int k)
{
	if (k == 1)
	{
		free(**input);
		**input = ft_strdup((**q)->inp);
		ft_cleanstr((*flag)->i);
		(*flag)->i = ft_strlen(**input);
		(*flag)->max = ft_strlen(**input);
		ft_putstr_fd((**q)->inp, 2);
	}
	else if (k == 2)
	{
		free(**input);
		**input = ft_strnew(1);
		ft_cleanstr((*flag)->i);
		(*flag)->i = ft_strlen(**input);
		(*flag)->max = ft_strlen(**input);
		ft_putstr_fd(**input, 2);
	}
}

void		ft_putmemory(t_memory ***q, int sum, char ***input, t_flag **flag)
{
	static int		d = 0;


	if (**q && (**q)->back && (**q)->back->back == NULL && sum == 183)
		ft_dop_history(q, input, flag, 1);
	if (**q && sum == 183 && (**q)->back && (**q)->back->back)
	{
		if (d != 0)
			**q = (**q)->back;
		ft_dop_history(q, input, flag, 1);
		if ((**q)->next == NULL)
			d = 1;
	}
	if (**q && sum == 184 && (**q)->next)
	{
		if ((**q)->next == NULL)
			d = 0;
		**q = (**q)->next;
		ft_dop_history(q, input, flag, 1);
	}
	else if (sum == 184)
	{
		ft_dop_history(q, input, flag, 2);
		d = 0;
	}
}
