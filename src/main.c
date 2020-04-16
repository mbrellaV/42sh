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
	int				f;

	f = 4242;
	while (f != 1)
	{
		p->index = do_zamena_slash(p->buff, p);
		while (ft_cheak_quote(p->buff) != 1)
			ft_add_intput_que(p, g_memory_head, 1);
		p->index = do_zamena_slash(p->buff, p);
		while (p->index > 0 && p->buff[p->index - 1] == '\\')
		{
			p->buff[p->index - 1] = 0;
			ft_add_intput_que(p, g_memory_head, 11);
		}
		p->index = do_zamena_slash(p->buff, p);
		if ((f = ck_br(p->buff)) == 0)
			ft_add_intput_que(p, g_memory_head, 20);
		else if (f == -1 || f == -2)
		{
			ft_putstr_fd("Error \"()\"\n", 2);
			free(p->buff);
			return (0);
		}
	}
	return (1);
}

int		main_read(t_readline *p, t_exectoken **start_token)
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
	else if (main_read(p, start_token) == -1)
		return (-1);
	p->buff[0] != '\0' ? g_memory_head = ft_memory(g_memory_head,
			&(p->buff)) : g_memory_head;
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
	t_readline		p;
	t_exectoken		*start_token;

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
