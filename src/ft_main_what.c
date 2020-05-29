/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_what.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 17:22:09 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/12 22:36:30 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

static int	trick(t_exectoken **tmp)
{
	*tmp = (*tmp)->right;
	return (1);
}

int			do_qest(int wait_and, int wait_or)
{
	char	*del;
	int		num;

	if (!(del = ft_get_var("?", globals()->g_all_var)))
	{
		put_error_to_shell(2);
		return (1);
	}
	num = ft_atoi(del);
	ft_strdel(&del);
	if ((wait_and == 1 && num > 0) || (wait_or == 1 && num == 0))
	{
		return (1);
	}
	return (0);
}

static void	do_job_things(int *sas, t_job **job, t_exectoken *tmp)
{
	*job = create_job(tmp);
	if (globals()->g_f_job != NULL)
		get_last_job()->next = *job;
	else
		globals()->g_f_job = *job;
	*sas = launch_job(*job, (*job)->foreground);
	if (*sas == -2)
		make_job_completed(*job);
}

int			ft_main_if(t_exectoken *tmp, int sas, t_job *job)
{
	if (zam_bax_in_exectoken(tmp) == -1)
		return (-3);
	if ((tmp->file_args && !is_builtin(tmp->file_args[0])) || tmp->left)
		do_job_things(&sas, &job, tmp);
	else
		sas = do_builtin(tmp->file_args, tmp->file_opt, 0);
	return (sas);
}

int			ft_main_what(t_exectoken *tmp)
{
	t_job	*job;
	int		exit_status;

	exit_status = 0;
	job = NULL;
	while (tmp)
	{
		if (globals()->fd != NULL)
			free(globals()->fd);
		if (!(globals()->fd = ft_create_opened_fds()))
			return (-1);
		if ((tmp->file_args == NULL) && (tmp->file_opt == NULL) && trick(&tmp))
			continue ;
		if (((tmp->file_args && !is_builtin(tmp->file_args[0])) || tmp->left)
			|| (tmp->left == NULL && is_builtin(tmp->file_args[0]) == 1))
		{
			if (do_qest(tmp->wait_and, tmp->wait_or) && trick(&tmp))
				continue ;
			exit_status = ft_main_if(tmp, exit_status, job);
		}
		if (trick(&tmp) && exit_status == -1)
			return (-1);
		if (exit_status == -3)
			return (-3);
	}
	do_job_del();
	return (1);
}
