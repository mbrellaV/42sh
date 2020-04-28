#include "fshell.h"

int		is_system_symbol(char c)
{
	if (c == '$' || c == '>' || c == '<' ||
	c == '=' || c == '&' || c == '|' || c == ';')
		return (1);
	return (0);
}