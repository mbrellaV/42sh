/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 02:59:46 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/13 20:04:23 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"
#include <stdio.h>

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

void	ft_open_flag(char *opt, t_pipe *p)
{
	if (p->flag == 1)
		*p->outfile = open(opt, O_CREAT | O_RDWR | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
				S_IROTH | S_IWOTH);
	else if (p->flag == 2)
		*p->outfile = open(opt, O_CREAT | O_RDWR | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
				S_IROTH | S_IWOTH);
	else if (p->flag == 6)
		*p->outfile = open(opt, O_CREAT | O_RDWR | O_TRUNC,
						   S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
						   S_IROTH | S_IWOTH);
	else if (p->flag == 3)
		*p->infile = open(opt, O_RDONLY);
	if ((p->flag == 1 || p->flag == 6 || p->flag == 2) && *p->outfile <= 0)
	{
		ft_putstr_fd("42sh: open fd ERROR ", 2);
		ft_putendl_fd(opt, 2);
		p->flag = 0;
	}
	else if (p->flag == 3 && *p->infile <= 0)
	{
		ft_putstr_fd("42sh: open fd ERROR ", 2);
		ft_putendl_fd(opt, 2);
	}
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

void	ft_redirect(t_pipe *p, int new_infile_fd, int new_outfile_fd)
{
	if (*p->infile != new_infile_fd)
	{
		ft_redirect_one(*p->infile, new_infile_fd);
	}
	if (*p->outfile != new_outfile_fd)
	{
		ft_redirect_one(*p->outfile, new_outfile_fd);
	}
	if (*p->errfile != STDERR_FILENO)
	{
		dup2 (*p->errfile, STDERR_FILENO);
		close (*p->errfile);
	}
}

void	do_redir_into_file(t_pipe *p, char *file, int new_infile_fd, int new_outfile_fd)
{
	ft_open_flag(file, p);
	ft_redirect(p, new_infile_fd, new_outfile_fd);
}

int		return_with_close(int *opened_fds, int int_to_return)
{
	free(opened_fds);
	return (int_to_return);
}

int		ft_fd_flag(char **av, int *infile, int *outfile, int *errfile)
{
	t_pipe	p;
	int		*opened_fds;

	if (!(opened_fds = ft_create_opened_fds()))
		return (-1);
	p = (t_pipe){0, 0, 1, 0, 0, 0, infile, outfile, errfile};
	while (p.i < ft_env_len(av) && av[(p.i)] != NULL)
	{
		if (av[p.i][0] >= '0' && av[p.i][0] <= '9')
		{
			p.st = ft_atoi(av[p.i]);
			p.fd = ft_atoi(av[p.i + 2]);
			p.flag = ft_what_flag(av[p.i + 1]);
			if (p.flag != 6 && p.flag != 4)
			{
				//dprintf(2, "\nsas: |%d, %d|\n", p.flag, p.st);
				if (p.flag == 1 || p.flag == 2)
				{
					ft_open_flag(av[p.i + 2], &p);
					ft_redirect_one(*p.outfile, p.st);
					if (ft_find_in_fds(opened_fds, p.st) == 0)
						ft_add_to_fds(opened_fds, p.st);
				}
				if (p.flag == 3)
				{
					ft_open_flag(av[p.i + 2], &p);
					ft_redirect_one(*p.infile, p.st);
				}
			}
			else if (p.flag == 4)
			{
				*p.infile = ft_heredoc(av[p.i + 2]);
				ft_redirect(&p, STDIN_FILENO, STDOUT_FILENO);
			}
			else
			{
				if (ft_strcmp(av[p.i + 1], ">&") == 0 && ft_strcmp(av[p.i + 2], "-") == 0)
				{
					ft_remove_from_fds(opened_fds, p.st);
					close(p.st);
				}
				else if (ft_strcmp(av[p.i + 1], "<&") == 0 && ft_strcmp(av[p.i + 2], "-") == 0)
				{
					ft_remove_from_fds(opened_fds, p.st);
					close(p.st);
				}
				else if (ft_strcmp(av[p.i + 1], "<&") == 0)
				{
					if (ft_find_in_fds(opened_fds, p.fd) == 0)
					{
						ft_redirect_error(10, ft_itoa(p.fd));
						return (return_with_close(opened_fds, -1));
					}
					if (isword(av[p.i + 2][0]) && !ft_isdigit(av[p.i + 2][0]))
					{
						ft_redirect_error(9, av[p.i + 2]);
						return (return_with_close(opened_fds, -1));
					}
					dup2(p.st, p.fd);
				}
				else
				{
					if (isword(av[p.i + 2][0]) && !ft_isdigit(av[p.i + 2][0]))
					{
						do_redir_into_file(&p, av[p.i + 2], STDIN_FILENO, p.st);
						if (ft_find_in_fds(opened_fds, p.st) == 0)
						{
							ft_add_to_fds(opened_fds, p.st);
						}
						dup2(STDOUT_FILENO, STDERR_FILENO);
					}
					else if (ft_find_in_fds(opened_fds, p.st) == 0)
					{
						ft_redirect_error(10, ft_itoa(p.fd));
						return (return_with_close(opened_fds, -1));
					}
					else
						dup2(p.fd, p.st);
				}
			}
			p.i += 3;
		}
		else
			break ;
		p = (t_pipe){0, p.i, 1, 0, 0, 0, infile, outfile, errfile};
	}
	return (return_with_close(opened_fds, p.fd));
}
