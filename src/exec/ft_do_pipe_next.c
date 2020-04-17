/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_pipe_next.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 13:29:33 by wstygg            #+#    #+#             */
/*   Updated: 2020/04/14 13:32:23 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

void	ft_redirect_error(int marker, char *dopline)
{
	if (marker == 10)
	{
		ft_printf(SHELL_NAME": %s: Bad file descriptor", dopline);
		ft_strdel(&dopline);
	}
	if (marker == 9)
	{
		ft_printf(SHELL_NAME": %s: ambiguous redirect", dopline);
	}
}

int		ft_what_flag(char *opt)
{
	int flag;

	flag = 0;
	ft_strcmp(opt, ">") == 0 ? flag = 1 : flag;
	ft_strcmp(opt, ">>") == 0 ? flag = 2 : flag;
	ft_strcmp(opt, "<") == 0 ? flag = 3 : flag;
	ft_strcmp(opt, "<<") == 0 ? flag = 4 : flag;
	ft_strcmp(opt, ">&") == 0 ? flag = 6 : flag;
	ft_strcmp(opt, "<&") == 0 ? flag = 6 : flag;
	return (flag);
}

int		ft_open_flag(char *opt, t_pipe *p)
{
	if (p->flag == 1 || p->flag == 2 || p->flag == 6)
		*p->outfile = open(opt, O_CREAT | O_RDWR | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
				S_IROTH | S_IWOTH);
	else if (p->flag == 3)
		*p->infile = open(opt, O_RDONLY);
	//dprintf(2, "\n|%d|", *p->infile);
	if (((p->flag == 1 || p->flag == 6 || p->flag == 2) && *p->outfile <= 0) ||
		(p->flag == 3 && *p->infile <= 0))
	{
		ft_putstr_fd("42sh: open fd ERROR ", 2);
		ft_putendl_fd(opt, 2);
		return (-1);
	}
	return (1);
}

int		ft_heredoc(char *tmp)
{
	int			j;
	int			f[2];
	t_readline	h;

	pipe(f);
	j = 0;
	h.mod = -100;
	ft_start_read(&h);
	set_input_mode();
	while (ft_strcmp(h.buff, tmp) != 0 && ft_strcmp(h.buff, "exit") != 0)
	{
		j != 0 ? ft_putendl_fd(h.buff, f[1]) : NULL;
		h.mod = 2;
		del_readline(&h);
		ft_start_read(&h);
		ft_read_8(&h, NULL, 2);
		write(2, "\n", 1);
		j++;
	}
	close(f[1]);
	del_readline(&h);
	reset_input_mode();
	return (f[0]);
}

void	ft_redirect_one(int old_file_fd, int new_infile_fd)
{
	if (old_file_fd != new_infile_fd)
	{
		dup2(old_file_fd, new_infile_fd);
		close(old_file_fd);
	}
}
