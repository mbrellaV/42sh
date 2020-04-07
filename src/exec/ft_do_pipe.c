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

int		ft_fd_flag(char **av, int *infile, int *outfile, int *errfile)
{
	t_pipe	p;

	//dprintf(2, "\n\nda1|%d|, |%d|", *infile, *outfile);
	p = (t_pipe){0, 0, 1, 0, 0, 0, infile, outfile, errfile};
	while (p.i < ft_env_len(av) && av[(p.i)] != NULL)
	{
		if (av[p.i][0] >= '0' && av[p.i][0] <= '9')
		{
			p.flag = ft_what_flag(&p, av[p.i + 1]);
			if (p.flag != 6 && p.flag != 4)
			{
				do_redir_into_file(&p, av[p.i + 2], ft_atoi(av[p.i]));
			}
			else if (p.flag == 4)
				ft_heredoc(av[p.i + 2]);
			else
			{
				p.st = ft_atoi(av[p.i]);
				p.fd = ft_atoi(av[p.i + 2]);
//				if (ft_strcmp(av[p.i + 1], ">&") == 0 && isword(av[p.i + 2][0]) == 1)
//				{
//					do_redir_into_file(&p, av[p.i + 2], p.st);
//					dup2(, p.st);
//				}
//				if (ft_strcmp(av[p.i + 1], "<&") == 0 && isword(av[p.i + 2][0]) == 1)
//				{
//					do_redir_into_file(&p, av[p.i + 2], p.st);
//					dup2(2, p.st);
//				}
				if (ft_strcmp(av[p.i + 1], "<&") == 0)
					dup2(p.st, p.fd);
				else
					dup2(p.fd, p.st);
			}
			p.i += 3;
		}
		else
			break ;
		p = (t_pipe){0, p.i, 1, 0, 0, 0, infile, outfile, errfile};
	}
	//dprintf(2, "\n\nda2|%d|, |%d|", *infile, *outfile);
	return (p.fd);
}


//int		ft_fd_flag(char **av, int *fd_in, int *infile, int *outfile)
//{
//	t_pipe	p;
//
//	//dprintf(2, "\n\nda1|%d|, |%d|", *infile, *outfile);
//	p = (t_pipe){0, -1, 1, 0, 0, 0};
//	while (av[++(p.i)])
//	{
//		if (p.b == 0 && av[p.i][0] >= '0' && av[p.i][0] <= '9')
//			p.st = ft_atoi(av[p.i]);
//		else if ((av[p.i][0] == '>' || av[p.i][0] == '<' || av[p.i][0] == '&'))
//			p.flag = ft_what_flag(av[p.i], &(p.b));
//		else if (p.b == 1 && p.flag != 0)
//		{
//			ft_open_flag(av, p, &fd_in, &p.fd);
//			dprintf(2, "\nsas: |%d, %d, %d|\n", p.st, p.fd, p.flag);
//			if (*fd_in < 0)
//				return (-1);
//			if (p.flag == 1 || p.flag == 2)
//			{
//				//*infile = p.st;
//				//*outfile = p.fd;
//				dup2(p.fd, p.st);
//			}
//			else if (p.flag == 4)
//				*fd_in = ft_heredoc(av[p.i]);
//			else if (p.flag == 6)
//			{
//				dup2(p.fd, p.st);
//			}
//			p = (t_pipe){0, p.i, 1, p.fd, 0, p.j};
//		}
//	}
//	//dprintf(2, "\n\nda2|%d|, |%d|", *infile, *outfile);
//	return (p.fd);
//}
