#include "fshell.h"
//
//pid_t				g_shell_pgid;
//int					g_shell_terminal;
//int					g_shell_is_interactive;
//char				**g_env;
//char				*g_cp;
//int					g_his_d;
//char				**g_alias;
//char				**g_all_var;
//t_memory			*g_memory_head;
//extern const char	*g_builtins[BIL_NUM];
//t_job				*g_f_job;

char							**alises(char **alises)
{
	static char		**all_aliases;

	if (alises != NULL && all_aliases == NULL)
	{
		all_aliases = alises;
		return (all_aliases);
	}
	else
	{
		return (all_aliases);
	}
}

char							**all_var(char **var)
{
	static char		**all_var;

	if (var != NULL && all_var == NULL)
	{
		all_var = var;
		return (all_var);
	}
	else
	{
		return (all_var);
	}
}

t_memory						*memory_head(t_memory *head)
{
	static t_memory		*memory_head;

	if (head != NULL && memory_head == NULL)
	{
		memory_head = head;
		return (memory_head);
	}
	else
	{
		return (memory_head);
	}
}

t_job							*get_first_job(t_job *f_job)
{
	static t_memory		*first_job;

	if (f_job != NULL && first_job == NULL)
	{
		first_job = f_job;
		return (first_job);
	}
	else
	{
		return (first_job);
	}
}