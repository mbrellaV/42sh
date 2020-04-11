/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 11:45:44 by plettie           #+#    #+#             */
/*   Updated: 2020/02/06 11:45:52 by plettie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

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
