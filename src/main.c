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
	if (do_zam_bax_and_hist_full(tmp->file_args) == -1)
		ft_error_args(tmp);
	if (ft_do_zam_eval(tmp->file_args) == -1)
		ft_error_args(tmp);
	if (do_zam_ravno(tmp->file_args) == -1)
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


int		ft_main_what(t_exectoken *tmp, t_memory *q)
{
	int		i;

	i = -1;
	while (tmp)
	{
		if (ft_whatis(tmp, q) == -1)
			return (-1);
		tmp = tmp->right;
	}
	return (1);
}

char	**new_env_var(char **env)
{
	int		i;
	char	**new_env;

	i = -1;
	if (!(new_env = (char **)ft_memalloc(sizeof(char *) * (ft_env_len(env) + 1))))
		ft_error_q(1);
	while (env[++i])
	{
		//ft_printf();
		if (!(new_env[i] = ft_strdup(env[i])))
			ft_error_q(1);
	}

	return (new_env);
}

void    ft_check_cd()
{
	char    folder[1024];
	char	*dop;
	char	*res;
	char	**tmp;

	dop = ft_get_var("PWD", g_env);
	getcwd(folder, 1024);
	if (ft_strcmp(folder, dop) == 0)
    {
        ft_strdel(&dop);
        return ;
    }
	res = ft_strjoin("cd ", dop);
	tmp = ft_strsplit(res, " ");
	ft_strdel(&res);
    ft_strdel(&dop);
	ft_cd(tmp);
}

int		do_cmd(char *input, t_memory *head)
{
	t_exectoken		*start_token;
	char			**g_alias_dop;
	char			**g_env_dop;
	char			*g_cp_dop;
	char			**g_all_var_dop;

	g_cp_dop = ft_strdup(g_cp);
	g_alias_dop = new_env_var(g_alias);
	g_env_dop = new_env_var(g_env);
	g_all_var_dop = new_env_var(g_all_var);
	ft_show_env(g_alias_dop);
	start_token = all_parse(input);
	ft_main_what(start_token, head);
	ft_printf("123\n");
	g_alias = g_alias_dop;
	g_env = g_env_dop;
	g_cp = g_cp_dop;
	g_all_var = g_all_var_dop;
	return (0);
	return (ft_distruct_tree(start_token) &&
	ft_dist_str(input) ? 0 : 1);
}

int		save_history(t_memory *q)
{
	int		fd;
	char	buf[10];

	fd = open("history/hist.txt",  O_TRUNC);
	close(fd);
	fd = open("history/hist.txt",  O_RDWR);
	read(fd, buf, sizeof(buf));
	while (q->back->back != NULL)
		q = q->back;
	while (q != NULL)
	{
		write(fd, q->inp, ft_strlen(q->inp));
		write(fd, "\n", 1);
		q = q->next;
	}
	close(fd);
	return (0);
}

void	do_count_shell_lvl()
{
	char	*dop;
	char	*dop1;

	dop = ft_get_var("SHLVL", g_env);
	dop1 = ft_itoa(ft_atoi(dop) + 1);
	set_new_var("SHLVL", dop1, &g_env);
	ft_strdel(&dop);
	ft_strdel(&dop1);
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
	//do_count_shell_lvl();
	while (1)
	{
		set_input_mode();
		atexit(reset_input_mode);
		input = ft_read_8(ft_main_norm(0), head, 0);
		write(2, "\n", 1);
		input[0] != '\0' ? head = ft_memory(head, &input) : head;
		while (ft_cheak_quote(input) != 1)
			ft_add_intput_que(&input, head);
		reset_input_mode();
		//input = ft_strdup("ddd="ppp"");
		start_token = all_parse(input);
		if (ft_main_what(start_token, head) == -1)
			break ;
		ft_strdel(&input);
		ft_distruct_tree(start_token);
	}
	save_history(head);
	return (ft_distruct_memory(head) && ft_distruct_tree(start_token) &&
		ft_dist_str(input) ? 0 : 1);
}
