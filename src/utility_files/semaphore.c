#include "fshell.h"

void	start_semaphore(t_jobl *jobl)
{
	jobl->rt = NULL;
	jobl->mypipe[0] = 0;
	jobl->mypipe[1] = 0;
	pipe(jobl->sempipe);
}


void	wait_for_semaphore(t_jobl *jobl)
{
	int		i;
	char	buf[1];

	dprintf(2,  "\n1|%s, %d|\n", jobl->rt, is_builtin(jobl->rt));
	if (is_builtin(jobl->rt) == 0)
	{
		dprintf(2,  "\n2|%s, %d|\n", jobl->rt, is_builtin(jobl->rt));
		close(jobl->sempipe[1]);
		close(jobl->sempipe[0]);
		dprintf(2,  "\n33|%s, %d|\n", jobl->rt, is_builtin(jobl->rt));
		return ;
	}
	dprintf(2,  "\n3|%s, %d|\n", jobl->rt, is_builtin(jobl->rt));
	close(jobl->sempipe[1]);
	ft_dprintf(2, "\nsas0\n");
	while ((i = (read(jobl->sempipe[0], buf, 1))) <= 0)
		;
	ft_dprintf(2, "\nsas2: |%d, %s|\n", i, buf);
	close(jobl->sempipe[0]);
}

void	activate_semaphore(t_jobl *jobl)
{
	char	*buf;

//	if (is_builtin(jobl->rt) == 0)
//	{
//		close(jobl->sempipe[1]);
//		close(jobl->sempipe[0]);
//		return ;
//	}
	close(jobl->sempipe[0]);
	buf = ft_strdup("4");
	write(jobl->sempipe[1], buf, 2);
	ft_dprintf(2, "sas1\n");
	ft_strdel(&buf);
	close(jobl->sempipe[1]);
}