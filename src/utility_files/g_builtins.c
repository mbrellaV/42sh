/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 18:54:39 by wstygg            #+#    #+#             */
/*   Updated: 2020/04/20 14:49:45 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

const char		*g_builtins[BIL_NUM] =
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
	NULL
};

int		is_builtin(char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (0);
	while (i < BIL_NUM - 1)
	{
		if (ft_strcmp(str, g_builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
