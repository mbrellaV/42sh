/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:38:47 by wstygg            #+#    #+#             */
/*   Updated: 2020/04/13 20:04:23 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

int 				try_builtin(char *name)
{
	if (fcntl(1, F_GETFD, FD_CLOEXEC) > 0)
		return (1);
	ft_dprintf(2, "42sh: %s: write error: Bad file descriptor\n", name);
	return (-1);
}

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
		if (try_builtin("type") != -1 && !ft_strcmp(arg, g_builtins[i]))
		{
			ft_printf("%s is a 42sh builtin\n", arg);
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
				ft_dprintf(2, "%s not found\n", argv[i]);
	}
}
