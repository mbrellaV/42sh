/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 18:29:17 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/12 17:28:00 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int		do_next_builtins_2(char **file_args)
{
	if (ft_strcmp(file_args[0], "env") == 0)
		ft_show_env(globals()->g_env);
	else if (ft_strcmp(file_args[0], "clear") == 0)
		ft_putstr_fd("\033[2J\033[H", globals()->fd[2]);
	else if (ft_strcmp(file_args[0], "hash") == 0)
		return (do_hash(file_args));
	else if (!ft_strcmp(file_args[0], "type"))
		ft_type(file_args);
	else if (!ft_strcmp(file_args[0], "fc"))
		return (do_fc(file_args));
	else if (!ft_strcmp(file_args[0], "authors"))
		return (do_authors());
	else
		return (0);
	return (1);
}

int		do_next_builtins(char **file_args)
{
	if (ft_strcmp(file_args[0], "set") == 0 && file_args[1] == NULL)
		ft_show_env(globals()->g_all_var);
	else if (ft_strcmp(file_args[0], "true") == 0)
		put_error_to_shell(0);
	else if (ft_strcmp(file_args[0], "false") == 0)
		put_error_to_shell(2);
	else if (ft_strcmp(file_args[0], "fg") == 0)
		do_fg(file_args);
	else if (ft_strcmp(file_args[0], "bg") == 0)
		do_bg(file_args);
	else if (ft_strcmp(file_args[0], "jobs") == 0)
		do_job_notification();
	else if (ft_strcmp(file_args[0], "echo") == 0)
		ft_echo(file_args);
	else if (ft_strcmp(file_args[0], "history") == 0)
		show_history(globals()->g_memory_head);
	else
		return (do_next_builtins_2(file_args));
	return (1);
}

int		do_builtin(char **file_args, char **file_opt, int type)
{
	if (file_args == NULL)
		return (-2);
	if (file_args[0] == NULL)
		return (-2);
	if (ft_strcmp(file_args[0], "exit") == 0)
		return (exit_builtin(file_args));
	if (type == 0 && file_opt != NULL && !(set_redirects_for_builtins(file_opt)))
		return (-2);
	if (ft_strcmp(file_args[0], "alias") == 0 ||
		ft_strcmp(file_args[0], "unalias") == 0)
		ft_do_change_alias(file_args);
	else if (ft_strcmp(file_args[0], "cd") == 0)
		ft_cd(file_args);
	else if (ft_strcmp(file_args[0], "export") == 0)
		ft_do_export(file_args);
	else if (ft_strcmp(file_args[0], "unset") == 0 && file_args[1])
	{
		unset_var(file_args[1], &globals()->g_env);
		unset_var(file_args[1], &globals()->g_all_var);
	}
	else
		return (do_next_builtins(file_args));
	return (1);
}
