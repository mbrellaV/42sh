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

int		ft_fd_flag(char **av, int *fd_in, int *infile, int *outfile)
{
	t_pipe	p;

	dprintf(2, "\n\nda1|%d|, |%d|", *infile, *outfile);
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
			{
				*infile = p.st;
				*outfile = p.fd;
			}
			else if (p.flag == 4)
				*fd_in = ft_heredoc(av[p.i]);
			p = (t_pipe){0, p.i, 1, p.fd, 0, p.j};
		}
	}
	dprintf(2, "\n\nda2|%d|, |%d|", *infile, *outfile);
	return (p.fd);
}
//
//void launch_job (job *j, int foreground)
//{
//	process *p;
//	pid_t pid;
//	int mypipe[2], infile, outfile;
//
//	infile = j->stdin;
//	for (p = j->first_process; p; p = p->next)
//	{
//		/* Set up pipes, if necessary.  */
//		if (p->next)
//		{
//			if (pipe (mypipe) < 0)
//			{
//				perror ("pipe");
//				exit (1);
//			}
//			outfile = mypipe[1];
//		}
//		else
//			outfile = j->stdout;
//
//		/* Fork the child processes.  */
//		pid = fork ();
//		if (pid == 0)
//			/* This is the child process.  */
//			launch_process (p, j->pgid, infile,
//							outfile, j->stderr, foreground);
//		else if (pid < 0)
//		{
//			/* The fork failed.  */
//			perror ("fork");
//			exit (1);
//		}
//		else
//		{
//			/* This is the parent process.  */
//			p->pid = pid;
//			if (shell_is_interactive)
//			{
//				if (!j->pgid)
//					j->pgid = pid;
//				setpgid (pid, j->pgid);
//			}
//		}
//	}
//}
//
//void	ft_infinit_pipe2(t_exectoken *head, t_memory *q)
//{
//	pid_t		pid;
//	char		*rt;
//	pid_t		gr_pid;
//	int			status;
//
//	ft_file_create(head);
//	gr_pid = 0;
//	dprintf(2, "getpgrp: %d\n", getpgrp());
//	while (head)
//	{
//		rt = hash_get(head->file_args[0], 0);
//		if ((pid = fork()) == -1)
//		{
//			ft_putstr_fd("ERROR pipe or fork", 2);
//			exit(1);
//		}
//		else if (pid == 0)
//		{
//			dprintf(2, "getpgrp1: %d\n", getpgrp());
//			if (ft_whatis2(head, q) == 0)
//				exit(0);
//			if (rt != NULL)
//				ft_fun_fork(rt, head->file_args, pid, 0);
//			exit(127);
//		}
//		else if (pid > 0)
//		{
//			if (gr_pid == 0)
//				gr_pid = pid;
//			setpgid (pid, gr_pid);
//			waitpid(pid, &status, 0);
//			if (WIFEXITED(status))
//			{
//				g_exit_code = WEXITSTATUS(status);
//				printf("%sExit status of the child was %d%s\n", YEL, g_exit_code, RESET);
//			}
//			head = (head)->left;
//		}
//	}
//	while (tcgetpgrp(shell_terminal) != (shell_pgid = getpgrp ()))
//		kill(- shell_pgid, SIGTTIN);
//}
