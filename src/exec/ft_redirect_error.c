#include "fshell.h"

void	ft_redirect_error(int marker, char *dopline)
{
	put_error_to_shell(2);
	if (marker == 10)
	{
		ft_dprintf(globals()->fd[2], SHELL_NAME": %s: Bad file descriptor",
				dopline);
		ft_strdel(&dopline);
	}
	if (marker == 9)
	{
		ft_dprintf(globals()->fd[2], SHELL_NAME": %s: ambiguous redirect",
				dopline);
	}
}