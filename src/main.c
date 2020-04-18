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

void	update_history(t_readline *p)
{
	int		i;
	char	*second_str;
	char	*str_for_del;

	i = 0;
	if (p->buff[0] == '\0')
		return ;
	if (!(second_str = ft_strnew(130000)))
		ft_error_q(2);
	while (p->buff[i] && p->buff[i] != '\n')
		i++;
	ft_strcat(second_str, &p->buff[i]);
	str_for_del = g_memory_head->inp;
	g_memory_head->inp = ft_strjoin(g_memory_head->inp, second_str);
	ft_strdel(&str_for_del);
	ft_strdel(&second_str);
}

int		read_form_file(t_readline *p)
{
	t_exectoken *start_token;

	while (get_next_line(STDIN_FILENO, &p->buff))
	{
		if ((start_token = all_parse(p->buff)) == NULL)
		{
			del_readline(p);
			ft_distruct_tree(start_token);
			return (0);
		}
		p->buff[0] != '\0' ? g_memory_head = ft_memory(g_memory_head,
				&(p->buff)) : g_memory_head;
		if (ft_main_what(start_token) == -1)
			return (-1);
		del_readline(p);
		ft_distruct_tree(start_token);
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
	else
		return (read_form_file(p));
	update_history(p);
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
