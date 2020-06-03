/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_what.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 17:22:09 by wstygg            #+#    #+#             */
/*   Updated: 2020/06/03 20:13:48 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

static int	trick(t_exectoken **tmp)
{
	*tmp = (*tmp)->right;
	return (1);
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
	if ((tmp->file_args && !is_builtin(tmp->file_args[0]))
	|| tmp->left || tmp->foreground == 0)
		do_job_things(&sas, &job, tmp);
	else
		sas = do_builtin(tmp->file_args, tmp->file_opt, 0, tmp->inhibitor_args);
	return (sas);
}

static int	ft_exit_status(t_exectoken **tmp, int exit_status)
{
	if (trick(tmp) && exit_status == -1)
		return (-1);
	if (exit_status == -3)
		return (-3);
	return (0);
}

int			ft_main_what(t_exectoken *tmp)
{
	t_job	*job;
	int		exit_status;

	exit_status = 0;
	job = NULL;
	while (tmp)
	{
		globals()->fd != NULL ? free(globals()->fd) : 0;
		if (!(globals()->fd = ft_create_opened_fds()))
			return (-1);
		if ((tmp->file_args == NULL) && (tmp->file_opt == NULL) && trick(&tmp))
			continue ;
		if (((tmp->file_args && !is_builtin(tmp->file_args[0])) || tmp->left)
			|| (tmp->left == NULL && is_builtin(tmp->file_args[0]) == 1))
		{
			if (do_quest(tmp->wait_and, tmp->wait_or) && trick(&tmp))
				continue ;
			exit_status = ft_main_if(tmp, exit_status, job);
		}
		if ((exit_status = ft_exit_status(&tmp, exit_status)) != 0)
			return (exit_status);
	}
	do_job_del();
	return (1);
}
