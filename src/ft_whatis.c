/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_whatis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 18:29:17 by wstygg            #+#    #+#             */
/*   Updated: 2020/04/19 18:12:50 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int		ft_whatis4_1(t_exectoken *tmp)
{
	if (ft_strcmp(tmp->file_args[0], "fg") == 0)
		do_fg(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "bg") == 0)
		do_bg(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "jobs") == 0)
		do_job_notification();
	else if (ft_strcmp(tmp->file_args[0], "echo") == 0)
		ft_echo(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "history") == 0)
		show_history(g_memory_head);
	else if (ft_strcmp(tmp->file_args[0], "env") == 0)
		ft_show_env(g_env);
	else if (ft_strcmp(tmp->file_args[0], "clear") == 0)
		ft_putstr_fd("\033[2J\033[H", 2);
	else if (ft_strcmp(tmp->file_args[0], "hash") == 0)
		do_hash(tmp->file_args);
	else if (!ft_strcmp(tmp->file_args[0], "type"))
		ft_type(tmp->file_args);
	else
		return (0);
	return (1);
}

int		ft_whatis4(t_exectoken *tmp)
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
		unset_var(tmp->file_args[1], &g_env);
		unset_var(tmp->file_args[1], &g_all_var);
	}
	else if (ft_strcmp(tmp->file_args[0], "set") == 0)
		ft_show_env(g_all_var);
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
		show_history(g_memory_head);
	else if (ft_strcmp(tmp->file_args[0], "env") == 0)
		ft_show_env(g_env);
	else if (ft_strcmp(tmp->file_args[0], "clear") == 0)
		ft_putstr_fd("\033[2J\033[H", 2);
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
		unset_var(tmp->file_args[1], &g_env);
		unset_var(tmp->file_args[1], &g_all_var);
	}
	else if (ft_strcmp(tmp->file_args[0], "set") == 0)
		ft_show_env(g_all_var);
	else
		return (ft_whatis2_1(tmp));
	return (1);
}
