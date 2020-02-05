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

int		ft_what_flag(char *str, int *b)
{
	int flag;

	flag = 0;
	ft_strcmp(str, ">") == 0 ? flag = 1 : flag;
	ft_strcmp(str, ">>") == 0 ? flag = 2 : flag;
	ft_strcmp(str, "<") == 0 ? flag = 3 : flag;
	ft_strcmp(str, "<<") == 0 ? flag = 4 : flag;
	ft_strcmp(str, ">&") == 0 ? flag = 6 : flag;
	ft_strcmp(str, "&>") == 0 ? flag = 6 : flag;
	*b = 1;
	return (flag);
}

void	ft_open_flag(char *str, int *flag, int **ff, int *fd)
{
	if (*flag == 1 || *flag == 6)
		*fd = open(str, O_CREAT | O_RDWR | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
				S_IROTH | S_IWOTH);
	else if (*flag == 2)
		*fd = open(str, O_CREAT | O_RDWR | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
				S_IROTH | S_IWOTH);
	else if (*flag == 3)
		**ff = open(str, O_RDONLY);
	if ((*flag == 1 || *flag == 6 || *flag == 2) && *fd <= 0)
	{
		ft_putstr_fd("21sh: open fd ERROR ", 2);
		ft_putendl_fd(str, 2);
		*flag = 0;
	}
	else if (*flag == 3 && **ff <= 0)
	{
		ft_putstr_fd("21sh: open fd ERROR ", 2);
		ft_putendl_fd(str, 2);
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

int		ft_fd_flag(char **av, int *fd_in)
{
	t_pipe	p;

	p = (t_pipe){0, -1, 1, 0, 0, 0};
	while (av[++(p.i)])
	{
		if (p.b == 0 && av[p.i][0] >= '0' && av[p.i][0] <= '9')
			p.st = ft_atoi(av[p.i]);
		else if ((av[p.i][0] == '>' || av[p.i][0] == '<' || av[p.i][0] == '&'))
			p.flag = ft_what_flag(av[p.i], &(p.b));
		else if (p.b == 1 && p.flag != 0)
		{
			ft_open_flag(av[p.i], &(p.flag), &fd_in, &p.fd);
			if (p.flag == 1 || p.flag == 2)
				dup2(p.fd, p.st);
			else if (p.flag == 6)
			{
				dup2(p.fd, 1);
				dup2(p.fd, 2);
			}
			else if (p.flag == 4)
				*fd_in = ft_heredoc(av[p.i]);
			p = (t_pipe){0, p.i, 1, p.fd, 0, p.j};
		}
	}
	return (p.fd);
}

void	ft_infinit_pipe(t_exectoken *head)
{
	int			p[2];
	pid_t		pid;
	int			fd_in;
	char		*rt;

	fd_in = 0;
	ft_file_create(head);
	while (head)
	{
		rt = hash_get(head->file_args[0]);
		if (pipe(p) == -1 || (pid = fork()) == -1)
			exit(1);
		else if (pid == 0)
		{
			if (head->left != NULL)
				ft_norm_pipe(p[1], &fd_in, -404, NULL);
			if (head->file_opt)
				ft_fd_flag(head->file_opt, &fd_in);
			if (ft_norm_pipe(-404, &fd_in, p[0], NULL) && rt != NULL)
				ft_fun_fork(rt, head->file_args, pid);
			exit(0);
		}
		else
			ft_norm_pipe(p[1], &fd_in, p[0], &head);
	}
}
