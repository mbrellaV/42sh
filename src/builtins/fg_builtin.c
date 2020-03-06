#include "../../inc/fshell.h"

int		do_fg(char **mas)
{
	if (mas[0] != NULL && mas[1] == NULL)
	{
		continue_job(get_last_job(), 1);
	}
	else if (mas[0] != NULL && mas[1] != NULL && mas[2] == NULL)
	{
		continue_job(get_job_by_number(ft_atoi(mas[1])), 1);
	}
	else
		return (-1);
	return (0);
}