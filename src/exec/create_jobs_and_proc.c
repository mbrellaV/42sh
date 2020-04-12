#include "fshell.h"

int			check_file_args(t_process *tmp)
{
	if (tmp->file_args == NULL && tmp->file_opt == NULL)
		return (0);
	//if (ft_strcmp(tmp->file_args[0], "exit") == 0)
	//	return (-1);
	return (1);
}

t_process	*create_process_list(t_exectoken *tmp)
{
	t_process	*proc;
	t_process	*fir;


	if (!(fir = ft_memalloc(sizeof(t_process))))
		ft_error_q(5);
	fir->file_args = tmp->file_args;

	if (check_file_args(fir) == 0)
		return (NULL);
	//take
	fir->foreground = 1;
	//ft_show_env(tmp->file_args);
	if (tmp->file_opt && ft_strcmp(tmp->file_opt[ft_env_len(tmp->file_opt) - 1], "&") == 0)
		fir->foreground = 0;
	fir->pid = -1;
	fir->completed = 0;
	fir->next = NULL;
	fir->completed = 0;
	fir->stopped = 0;
	fir->file_opt = tmp->file_opt;
	proc = fir;
	tmp = tmp->left;
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

	return (fir);
}

char	*create_command(t_exectoken *head)
{
	char *new_str;
	char *tmp;

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

t_job	*create_job(t_exectoken *head)
{
	t_job	*new_job;

	if (head == NULL)
		return (NULL);
	if (!(new_job = ft_memalloc(sizeof(t_job))))
		ft_error_q(2);
	//dprintf(2, "\n|%d|\n", head->foreground);
	new_job->first_process = create_process_list(head);
	new_job->foreground = head->foreground;
	new_job->pgid = -1;
	new_job->command = create_command(head);
	new_job->stdinc = 0;
	new_job->stdoutc = 1;
	new_job->stderrc = 2;
	return (new_job);
}