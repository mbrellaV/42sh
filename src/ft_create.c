/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 09:38:59 by qmartina          #+#    #+#             */
/*   Updated: 2019/11/15 16:17:33 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

int				check_file_args(t_process *tmp)
{
	if (tmp->file_args == NULL && tmp->file_opt == NULL)
		return (0);
	return (1);
}

void			tmp_cycle(t_exectoken *tmp, t_process *proc)
{
	while (tmp)
	{
		if (!(proc->next = ft_memalloc(sizeof(t_process))))
			ft_error_q(5);
		proc->next->file_args = tmp->file_args;
		proc->next->pid = 0;
		proc->next->file_opt = tmp->file_opt;
		proc->next->completed = 0;
		proc->next->completed = 0;
		proc->next->stopped = 0;
		proc->next->next = NULL;
		proc = proc->next;
		tmp = tmp->left;
	}
}

t_process		*create_process_list(t_exectoken *tmp)
{
	t_process	*proc;
	t_process	*fir;

	if (!(fir = ft_memalloc(sizeof(t_process))))
		ft_error_q(5);
	fir->file_args = tmp->file_args;
	if (check_file_args(fir) == 0)
		return (NULL);
	fir->foreground = 1;
	if (tmp->file_opt &&
	ft_strcmp(tmp->file_opt[ft_env_len(tmp->file_opt) - 1], "&") == 0)
		fir->foreground = 0;
	fir->pid = -1;
	fir->completed = 0;
	fir->next = NULL;
	fir->completed = 0;
	fir->stopped = 0;
	fir->file_opt = tmp->file_opt;
	proc = fir;
	tmp = tmp->left;
	tmp_cycle(tmp, proc);
	return (fir);
}

char			*create_command(t_exectoken *head)
{
	char		*new_str;
	char		*tmp;

	if (!(new_str = ft_strnew(1)))
		ft_error_q(5);
	while (head)
	{
		tmp = new_str;
		new_str = ft_strjoin(new_str, head->file_args[0]);
		head = head->left;
		ft_strdel(&tmp);
	}
	return (new_str);
}

t_job			*create_job(t_exectoken *head)
{
	t_job		*new_job;

	if (head == NULL)
		return (NULL);
	if (!(new_job = ft_memalloc(sizeof(t_job))))
		new_job->first_process = create_process_list(head);
	new_job->foreground = head->foreground;
	new_job->pgid = -1;
	new_job->command = create_command(head);
	new_job->stdinc = 0;
	new_job->stdoutc = 1;
	new_job->stderrc = 2;
	return (new_job);
}
