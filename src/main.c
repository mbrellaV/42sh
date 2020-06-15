/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 09:38:59 by qmartina          #+#    #+#             */
/*   Updated: 2020/06/15 22:42:15 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int					main_cycle(t_readline *p, t_exectoken **start_token)
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
	ft_free_env_table();
	del_readline(p);
	ft_distruct_tree(*start_token);
	return (0);
}

static void			init_by_null(t_job **one, char **two, t_exectoken **three)
{
	*one = NULL;
	*two = NULL;
	*three = NULL;
}

void				ft_start_42sh(char **argv)
{
	t_readline		p;
	t_exectoken		*start_token;

	p.mod = 127;
	init_by_null(&globals()->g_f_job, argv, &start_token);
	if (argv[1] == NULL)
	{
		while (1)
			if (main_cycle(&p, &start_token) == -1)
				break;
	}
	else
	{
		do_42sh_builtin(argv);
	}
}

int					main(int argc, char **argv, char **env)
{
	globals()->g_his_d = 0;
	if (!(globals()->fd = ft_create_opened_fds()))
		exit(0);
	ft_alias();
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
	ft_start_42sh(argv);
	save_history(globals()->g_memory_head);
	exit(0);
}
