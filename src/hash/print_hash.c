/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:54:56 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/02 13:20:10 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"
#include "hash.h"

static void			do_hash_args(char **args)
{
	register int	i;

	i = -1;
	while (args[++i])
		hash_get(args[i], 0);
}

int					do_hash(char **args)
{
	if (!args || !args[0] || !args[1])
		return (print_hash());
	while (args[1] && args[1][0] == '-')
	{
		if (ft_strequ(args[1], "-r"))
			hash_clear();
		else
			return (ft_dprintf(globals()->fd[1],
					"Invalid option %s!\nUsage: "HASH_USAGE"\n", args[1]));
				args++;
	}
	do_hash_args(args + 1);
	return (0);
}

int					print_hash(void)
{
	t_hash			*hash;
	int				i;

	i = -1;
	while (++i < MAX_HASH)
	{
		if (globals()->g_hash[i] != NULL)
		{
			hash = globals()->g_hash[i];
			while (hash)
			{
				ft_putstr_fd(hash->key, globals()->fd[1]);
				ft_putstr_fd("=", globals()->fd[1]);
				ft_putstr_fd(hash->value, globals()->fd[1]);
				if (hash->next)
					ft_putstr_fd("    ", globals()->fd[1]);
				hash = hash->next;
			}
			ft_putstr_fd("\n", globals()->fd[1]);
		}
	}
	return (1);
}
