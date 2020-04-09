/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 02:59:46 by qmartina          #+#    #+#             */
/*   Updated: 2019/11/26 02:59:47 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"
#include <stdio.h>
#include <errno.h>

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

int		ft_what_flag(t_pipe *p, char *opt)
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
	//dprintf(2, "\n\nda3|%d|, |%d|", *p->infile, *p->outfile);
	if ((p->flag == 1 || p->flag == 6 || p->flag == 2) && *p->outfile <= 0)
	{
		ft_putstr_fd("21sh: open fd ERROR ", 2);
		ft_putendl_fd(opt, 2);
		p->flag = 0;
	}
	else if (p->flag == 3 && *p->infile <= 0)
	{
		ft_putstr_fd("21sh: open fd ERROR ", 2);
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

void	do_redir_into_file(t_pipe *p, char *file, int newfd)
{
	//p->st = ft_atoi(av[p->i]);
	ft_open_flag(file, p);
	if (*p->infile != STDIN_FILENO)
	{
		//dprintf(2, "\ninfile: |%d|\n", *p.infile);
		dup2 (*p->infile, newfd);
		close (*p->infile);
	}
	if (*p->outfile != STDOUT_FILENO)
	{
		//dprintf(2, "\noutfile: |%d|\n", *p.outfile);
		dup2(*p->outfile, newfd);
		close (*p->outfile);
		//dprintf(1, "\noutfilef: |%d|\n", outfile);

	}
	if (*p->errfile != STDERR_FILENO)
	{
		//dprintf(2, "\nerrfile: |%d|\n", *p.errfile);
		dup2 (*p->errfile, STDERR_FILENO);
		close (*p->errfile);
	}
}

int		ft_find_in_fds(int *opened_fds, int fd_to_find)
{
	if (opened_fds == NULL)
		return (-1);
	if (opened_fds[fd_to_find] == 1)
		return (1);
	return (0);
}

int		ft_add_to_fds(int *opened_fds, int fd_to_add)
{
	if (opened_fds == NULL)
		return (-1);
	opened_fds[fd_to_add] = 1;
	return (1);
}

int		ft_remove_from_fds(int *opened_fds, int fd_to_remove)
{
	if (opened_fds == NULL)
		return (-1);
	opened_fds[fd_to_remove] = -1;
	return (1);
}

int		*ft_create_opened_fds()
{
	int *opened_fds;

	if (!(opened_fds = (int *)ft_memalloc(sizeof(int) * 10)))
		return (NULL);
	opened_fds[0] = 1;
	opened_fds[1] = 1;
	opened_fds[2] = 1;
	opened_fds[3] = -1;
	opened_fds[4] = -1;
	opened_fds[5] = -1;
	opened_fds[6] = -1;
	opened_fds[7] = -1;
	opened_fds[8] = -1;
	opened_fds[9] = -1;
	return (opened_fds);
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

	//dprintf(2, "\n\nda1|%d|, |%d|", *infile, *outfile);
	if (!(opened_fds = ft_create_opened_fds()))
		return (-1);
	p = (t_pipe){0, 0, 1, 0, 0, 0, infile, outfile, errfile};
	while (p.i < ft_env_len(av) && av[(p.i)] != NULL)
	{
		if (av[p.i][0] >= '0' && av[p.i][0] <= '9')
		{
			p.st = ft_atoi(av[p.i]);
			p.fd = ft_atoi(av[p.i + 2]);
			p.flag = ft_what_flag(&p, av[p.i + 1]);
			if (p.flag != 6 && p.flag != 4)
			{
				do_redir_into_file(&p, av[p.i + 2], p.st);
				if (ft_find_in_fds(opened_fds, p.st) == 0)
				{
					ft_add_to_fds(opened_fds, p.st);
				}
			}
			else if (p.flag == 4)
				ft_heredoc(av[p.i + 2]);
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
					dup2(p.st, p.fd);
				}
				else if (ft_strcmp(av[p.i + 1], "<&") == 0)
				{
					if (ft_find_in_fds(opened_fds, p.fd) == 0)
					{
						ft_redirect_error(10, ft_itoa(p.fd));
						return (return_with_close(opened_fds, -1));
					}
					if (isword(av[p.i + 2][0]))
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
						do_redir_into_file(&p, av[p.i + 2], p.st);
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
	//dprintf(2, "\n\nda2|%d|, |%d|", *infile, *outfile);
	return (return_with_close(opened_fds, p.fd));
}
