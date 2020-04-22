#include "fshell.h"

int		is_system_symbol(char *str)
{
	if (get_op_type(str) >= -1)
		return (1);
	if (ft_strcmp(str, "$") == 0)
		return (1);
	if (ft_strcmp(str, "=") == 0)
		return (1);
	if (ft_strstr(str, "\\") != NULL)
		return (1);
	if (ft_strcmp(str, "$") == 0)
		return (1);
	if (ft_strcmp(str, "$") == 0)
		return (1);
}