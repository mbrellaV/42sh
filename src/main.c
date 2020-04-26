/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 09:38:59 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/20 14:49:45 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

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
		p->buff[0] != '\0' ? globals()->g_memory_head = ft_memory(globals()->g_memory_head,
				&(p->buff)) : globals()->g_memory_head;
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
	if (globals()->all_opened_fds != NULL)
		free(globals()->all_opened_fds);
	if (!(globals()->all_opened_fds = ft_create_opened_fds()))
		return (-1);
	if (!set_input_mode())
	{
		ft_start_read(p);
		ft_read_8(p, globals()->g_memory_head, 0);
		write(2, "\n", 1);
		if (ft_ck_addline(p) < 1)
			p->buff = ft_strnew(130000);
		reset_input_mode();
	}
	else
		return (read_form_file(p));
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

	globals()->g_his_d = 0;
	p.mod = 127;
	ft_alias();
	globals()->g_f_job = NULL;
	argv[0] = NULL;
	start_token = NULL;
	ft_global_env(env, argc);
	globals()->g_memory_head = ft_head_memory();
	do_count_shell_lvl();
	hash_init();
	init_shell();
	if (isatty(0))
		ft_put_info();
	while (1)
		if (main_cycle(&p, &start_token) == -1)
			break ;
	save_history(globals()->g_memory_head);
	exit(0);
}
