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
		continue_job(get_last_job(), get_last_job()->first_process->foreground);
    else if (ft_strcmp(tmp->file_args[0], "jobs") == 0)
        do_job_notification();
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
	fir->foreground = 1;
	ft_show_env(tmp->file_args);
	if (tmp->file_opt)
		ft_show_env(tmp->file_opt);
	if (tmp->file_opt && ft_strcmp(tmp->file_opt[ft_env_len(tmp->file_opt) - 1], "&") == 0)
		fir->foreground = 0;
	fir->pid = -1;
	fir->completed = 0;
	fir->next = NULL;
	fir->completed = 0;
	fir->stopped = 0;
    fir->file_opt = tmp->file_opt;
	proc = fir;
	tmp = tmp->left;
	while (tmp)
	{
		if (!(proc->next = ft_memalloc(sizeof(t_process))))
			ft_error_q(5);
		proc->next->file_args = tmp->file_args;
		proc->next->pid = -1;
        proc->next->file_opt = tmp->file_opt;
		if (tmp->file_opt && ft_strcmp(tmp->file_opt[ft_env_len(tmp->file_opt) - 1], "&") == 0)
			fir->foreground = 0;
		proc->next->completed = 0;
		proc->next->completed = 0;
		proc->next->stopped = 0;
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
	new_job->stdinc = 0;
	new_job->stdoutc = 1;
	new_job->stderrc = 2;
	return (new_job);
}

t_job	*turn_exectokens_to_jobs(t_exectoken *exec)
{
	t_job *tmp;
	//t_exectoken *tmp_exec;
	t_job	*start_job;
	t_job	*dop;

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
	if (f_job != NULL)
	{
		dop = f_job;
		while (dop->next)
			dop = dop->next;
		dop->next = start_job;
	}
	else
		f_job = start_job;
	return (start_job);
}

int		ft_main_what(t_exectoken *tmp, t_memory *q)
{
	t_job	*jobs;
	int		sas;

	jobs = turn_exectokens_to_jobs(tmp);
	while (jobs)
	{
		dprintf(2, "\nrofl: |%d|\n", jobs->first_process->foreground);
		sas = launch_job(jobs, jobs->first_process->foreground, q);
		if (sas == -1)
			exit(0);
		jobs = jobs->next;
	}
	do_job_notification();
	return (1);
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
	f_job = NULL;
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
