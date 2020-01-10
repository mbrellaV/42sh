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
	if (ft_do_zam_eval(tmp->file_args) == -1)
		ft_error_args(tmp);
	if (do_zam_ravno(tmp->file_args) == -1)
		ft_error_args(tmp);
	if (ft_do_zam_alias(tmp->file_args) == -1)
		ft_error_args(tmp);
	if (tmp->file_args[0] == NULL)
		return (0);
	if (ft_strcmp(tmp->file_args[0], "echo") == 0)
		ft_echo(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "set") == 0)
		ft_show_env(g_all_var);
	else if (ft_strcmp(tmp->file_args[0], "cd") == 0)
		ft_cd(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "export") == 0)
		ft_do_export(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "unset") == 0 && tmp->file_args[1] != NULL)
		unset_var(tmp->file_args[1], &g_all_var);
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
		tputs(tgetstr("cl", NULL), 1, ft_c);
	else
		ft_infinit_pipe(tmp);
	return (1);
}

int		ft_main_norm(int flag)
{
	if (flag == 1)
	{
		ft_putstr_fd("quote> ", 2);
		return (ft_strlen("quote> "));
	}
	else if (flag == 0)
		return (ft_put_info());
	else if (flag == 2)
	{
		ft_putstr_fd("heredoc> ", 2);
		return (ft_strlen("heredoc> "));
	}
	return (0);
}

int		ft_cheak_quote(char *input)
{
	int		k;
	char	c;

	k = -1;
	while (input[++k])
	{
		if (input[k] == '\'' || input[k] == '\"')
		{
			c = input[k];
			while (input[++k] && input[k] != c)
				;
			if (input[k] == '\0')
				return (-1);
		}
	}
	return (1);
}

void	ft_add_intput_que(char **input, t_memory *head)
{
	char	*tmp;
	char	*t;

	t = *input;
	*input = ft_strjoinch(t, '\n');
	free(t);
	tmp = ft_read_8(ft_main_norm(1), head, 1);
	write(2, "\n", 1);
	t = *input;
	*input = ft_strjoin(t, tmp);
	free(t);
	free(tmp);
}

int		main(int argc, char **argv, char **env)
{
	char		*input;
	t_memory	*head;
	t_exectoken	*start_token;

	argv[0] = NULL;
	ft_alias();
	ft_global_env(env, argc);
	signal(SIGINT, ft_fork_signal);
	head = ft_head_memory();
	//set_new_var(ft_strdup("?"), ft_itoa(0));
	while (1)
	{
		set_input_mode();
		atexit(reset_input_mode);
		input = ft_read_8(ft_main_norm(0), head, 0);
		write(2, "\n", 1);
		while (ft_cheak_quote(input) != 1)
			ft_add_intput_que(&input, head);
		reset_input_mode();
		input[0] != '\0' ? head = ft_memory(head, input) : head;
		//input = ft_strdup("alias ddd fff ; exit");
		start_token = all_parse(input);
		if (ft_main_what(start_token, head) == -1)
			break ;
		free(input);
		ft_distruct_tree(start_token);
	}
	return (ft_distruct_memory(head) && ft_distruct_tree(start_token) &&
			ft_dist_str(input) ? 0 : 1);
}
