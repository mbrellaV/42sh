/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 18:54:39 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/02 13:20:11 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

char	init_shell_builtins()
{
	int		i;
	char		*g_builtins[BIL_NUM] =
			{
					"alias",
					"export",
					"unset",
					"history",
					"env",
					"clear",
					"hash",
					"cd",
					"echo",
					"exit",
					"type",
					"set",
					"fg",
					"bg",
					"jobs",
					"fc",
					NULL
			};
	i = 0;
	if (!(globals()->g_builtins = (char **)ft_memalloc(sizeof(char *) *
												  (BIL_NUM + 1))))
		ft_error_q(1);
	while (g_builtins[i])
	{
		if (!(globals()->g_builtins[i] = ft_strdup(g_builtins[i])))
			ft_error_q(1);
		i++;
	}
}

int		is_builtin(char *str)
{
	int i;

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
