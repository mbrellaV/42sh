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

int		ft_whatis(t_exectoken *tmp, t_memory *q)
{
	if (tmp->file_args == NULL)
		return (ft_error_args(tmp));
	if (tmp->file_args[0] == NULL)
		return (0);
	do_zam_str_with_tilda(tmp->file_args);
	if (ft_strcmp(tmp->file_args[0], "echo") == 0)
		ft_echo(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "set") == 0)
		ft_show_env(g_all_var);
	else if (ft_strcmp(tmp->file_args[0], "cd") == 0)
		ft_cd(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "export") == 0)
		ft_do_export(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "unset") == 0 && tmp->file_args[1] != NULL)
    {
        unset_var(tmp->file_args[1], &g_env);
        unset_var(tmp->file_args[1], &g_all_var);
    }
	else if (ft_strcmp(tmp->file_args[0], "unexport") == 0 && tmp->file_args[1] != NULL)
		unset_var(tmp->file_args[1], &g_env);
	else if (ft_strcmp(tmp->file_args[0], "history") == 0)
		show_history(q);
	else if (ft_strcmp(tmp->file_args[0], "env") == 0)
		ft_show_env(g_env);
	else if (ft_strstr(tmp->file_args[0], "alias") != NULL)
		ft_do_change_alias(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "exit") == 0)
		return (-1);
	else if (ft_strcmp(tmp->file_args[0], "clear") == 0)
		ft_putstr_fd("\033[2J\033[H", 2);
	else if (ft_strcmp(tmp->file_args[0], "hash") == 0)
		print_hash();
	else
		ft_infinit_pipe(tmp);
	return (1);
}

void				print_hash()
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
				dprintf(2, "hash - [%i]; key - [%s];  value - [%s]    ", str_to_hash(hash->key), hash->key, hash->value);
				hash = hash->next;
			}
			ft_printf("\n");
		}
	}
}

int		ft_main_what(t_exectoken *tmp, t_memory *q)
{
	while (tmp)
	{
		if (ft_whatis(tmp, q) == -1)
			return (-1);
		tmp = tmp->right;
	}
	return (1);
}

int		save_history(t_memory *q)
{
	int		fd;

	fd = open("history/hist.txt",  O_TRUNC);
	close(fd);
	fd = open("history/hist.txt",  O_RDWR);
	while (q->back->back != NULL)
		q = q->back;
	while (q != NULL)
	{
		write(fd, q->inp, ft_strlen(q->inp));
		ft_putchar_fd(-100, fd);
		q = q->next;
	}
	ft_putchar_fd(0, fd);
	close(fd);
	return (0);
}

void	do_count_shell_lvl()
{
	char	*dop;
	char	*dop1;

	if (!(dop = ft_get_var("SHLVL", g_env)))
		return ;
	dop1 = ft_itoa(ft_atoi(dop) + 1);
	set_new_var("SHLVL", dop1, &g_env);
	ft_strdel(&dop);
	ft_strdel(&dop1);
}

int		main(int argc, char **argv, char **env)
{
	t_readline	p;
	t_memory	*head;
	t_exectoken	*start_token;

	argv[0] = NULL;
	ft_alias();
	ft_global_env(env, argc);
	signal(SIGINT, ft_fork_signal);
	head = ft_head_memory();
	do_count_shell_lvl();
	hash_init();
	while (1)
	{
		set_input_mode();
		atexit(reset_input_mode);
		ft_start_read(&p);
		ft_read_8(&p, head, 0);
		write(2, "\n", 1);
		while (ft_cheak_quote(p.buff) != 1)
			ft_add_intput_que(&p, head);
		reset_input_mode();
		p.buff[0] != '\0' ? head = ft_memory(head, &p.buff) : head;
		start_token = all_parse(p.buff);
		if (ft_main_what(start_token, head) == -1)
			break ;
		del_readline(&p);
		ft_distruct_tree(start_token);
	}
	save_history(head);
	hash_clear();
	free(g_cp);
	ft_arrdel(g_alias);
	ft_arrdel(g_env);
	ft_arrdel(g_all_var);
	return (ft_distruct_memory(head) && ft_distruct_tree(start_token) &&
		del_readline(&p) ? 0 : 1);
}
