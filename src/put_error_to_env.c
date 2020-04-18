#include "fshell.h"

void	put_error_to_shell(int error)
{
	char	*str_for_del;

	str_for_del = ft_itoa(error);
	set_new_var("?", str_for_del, &g_all_var);
	ft_strdel(&str_for_del);
}