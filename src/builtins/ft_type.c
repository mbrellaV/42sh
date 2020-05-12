/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:38:47 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/12 17:33:39 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

static int			check_hash(char *arg)
{
	char			*hash;

	if (!(hash = hash_get(arg, 1)))
		return (0);
	ft_dprintf(globals()->fd[1], "%s is %s\n", arg, hash);
	return (1);
}

static int			check_builtins(char *arg)
{
	register int	i;

	i = -1;
	while (globals()->g_builtins[++i])
		if (!ft_strcmp(arg, globals()->g_builtins[i]))
		{
			ft_dprintf(globals()->fd[1], "%s is a 42sh builtin\n", arg);
			return (1);
		}
	return (0);
}

static int			check_alias(char *arg)
{
	register int	i;
	char			*alias;

	i = -1;
	while (globals()->g_alias[++i])
	{
		alias = globals()->g_alias[i];
		if (ft_strnstr(alias, arg, ft_strlen(arg)))
		{
			ft_dprintf(globals()->fd[1], "%s is aliased to `%s'\n",
					arg, ft_strchr(alias, '=') + 1);
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
		if (!check_alias(argv[i]))
			if (!check_builtins(argv[i]))
				if (!check_hash(argv[i]))
					ft_dprintf(globals()->fd[2], "%s not found\n", argv[i]);
	}
}
