/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_whatis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 18:29:17 by wstygg            #+#    #+#             */
/*   Updated: 2020/04/20 14:49:45 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

void		do_heredoc_in_builtins(int *opened_fds, char *av, int flag)
{
	int		infile;
	if (flag == 4)
	{
		infile = ft_heredoc(av);
		//ft_redirect(p, STDIN_FILENO, STDOUT_FILENO);
		opened_fds[0] = infile;
	}
}

int		ft_open_flag_in_builtins(char *opt, int flag, int *infile, int *outfile)
{
	if (flag == 1 || flag == 2 || flag == 6)
		*outfile = open(opt, O_CREAT | O_RDWR | O_TRUNC,
						   S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
						   S_IROTH | S_IWOTH);
	else if (flag == 3)
		*infile = open(opt, O_RDONLY);
	if (((flag == 1 || flag == 6 || flag == 2) && *outfile <= 0) ||
		(flag == 3 && *infile <= 0))
	{
		ft_putstr_fd("42sh: open fd ERROR ", globals()->all_opened_fds[2]);
		ft_putendl_fd(opt, globals()->all_opened_fds[2]);
		return (-1);
	}
	return (1);
}

int		do_simple_redirects_for_builtin(int *opened_fds, char **av, int flag, int i)
{
	int		infile;
	int		outfile;

	infile = 0;
	outfile = 1;
	if (flag == 1 || flag == 2)
	{
		if (ft_open_flag_in_builtins(av[i + 2], flag, &infile, &outfile) == -1)
			return (-1);
		opened_fds[ft_atoi(av[i])] = outfile;
		//if (ft_find_in_fds(opened_fds, ft_atoi(av[i])) == 0)
		//	ft_add_to_fds(opened_fds, ft_atoi(av[i]));
	}
	if (flag == 3)
	{
		if (ft_open_flag_in_builtins(av[i + 2], flag, &infile, &outfile) == -1)
			return (-1);
		opened_fds[0] = infile;
	}
	return (0);
}

int			do_hard_redirects_in_builtins(int *opened_fds, char **av, int i, int flag)
{
	if ((ft_strcmp(av[i + 1], ">&") == 0 || ft_strcmp(av[i + 1], "<&")
											   == 0) && ft_strcmp(av[i + 2], "-") == 0)
	{
		ft_remove_from_fds(opened_fds, ft_atoi(av[i]));
	}
	else if (ft_strcmp(av[i + 1], "<&") == 0)
	{
		if (ft_find_in_fds(opened_fds, ft_atoi(av[i + 2])) == 0)
			return (-10);
		if (isword(av[i + 2][0]) && !ft_isdigit(av[i + 2][0]))
			return (-9);
		opened_fds[ft_atoi(av[i + 2])] = ft_atoi(av[i]);
	}
	else
	{
		if (isword(av[i + 2][0]) && !ft_isdigit(av[i + 2][0]))
			do_simple_redirects_for_builtin(opened_fds, av, flag, i);
		else if (ft_find_in_fds(opened_fds, ft_atoi(av[i])) == 0)
			return (-10);
		else
			opened_fds[ft_atoi(av[i])] = ft_atoi(av[i + 2]);
	}
	return (1);
}

int		set_redirects_for_builtins(char **av)
{
	int		*opened_fds;
	int		i;
	int		flag;
	int		b;

	b = 0;
	if (!(opened_fds = ft_create_opened_fds()))
		return (-1);
	i = 0;
	while (i < ft_env_len(av) && av[(i)] != NULL)
	{
		if (!(av[i][0] >= '0' && av[i][0] <= '9'))
			break ;
		flag = ft_what_flag(av[i + 1]);
		if (do_simple_redirects_for_builtin(opened_fds, av, flag, i) == -1)
			return (return_with_close(opened_fds, -1, NULL, 0));
		do_heredoc_in_builtins(opened_fds, av[i + 2], flag);
		if (flag == 6)
			b = do_hard_redirects_in_builtins(opened_fds, av, i, flag);
		if (b < 0)
			return (return_with_close(opened_fds, -1,
					ft_strdup(av[i + (b == -9 ? 2 : 0)]), b * -1));
		i += 3;
	}
	free(globals()->all_opened_fds);
	globals()->all_opened_fds = opened_fds;
	return (1);
}

int		ft_whatis4_1(t_exectoken *tmp)
{
	if (ft_strcmp(tmp->file_args[0], "true") == 0)
		put_error_to_shell(0);
	else if (ft_strcmp(tmp->file_args[0], "false") == 0)
		put_error_to_shell(2);
	else if (ft_strcmp(tmp->file_args[0], "fg") == 0)
		do_fg(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "bg") == 0)
		do_bg(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "jobs") == 0)
		do_job_notification();
	else if (ft_strcmp(tmp->file_args[0], "echo") == 0)
		ft_echo(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "history") == 0)
		show_history(globals()->g_memory_head);
	else if (ft_strcmp(tmp->file_args[0], "env") == 0)
		ft_show_env(globals()->g_env);
	else if (ft_strcmp(tmp->file_args[0], "clear") == 0)
		ft_putstr_fd("\033[2J\033[H", globals()->all_opened_fds[2]);
	else if (ft_strcmp(tmp->file_args[0], "hash") == 0)
		print_hash();
	else if (!ft_strcmp(tmp->file_args[0], "type"))
		ft_type(tmp->file_args);
	else
		return (0);
	return (1);
}

int		do_builtin(t_exectoken *tmp)
{
	if (tmp->file_args == NULL)
		return (-2);
	if (tmp->file_args[0] == NULL)
		return (-2);
	if (ft_strcmp(tmp->file_args[0], "exit") == 0 && tmp->file_args[1] == NULL)
		return (-1);
	if (tmp->file_opt != NULL && !(set_redirects_for_builtins(tmp->file_opt)))
		return (-2);
	put_error_to_shell(0);
	if (ft_strcmp(tmp->file_args[0], "alias") == 0 ||
	ft_strcmp(tmp->file_args[0], "unalias") == 0)
		ft_do_change_alias(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "cd") == 0)
		ft_cd(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "export") == 0)
		ft_do_export(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "unset") == 0 &&
		tmp->file_args[1] != NULL)
	{
		unset_var(tmp->file_args[1], &globals()->g_env);
		unset_var(tmp->file_args[1], &globals()->g_all_var);
	}
	else if (ft_strcmp(tmp->file_args[0], "set") == 0)
		ft_show_env(globals()->g_all_var);
	else
		return (ft_whatis4_1(tmp));
	return (1);
}

int		ft_whatis2_1(t_process *tmp)
{
	if (ft_strcmp(tmp->file_args[0], "fg") == 0)
		;
	else if (ft_strcmp(tmp->file_args[0], "bg") == 0)
		;
	else if (ft_strcmp(tmp->file_args[0], "jobs") == 0)
		do_job_notification();
	else if (ft_strcmp(tmp->file_args[0], "echo") == 0)
		ft_echo(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "history") == 0)
		show_history(globals()->g_memory_head);
	else if (ft_strcmp(tmp->file_args[0], "env") == 0)
		ft_show_env(globals()->g_env);
	else if (ft_strcmp(tmp->file_args[0], "clear") == 0)
		ft_putstr_fd("\033[2J\033[H", globals()->all_opened_fds[2]);
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
	if (ft_strcmp(tmp->file_args[0], "alias") == 0 ||
		ft_strcmp(tmp->file_args[0], "unalias") == 0)
		ft_do_change_alias(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "cd") == 0)
		ft_cd(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "export") == 0)
		ft_do_export(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "unset") == 0 &&
		tmp->file_args[1] != NULL)
	{
		unset_var(tmp->file_args[1], &globals()->g_env);
		unset_var(tmp->file_args[1], &globals()->g_all_var);
	}
	else if (ft_strcmp(tmp->file_args[0], "set") == 0)
		ft_show_env(globals()->g_all_var);
	else
		return (ft_whatis2_1(tmp));
	return (1);
}
