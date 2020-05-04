/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_what.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 17:22:09 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/02 13:20:10 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

static int	trick(t_exectoken **tmp)
{
	*tmp = (*tmp)->right;
	return (1);
}

static void	do_job_things(char **del, int *sas, t_job **job, t_exectoken *tmp)
{
	*job = create_job(tmp);
	if (globals()->g_f_job != NULL)
		get_last_job()->next = *job;
	else
		globals()->g_f_job = *job;
	*sas = launch_job(*job, (*job)->foreground);
	ft_strdel(del);
}

int			ft_main_if(t_exectoken *tmp, int sas, char *del, t_job *job)
{
	if ((tmp->file_args && !is_builtin(tmp->file_args[0])) || tmp->left)
		do_job_things(&del, &sas, &job, tmp);
	else
	{
		sas = do_builtin(tmp);
		ft_strdel(&del);
	}
	return (sas);
}

int			ft_main_what(t_exectoken *tmp)
{
	t_job	*job;
	int		sas;
	char	*del;

	sas = 0;
	while (tmp)
	{
		if ((tmp->file_args == NULL) && (tmp->file_opt == NULL) && trick(&tmp))
			continue ;
		if (((tmp->file_args && !is_builtin(tmp->file_args[0])) || tmp->left)
			|| (tmp->left == NULL && is_builtin(tmp->file_args[0]) == 1))
		{
			del = ft_get_var("?", globals()->g_all_var);
			if (((tmp->wait_and == 1 && ft_atoi(del) > 0) || (tmp->wait_or == 1
				&& !ft_atoi(del))) && strdelr(&del) && trick(&tmp))
				continue ;
			sas = ft_main_if(tmp, sas, del, job);
		}
		if (trick(&tmp) && sas == -1)
			return (-1);
	}
	do_job_del();
	return (1);
}
