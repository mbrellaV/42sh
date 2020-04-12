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

int		ft_main_what(t_exectoken *tmp)
{
	t_job	*job;
	int		sas;
	char	*str_to_del;

	sas = 0;
	while (tmp)
	{
		if ((tmp->file_args == NULL) && (tmp->file_opt == NULL))
		{
			tmp = tmp->right;
			continue ;
		}
		if ((tmp->file_args != NULL && is_builtin(tmp->file_args[0]) == 0) ||
			tmp->file_opt != NULL)
		{
			str_to_del = ft_get_var("?", g_all_var);
			if (tmp->should_wait_and == 1 && ft_atoi(str_to_del) > 0)
			{
				ft_strdel(&str_to_del);
				tmp = tmp->right;
				continue ;
			}
			else if (tmp->should_wait_or == 1 && ft_atoi(str_to_del) == 0)
			{
				ft_strdel(&str_to_del);
				tmp = tmp->right;
				continue ;
			}
			job = create_job(tmp);
			if (g_f_job != NULL)
				get_last_job()->next = job;
			else
				g_f_job = job;
			sas = launch_job(job, job->foreground);
			ft_strdel(&str_to_del);
		}
		else if (tmp->left == NULL && is_builtin(tmp->file_args[0]) == 1)
			sas = ft_whatis4(tmp);
		if (sas == -1)
			return (-1);
		tmp = tmp->right;
	}
	do_job_del();
	return (1);
}

int		main_cycle(t_readline *p, t_exectoken **start_token)
{
	init_shell();
	if (!set_input_mode())
	{
		ft_start_read(p);
		ft_read_8(p, g_memory_head, 0);
		write(2, "\n", 1);
		if (!ft_ck_addline(p))
			p->buff = ft_strnew(130000);
		reset_input_mode();
	}
	else
	{
		while (get_next_line(STDIN_FILENO, &p->buff))
		{
			*start_token = all_parse(p->buff);
			if (ft_main_what(*start_token) == -1)
				return (-1);
			free(p->buff);
			ft_distruct_tree(*start_token);
		}
	}
	p->buff[0] != '\0' ? g_memory_head = ft_memory(g_memory_head, &(p->buff)) : g_memory_head;
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

int		main(int argc, char **argv, char **env)
{
	t_readline	p;
	t_exectoken	*start_token;

	g_his_d = 0;
	p.mod = 127;
	ft_alias();
	g_f_job = NULL;
	argv[0] = NULL;
	start_token = NULL;
	ft_global_env(env, argc);
	g_memory_head = ft_head_memory();
	do_count_shell_lvl();
	hash_init();
	init_shell();
	if (isatty(0))
		ft_put_info();
	while (1)
		if (main_cycle(&p, &start_token) == -1)
			break ;
	save_history(g_memory_head);
	exit(0);
}