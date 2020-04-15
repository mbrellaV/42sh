/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 09:38:59 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/15 18:26:45 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

int		ft_whatis4(t_exectoken *tmp)
{
	if (tmp->file_args == NULL)
		return (-2);
	if (tmp->file_args[0] == NULL)
		return (-2);
	if (ft_strcmp(tmp->file_args[0], "exit") == 0 && tmp->file_args[1] == NULL)
		return (-1);
	if (ft_strcmp(tmp->file_args[0], "alias") == 0 || ft_strcmp(tmp->file_args[0], "unalias") == 0)
		ft_do_change_alias(tmp->file_args);
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
	else if (ft_strcmp(tmp->file_args[0], "set") == 0)
		ft_show_env(g_all_var);
	else if (ft_strcmp(tmp->file_args[0], "fg") == 0)
	{
		do_fg(tmp->file_args);
	}
	else if (ft_strcmp(tmp->file_args[0], "bg") == 0)
	{
		do_bg(tmp->file_args);
	}
	else if (ft_strcmp(tmp->file_args[0], "jobs") == 0)
		do_job_notification();
	else if (ft_strcmp(tmp->file_args[0], "echo") == 0)
		ft_echo(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "history") == 0)
		show_history(memory_head);
	else if (ft_strcmp(tmp->file_args[0], "env") == 0)
		ft_show_env(g_env);
	else if (ft_strcmp(tmp->file_args[0], "clear") == 0)
		ft_putstr_fd("\033[2J\033[H", 2);
	else if (ft_strcmp(tmp->file_args[0], "hash") == 0)
		print_hash();
	else if (!ft_strcmp(tmp->file_args[0], "type"))
		ft_type(tmp->file_args);
	else
		return (0);
	return (1);
}

int		ft_whatis2(t_process *tmp)
{
	if (tmp->file_args == NULL)
		return (-2);
	if (tmp->file_args[0] == NULL)
		return (-2);
	if (ft_strcmp(tmp->file_args[0], "exit") == 0 && tmp->file_args[1] == NULL)
		return (-1);
	if (ft_strcmp(tmp->file_args[0], "alias") == 0 || ft_strcmp(tmp->file_args[0], "unalias") == 0)
		ft_do_change_alias(tmp->file_args);
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
	else if (ft_strcmp(tmp->file_args[0], "set") == 0)
		ft_show_env(g_all_var);
	else if (ft_strcmp(tmp->file_args[0], "fg") == 0)
	{
		;
	}
	else if (ft_strcmp(tmp->file_args[0], "bg") == 0)
	{
		;
	}
	else if (ft_strcmp(tmp->file_args[0], "jobs") == 0)
		do_job_notification();
	else if (ft_strcmp(tmp->file_args[0], "echo") == 0)
		ft_echo(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "history") == 0)
		show_history(memory_head);
	else if (ft_strcmp(tmp->file_args[0], "env") == 0)
		ft_show_env(g_env);
	else if (ft_strcmp(tmp->file_args[0], "clear") == 0)
		ft_putstr_fd("\033[2J\033[H", 2);
	else if (ft_strcmp(tmp->file_args[0], "hash") == 0)
		print_hash();
	else if (!ft_strcmp(tmp->file_args[0], "type"))
		ft_type(tmp->file_args);
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

int		ft_ck_addline(t_readline *p)
{
	int 	f;

	f = 4242;
	while (f != 1)
	{
		p->index = do_zamena_slash(p->buff, p);
		while (ft_cheak_quote(p->buff) != 1)
			ft_add_intput_que(p, memory_head, 1);
		p->index = do_zamena_slash(p->buff, p);
		while (p->index > 0 && p->buff[p->index - 1] == '\\')
		{
			p->buff[p->index - 1] = 0;
			ft_add_intput_que(p, memory_head, 11);
		}
		p->index = do_zamena_slash(p->buff, p);
		f = ck_br(p->buff);
		if (f == 0)
			ft_add_intput_que(p, memory_head, 20);
		else if (f == -1 || f == -2)
		{
			ft_putstr_fd("Error \"()\"\n", 2);
			free(p->buff);
			return 0;
		}
	}
	return (1);
}

int				main_read(t_readline *p, t_exectoken **start_token)
{
	while (get_next_line(STDIN_FILENO, &p->buff))
	{
		*start_token = all_parse(p->buff);
		if (ft_main_what(*start_token) == -1)
			return (-1);
		free(p->buff);
		ft_distruct_tree(*start_token);
	}
	return (0);
}

int				main_cycle(t_readline *p, t_exectoken **start_token)
{
	init_shell();
	if (!set_input_mode())
	{
		ft_start_read(p);
		ft_read_8(p, memory_head, 0);
		write(2, "\n", 1);
		if (!ft_ck_addline(p))
			p->buff = ft_strnew(130000);
		reset_input_mode();
	}
	else
		if (main_read(p, start_token) == -1)
			return (-1);
	p->buff[0] != '\0' ? memory_head = ft_memory(memory_head, &(p->buff)) : memory_head;
	if ((*start_token = all_parse(p->buff)) == NULL)
	{
		del_readline(p);
		ft_distruct_tree(*start_token);
		return (0);
	}
	if (ft_main_what(*start_token) == -1)
		return (-1);
	del_readline(p);
	ft_distruct_tree(*start_token);
	return (0);
}

int				main(int argc, char **argv, char **env)
{
	t_readline	p;
	t_exectoken	*start_token;

	g_his_d = 0;
	p.mod = 127;
	ft_alias();
	f_job = NULL;
	argv[0] = NULL;
	start_token = NULL;
	ft_global_env(env, argc);
	memory_head = ft_head_memory();
	do_count_shell_lvl();
	hash_init();
	init_shell();
	if (isatty(0))
		ft_put_info();
	while (1)
		if (main_cycle(&p, &start_token) == -1)
			break ;
	save_history(memory_head);
	exit(0);
}