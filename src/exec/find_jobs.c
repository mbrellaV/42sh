#include "fshell.h"

t_job		*get_job_by_number(int n)
{
	t_job *j;
	int i;

	j = f_job;
	if (n < 0)
		return (NULL);
	i = 1;
	while (j && i < n)
	{
		i++;
		j = j->next;
	}
	return (j);
}

t_job		*get_last_job()
{
	t_job *j;

	j = f_job;
	while (j && j->next)
	{
		j = j->next;
	}
	return (j);
}