#include "../../inc/fshell.h"

t_lextoken		*ft_kill_str_dop_lex(t_dop_str *t, t_lextoken *tmp)
{
	if (t != NULL)
		free(t);
	if (tmp != NULL)
	    return (tmp);
    return (NULL);
}

t_exectoken     *ft_kill_str_dop_exec(t_dop_str *t, t_exectoken *tmpexec)
{
    if (t != NULL)
        free(t);
    if (tmpexec != NULL)
        return (tmpexec);
    return (NULL);
}