/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 09:38:59 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/12 15:40:48 by pro              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

int		main_cycle(t_readline *p, t_exectoken **start_token)
{
	if (!set_input_mode())
	{
		ft_start_read(p);
		ft_read_8(p, globals()->g_memory_head, 0);
		write(2, "\n", 1);
		if (ft_ck_addline(p) < 1)
			p->buff = ft_strnew(130000);
		reset_input_mode();
	}
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
	if (!(globals()->fd = ft_create_opened_fds()))
		exit(0);
	p.mod = 127;
	ft_alias();
	globals()->g_f_job = NULL;
	argv[0] = NULL;
	start_token = NULL;
	ft_global_env(env, argc);
	globals()->g_memory_head = ft_head_memory();
	do_count_shell_lvl();
	init_shell_builtins();
	hash_init();
	init_shell();
	if (isatty(0) && isatty(1) && isatty(2))
		ft_put_info();
	else
		ft_error_q(3);
	while (1)
		if (main_cycle(&p, &start_token) == -1)
			break ;
	save_history(globals()->g_memory_head);
	exit(0);
}
