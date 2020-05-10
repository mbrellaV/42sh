/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 18:54:39 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/04 14:49:03 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

void			init_first_envs()
{
	int		i;
	char	*dop;

	i = 0;
	if (!(globals()->g_first_env = (char **)ft_memalloc(sizeof(char *) *
			(ft_env_len(globals()->g_env) + 1))))
		ft_error_q(2);
	while (globals()->g_env[i] != NULL)
	{
		dop = ft_strsub(globals()->g_env[i], 0,
				ft_strstr(globals()->g_env[i], "=") - globals()->g_env[i]);
		if (!(globals()->g_first_env[i] = ft_strdup(dop)))
			ft_error_q(2);
		ft_strdel(&dop);
		i++;
	}
}

char			init_shell_builtins(void)
{
	int			i;
	const char	*g_builtins[BIL_NUM] = {
		"alias", "export", "unset",
		"history", "env", "clear", "hash",
		"cd", "echo", "exit", "type",
		"set", "fg", "bg", "jobs", "false",
		"fc", "authors", "unalias", "true", NULL};

	i = 0;
	init_first_envs();
	if (!(globals()->g_builtins = (char **)ft_memalloc(sizeof(char *) *
			(BIL_NUM + 1))))
		ft_error_q(1);
	while (g_builtins[i])
	{
		if (!(globals()->g_builtins[i] = ft_strdup(g_builtins[i])))
			ft_error_q(1);
		i++;
	}
	return (1);
}

int				is_builtin(char *str)
{
	int			i;

	i = 0;
	if (str == NULL)
		return (0);
	while (i < BIL_NUM - 1)
	{
		if (ft_strcmp(str, globals()->g_builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
