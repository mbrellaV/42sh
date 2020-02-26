#include "../inc/fshell.h"

const char		*g_builtins[BIL_NUM] =
{
	"alias",
	"export",
	"unexport",
	"history",
	"env",
	"clear",
	"hash",
	"cd",
	"echo",
	"exit",
	"type",
	"fg",
	"bg",
	"jobs",
	NULL
};

int		is_builtin(char *str)
{
	int i;

	i = 0;
	while (i < BIL_NUM - 1)
	{
		if (ft_strcmp(str, g_builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}