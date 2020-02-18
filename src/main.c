/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 09:38:59 by qmartina          #+#    #+#             */
/*   Updated: 2019/11/15 16:17:33 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

int			check_file_args(t_process *tmp)
{
	if (tmp->file_args == NULL)
		return (0);
	if (tmp->file_args[0] == NULL)
		return (0);
	if (ft_strcmp(tmp->file_args[0], "exit") == 0)
		return (-1);
	return (1);
}

int	ft_whatis2(t_process *tmp, t_memory *q)
{
	if (tmp->file_args == NULL)
		return (-2);
	if (tmp->file_args[0] == NULL)
		return (-2);
	if (ft_strcmp(tmp->file_args[0], "exit") == 0)
		return (-1);
	if (ft_strcmp(tmp->file_args[0], "alias") == 0 || ft_strcmp(tmp->file_args[0], "unalias") == 0)
		ft_do_change_alias(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "echo") == 0)
		ft_echo(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "cd") == 0)
		ft_cd(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "export") == 0)
		ft_do_export(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "unset") == 0 &&
			 tmp->file_args[1] != NULL)
    {
        unset_var(tmp->file_args[1], &g_env);
        unset_var(tmp->file_args[1], &g_all_var);
    }
	else if (ft_strcmp(tmp->file_args[0], "history") == 0)
		show_history(q);
	else if (ft_strcmp(tmp->file_args[0], "env") == 0)
		ft_show_env(g_env);
	else if (ft_strcmp(tmp->file_args[0], "set") == 0)
		ft_show_env(g_all_var);
	else if (ft_strcmp(tmp->file_args[0], "clear") == 0)
		ft_putstr_fd("\033[2J\033[H", 2);
	else if (ft_strcmp(tmp->file_args[0], "hash") == 0)
		print_hash();
	else if (!ft_strcmp(tmp->file_args[0], "type"))
		ft_type(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "fg") == 0)
		ft_fork_signal(SIGCONT);
	else
		return (0);
	return (1);
}

void	print_hash(void)
{
	t_hash			*hash;
	int				i;

	i = -1;
	while (++i < MAX_HASH)
	{
		if (g_hash[i] != NULL)
		{
			hash = g_hash[i];
			while (hash)
			{
				ft_putstr_fd(hash->key, 2);
				ft_putstr_fd("=", 2);
				ft_putstr_fd(hash->value, 2);
				if (hash->next)
					ft_putstr_fd("    ", 2);
				hash = hash->next;
			}
			ft_putstr_fd("\n", 2);
		}
	}
}

t_process	*create_process_list(t_exectoken *tmp)
{
	t_process	*proc;
	t_process	*fir;


	if (!(fir = ft_memalloc(sizeof(t_process))))
		ft_error_q(5);
	fir->file_args = tmp->file_args;
	if (check_file_args(fir) == 0)
		return (NULL);
	do_zam_str_with_tilda(tmp->file_args);
	fir->pid = -1;
	fir->completed = 0;
	fir->next = NULL;
	proc = fir;
	tmp = tmp->left;
	while (tmp)
	{
		if (!(proc->next = ft_memalloc(sizeof(t_process))))
			ft_error_q(5);
		proc->next->file_args = tmp->file_args;
		proc->next->pid = -1;
		proc->next->completed = 0;
		proc->next->next = NULL;
		proc = proc->next;
		tmp = tmp->left;
	}
	return (fir);
}

t_job	*create_job(t_exectoken *head)
{
	t_job	*new_job;

	if (head == NULL)
		return (NULL);
	if (!(new_job = ft_memalloc(sizeof(t_job))))
		ft_error_q(5);
	new_job->first_process = create_process_list(head);
	new_job->pgid = -1;
	new_job->command = NULL;
	return (new_job);
}

t_job	*turn_exectokens_to_jobs(t_exectoken *exec)
{
	t_job *tmp;
	//t_exectoken *tmp_exec;
	t_job *start_job;

	if (exec == NULL)
		return (NULL);
	//tmp = NULL;
	//start_job = NULL;
	tmp = create_job(exec);
	start_job = tmp;
	exec = exec->right;
	while (exec)
	{
		tmp->next = create_job(exec);
		tmp = tmp->next;
		exec = exec->right;
	}
	return (start_job);
}

int		ft_main_what(t_exectoken *tmp, t_memory *q)
{
	t_job	*jobs;
	int		sas;

	jobs = turn_exectokens_to_jobs(tmp);
	while (jobs)
	{
		//dprintf(2, "\nsas: |%s|", jobs->first_process->file_args[0]);
		sas = launch_job(jobs, 1, q);
		//dprintf(2, "\nsas: |%d|", sas);
		if (sas == -1)
			exit(0);
		jobs = jobs->next;
	}
	return (1);
}

int		launch_process (t_process *p, pid_t pgid, int infile, int outfile, int errfile,
				int foreground, t_memory *q)
{
	pid_t		pid;
	char		*rt;

	rt = NULL;
//	infile = 0;
//	outfile = 0;
//	errfile = 0;
	do_zam_str_with_tilda(p->file_args);
	dprintf(2, "\nkek: |%s|\n", p->file_args[0]);
	dprintf(2, "\nkek: |%d|\n", outfile);
	if (shell_is_interactive)
	{
		if (ft_whatis2(p, q) == 0)
			exit(0);
		if (!(rt = hash_get(p->file_args[0], 0)))
			exit(1);
		//dprintf(2, "\n\n\n\\n\n\n\n\n\\n\n\n\n\n\nn\n\nsasasasas\n\n\n\n\n\n");
		/* Put the process into the process group and give the process group
		   the terminal, if appropriate.
		   This has to be done both by the shell and in the individual
		   child processes because of potential race conditions.  */
		pid = getpid();
		if (pgid == 0) pgid = pid;
			setpgid (pid, pgid);
		if (foreground)
			tcsetpgrp (shell_terminal, pgid);

		/* Set the handling for job control signals back to the default.  */
		signal (SIGINT, SIG_DFL);
		signal (SIGQUIT, SIG_DFL);
		signal (SIGTSTP, SIG_DFL);
		signal (SIGTTIN, SIG_DFL);
		signal (SIGTTOU, SIG_DFL);
		signal (SIGCHLD, SIG_DFL);
	}
	/* Set the standard input/output channels of the new process.  */
	if (infile != STDIN_FILENO)
	{
		dup2 (infile, STDIN_FILENO);
		close (infile);
	}
	if (outfile != STDOUT_FILENO)
	{
		dup2 (outfile, STDOUT_FILENO);
		close (outfile);
	}
	if (errfile != STDERR_FILENO)
	{
		dup2 (errfile, STDERR_FILENO);
		close (errfile);
	}
	/* Exec the new process.  Make sure we exit.  */
	execve(rt, p->file_args, g_env);
	perror ("execve");
	exit(1);
}

int		launch_job (t_job *j, int foreground, t_memory *q)
{
	t_process	*p;
	pid_t		pid;
	int			dop;
	int			status;
	int mypipe[2], infile, outfile;

	j->stdout = 1;
	infile = j->stdin;
	//ft_file_create();
	//dprintf(2, "\ncheburek:");
	p = j->first_process;
	while(p)
	{
		/* Set up pipes, if necessary.  */
		if (p->next)
		{
			if (pipe (mypipe) < 0)
			{
				perror ("pipe");
				exit (1);
			}
			outfile = mypipe[1];
		}
		else
			outfile = j->stdout;
		//dprintf(2, "\nlol: |%s|, |%d|, |%d|, |%p|", p->file_args[0], getpid(), d, p);
		dop = ft_whatis2(p, q);
		if (dop == 1)
		{
			p = p->next;
			continue ;
		}
		if (dop == -2)
		{
			p = p->next;
			continue ;
		}
		if (dop == -1)
			return (-1);
		/* Fork the child processes.  */
		if ((pid = fork()) == -1)
			exit(1);
		else if (pid < 0)
			exit(1);
		else if (pid == 0)
			/* This is the child process.  */
		{
			launch_process (p, j->pgid, infile, outfile, j->stderr, foreground, q);
		}
		else
		{
			/* This is the parent process.  */
//			p->pid = pid;
//			if (shell_is_interactive)
//			{
//				if (!j->pgid)
//					j->pgid = pid;
//				setpgid (pid, j->pgid);
//			}
			waitpid(pid, &status, 0);
//			printf("%sstatus: %d%s\n", RED, status, RESET);
			if (WIFEXITED(status))
			{
				g_exit_code = WEXITSTATUS(status);
				dprintf(2, "%sExit status of the child was %d%s\n", YEL, g_exit_code, RESET);
			}
			p = p->next;
		}
		/* Clean up after pipes.  */
		if (infile != j->stdin)
			close (infile);
		if (outfile != j->stdout)
			close (outfile);
		infile = mypipe[0];
	}
	return (0);
}

int		main_cycle(t_readline *p, t_memory **head, t_exectoken **start_token)
{
	t_memory	*headin;
//	char 		buf;

	headin = *head;
//	printf("%d\n", fileno(stdin));
//	while (read(STDIN_FILENO, &buf, 1) > 0)
//		printf("%c", buf);
	init_shell();
	if (!set_input_mode())
	{
		ft_start_read(p);
		ft_read_8(p, headin, 0);
		write(2, "\n", 1);
		while (ft_cheak_quote(p->buff) != 1)
			ft_add_intput_que(p, headin);
		reset_input_mode();
	}
	else
	{
		while (get_next_line(STDIN_FILENO, &p->buff))
		{
//			write(1, "\n", 1);
//			ft_start_read(p);
//			ft_cleanstr(50, p);
			*start_token = all_parse(p->buff);
			if (ft_main_what(*start_token, headin) == -1)
				return (-1);
//			write(1, "\n", 1);
			free(p->buff);
			ft_distruct_tree(*start_token);
		}
		exit (0);
	}
	p->buff[0] != '\0' ? headin = ft_memory(headin, &(p->buff)) : headin;
	*start_token = all_parse(p->buff);
	if (ft_main_what(*start_token, headin) == -1)
		return (-1);
	del_readline(p);
	ft_distruct_tree(*start_token);
	*head = headin;
    print_hash();
	return (0);
}

int		main(int argc, char **argv, char **env)
{
	t_readline	p;
	t_memory	*head;
	t_exectoken	*start_token;

	g_his_d = 0;
	ft_alias();
	argv[0] = NULL;
	start_token = NULL;
	ft_global_env(env, argc);
	signal(SIGINT, ft_fork_signal);
	head = ft_head_memory();
	do_count_shell_lvl();
	hash_init();
	init_shell();
	if (isatty(0))
		ft_put_info();
	while (1)
		if (main_cycle(&p, &head, &start_token) == -1)
			break ;
	save_history(head);
	hash_clear();
	free(g_cp);
	ft_arrdel(g_env);
	del_readline(&p);
	return (ft_distruct_memory(head->next) &&
		ft_distruct_tree(start_token) ? 0 : 1);
}
