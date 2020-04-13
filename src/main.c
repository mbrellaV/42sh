/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 09:38:59 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/13 20:04:22 by wstygg           ###   ########.fr       */
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

char	*do_reverse_zamena(char *str)
{
	int		i;
	char	*newstr;
	char	*tmp;

	i = 0;
	if (!(newstr = ft_memalloc(ft_strlen(str) * 2 + 1)))
		ft_error_q(15);
	while (str[i] != '\0')
	{
		if (str[i] < 0)
		{
			tmp = ft_strdup("\\ ");
			tmp[1] = -1 * str[i];
			ft_strcat(newstr, tmp);
			ft_strdel(&tmp);
		}
		else
		{
			tmp = ft_strdup(" ");
			tmp[0] = str[i];
			ft_strcat(newstr, tmp);
			ft_strdel(&tmp);
		}
		i++;
	}
	ft_strdel(&str);
	return (newstr);
}

int		ft_main_what(t_exectoken *tmp)
{
	t_job	*job;
	int		sas;
	char	*str_to_del;

	sas = 0;
	//take
    while (tmp)
	{
		if ((tmp->file_args == NULL) && (tmp->file_opt == NULL))
		{
			tmp = tmp->right;
			continue ;
		}

		if ((tmp->file_args != NULL && is_builtin(tmp->file_args[0]) == 0) || tmp->file_opt != NULL)
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
			if (f_job != NULL)
				get_last_job()->next = job;
			else
				f_job = job;
			sas = launch_job(job, job->foreground);
			ft_strdel(&str_to_del);
			//dprintf(2, "\n|%s|\n", tmp->file_args[0]);
		}
		else if (tmp->left == NULL && is_builtin(tmp->file_args[0]) == 1)
		{
			sas = ft_whatis4(tmp);
			//dprintf(2, "sas: |%d|", sas);
		}
		//sas = launch_job(jobs, jobs->first_process->foreground, q);
		if (sas == -1)
			return (-1);
		tmp = tmp->right;
//		ft_distruct_job(job);
	}
	do_job_del();
	return (1);
}

int	ck_br(const char *str)
{
	char	*s;
	int		i;
	int		k = 0;
	char	c;

	s = ft_strdup(str);
	i = -1;
	while (s[++i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			c = s[i];
			s[i] = 'F';
			while (s[++i] != c)
				s[i] = 'a';
			s[i] = 'F';
		}
	}
	if ((i = check_bracket(s)) && i != 1)
	{
		ft_strdel(&s);
		return (i);
	}
	while (1)
	{
		i = -1;
		while (s[++i])
			if (s[i] == '(')
				k = i;
		if (s[k] && s[k] == '(')
		{
			i = k;
			while (s[++i] && s[i] != ')')
				;
		}
		else
			break ;
		if (s[i] && s[i] == ')')
		{
			s[k] = 'A';
			s[i] = 'A';
		}
		else
		{
			ft_strdel(&s);
			return (0);
		}
	}
	i = -1;
	while (s[++i])
		if (s[i] == ')')
		{
			ft_strdel(&s);
			return (-2);
		}
	ft_strdel(&s);
	return(1);
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

int		main_cycle(t_readline *p, t_exectoken **start_token)
{
	//char	*str_for_del;
	init_shell();
	if (!set_input_mode())
	{
		ft_start_read(p);
		ft_read_8(p, memory_head, 0);
		write(2, "\n", 1);
		//str_for_del = p->buff;
		//p->buff = do_zamena_slash(p->buff);
		//ft_strdel(&str_for_del);
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
//			write(1, "\n", 1);
			free(p->buff);
			ft_distruct_tree(*start_token);
		}
	}
	p->buff[0] != '\0' ? memory_head = ft_memory(memory_head, &(p->buff)) : memory_head;
	//printf("|pars|%s\n", p->buff);
	if ((*start_token = all_parse(p->buff)) == NULL)
	{
		del_readline(p);
		ft_distruct_tree(*start_token);
		return (0);
	}
	if (ft_main_what(*start_token) == -1)
		return (-1);
	//ft_strdel(&p->buff);
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