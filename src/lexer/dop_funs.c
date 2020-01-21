#include "../../inc/fshell.h"

int				ispar(char c)
{
	return (c == 34 || c == 39);
}

int				issc(char c)
{
	return (c == '(' || c == '{');
}

int				isoperator(char c)
{
	return (c == '<' || c == '&' || c == '|' || c == '>' || c == ';');
}

char			find_pair_sc(char c)
{
	if (c == '(')
		return (')');
	if (c == '{')
		return ('{');
	return (0);
}

int				isword(char c)
{
	if (ispar(c) == 1)
		return (2);
	if (issc(c) == 1)
		return (3);
	if (!isoperator(c) && c != ' ' && c != '\t')
		return (1);
	return (0);
}