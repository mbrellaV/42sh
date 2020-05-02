/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_job_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 12:44:23 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/02 13:20:10 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

void			free_process(t_process *tmp)
{
	t_process	*process_for_del;

	while (tmp)
	{
		process_for_del = tmp;
		tmp = tmp->next;
		free(process_for_del);
	}
}

void			free_job(t_job *tmp)
{
	if (tmp)
	{
		free_process(tmp->first_process);
		ft_strdel(&tmp->command);
		free(tmp);
	}
}

static void		norme_help(t_del *del)
{
	if (del->j->first_process->foreground == 0)
		format_job_info(del->j, "completed", del->d);
	if (del->jlast)
		del->jlast->next = del->jnext;
	else
		globals()->g_f_job = del->jnext;
	del->jdop = del->j;
}

int				do_job_del(void)
{
	t_del		del;

	del.d = 0;
	update_status();
	del.jlast = NULL;
	del.j = globals()->g_f_job;
	while (del.j)
	{
		del.d++;
		del.jnext = del.j->next;
		del.jdop = NULL;
		if (job_is_completed(del.j))
			norme_help(&del);
		else
			del.jlast = del.j;
		del.j = del.j->next;
		(del.jdop != NULL) ? free_job(del.jdop) : 0;
	}
	return (1);
}
