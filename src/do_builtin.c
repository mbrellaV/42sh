/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 18:29:17 by wstygg            #+#    #+#             */
/*   Updated: 2020/06/15 22:42:15 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int		do_next_builtins_2(char **file_args)
{
	if (ft_strcmp(file_args[0], "env") == 0)
		put_error_to_shell(ft_show_env(globals()->g_env));
	else if (ft_strcmp(file_args[0], "clear") == 0)
    {
        ft_putstr_fd("\033[2J\033[H", globals()->fd[2]);
        put_error_to_shell(0);
    }
	else if (ft_strcmp(file_args[0], "hash") == 0)
		put_error_to_shell(do_hash(file_args));
	else if (!ft_strcmp(file_args[0], "type"))
		put_error_to_shell(ft_type(file_args));
	else if (!ft_strcmp(file_args[0], "authors"))
		put_error_to_shell(do_authors());
	else if (ft_strcmp(file_args[0], "export") == 0)
		put_error_to_shell(ft_do_export(file_args));
	else if (ft_strcmp(file_args[0], "unset") == 0 && file_args[1])
		put_error_to_shell(unset_builtin(file_args));
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
		put_error_to_shell(1);
	else if (ft_strcmp(file_args[0], "fg") == 0)
		put_error_to_shell(do_fg(file_args));
	else if (ft_strcmp(file_args[0], "bg") == 0)
		put_error_to_shell(do_bg(file_args));
	else if (ft_strcmp(file_args[0], "jobs") == 0)
		put_error_to_shell(do_job_notification());
	else if (ft_strcmp(file_args[0], "echo") == 0)
		put_error_to_shell(ft_echo(file_args));
	else if (ft_strcmp(file_args[0], "history") == 0)
		put_error_to_shell(hist_builtin(file_args));
	else
		return (do_next_builtins_2(file_args));
	return (1);
}

int		do_builtin(char **file_args, char **file_opt,
		int type, int *inhibitor_args)
{
	globals()->vivod = 0;
	if (file_args == NULL)
		return (-2);
	if (file_args[0] == NULL)
		return (-2);
	if (ft_strcmp(file_args[0], "exit") == 0)
		return (exit_builtin(file_args));
	if (type == 0 && file_opt != NULL
		&& !(set_redirects_for_builtins(file_opt)))
		return (-2);
	if (ft_strcmp(file_args[0], "alias") == 0 ||
		ft_strcmp(file_args[0], "unalias") == 0)
		ft_do_change_alias(file_args);
	else if (ft_strcmp(file_args[0], "cd") == 0)
		put_error_to_shell(ft_cd(file_args));
	else if (!ft_strcmp(file_args[0], "fc"))
		put_error_to_shell(do_fc(file_args));
	else if (!ft_strcmp(file_args[0], "42sh") && type == 0)
		put_error_to_shell(do_42sh_builtin(file_args));
	else
		return (do_next_builtins(file_args));
	return (1);
}
