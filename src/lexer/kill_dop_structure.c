#include "../../inc/fshell.h"

t_lextoken		*ft_kill_str_dop(t_dop_str *t, t_lextoken *tmp)
{
	if (t != NULL)
		free(t);
	return (tmp);
}