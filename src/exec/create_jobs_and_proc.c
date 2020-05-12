/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_jobs_and_proc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 11:48:56 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/12 22:36:30 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

t_process		*create_process(t_exectoken *tmp)
{
	t_process	*fir;

	if (!(fir = ft_memalloc(sizeof(t_process))))
		ft_error_q(5);
	fir->file_args = tmp->file_args;
	if (check_file_args(fir) == 0)
		return (NULL);
	fir->foreground = 1;
	fir->pid = 0;
	fir->completed = 0;
	fir->next = NULL;
	fir->stopped = 0;
	fir->file_opt = tmp->file_opt;
	return (fir);
}

t_process		*create_process_list(t_exectoken *tmp)
{
	t_process	*proc;
	t_process	*fir;

	if (!(fir = create_process(tmp)))
		ft_error_q(5);
	if (tmp->file_opt && ft_strcmp(tmp->file_opt[ft_env_len(tmp->file_opt) - 1],
			"&") == 0)
		fir->foreground = 0;
	proc = fir;
	tmp = tmp->left;
	while (tmp)
	{
		if (!(proc->next = create_process(tmp)))
			ft_error_q(5);
		proc = proc->next;
		tmp = tmp->left;
	}
	return (fir);
}

char			*create_new_cmd(char **mas, char *new_str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (mas[i] != NULL)
	{
		tmp = new_str;
		new_str = ft_strjoin(new_str, " ");
		ft_strdel(&tmp);
		tmp = new_str;
		new_str = ft_strjoin(new_str, mas[i]);
		ft_strdel(&tmp);
		i++;
	}
	return (new_str);
}

char			*create_command(t_exectoken *head)
{
	char		*new_str;

	if (!(new_str = ft_strnew(1)))
		ft_error_q(5);
	while (head)
	{
		new_str = create_new_cmd(head->file_args, new_str);
		if (head->file_opt != NULL)
			new_str = create_new_cmd(head->file_opt, new_str);
		head = head->left;
	}
	return (new_str);
}

t_job			*create_job(t_exectoken *head)
{
	t_job		*new_job;

	if (head == NULL)
		return (NULL);
	if (!(new_job = ft_memalloc(sizeof(t_job))))
		ft_error_q(2);
	new_job->first_process = create_process_list(head);
	new_job->foreground = head->foreground;
	new_job->pgid = -1;
	new_job->command = create_command(head);
	new_job->stdinc = 0;
	new_job->stdoutc = 1;
	new_job->stderrc = 2;
	return (new_job);
}
