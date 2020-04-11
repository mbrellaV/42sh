/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 11:45:44 by plettie           #+#    #+#             */
/*   Updated: 2020/02/06 11:45:52 by plettie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

int					check_hash(char *arg)
{
	char			*hash;

	if (!(hash = hash_get(arg, 1)))
		return (0);
	ft_printf("%s is %s\n", arg, hash);
	return (1);
}

int					check_builtins(char *arg)
{
	int				i;

	i = -1;
	while (g_builtins[++i])
	{
		if (!ft_strcmp(arg, g_builtins[i]))
		{
			ft_printf("%s is a 21sh builtin\n", arg);
			return (1);
		}
	}
	return (0);
}

void				ft_type(char **argv)
{
	int				i;

	i = 0;
	while (argv[++i])
	{
		if (!check_builtins(argv[i]))
			if (!check_hash(argv[i]))
				ft_printf("%s not found\n", argv[i]);
	}
}
