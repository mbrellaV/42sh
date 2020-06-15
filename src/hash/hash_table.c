/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:54:50 by wstygg            #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void				hash_init(void)
{
	register int	i;

	i = -1;
	while (++i < MAX_HASH)
		globals()->g_hash[i] = NULL;
}

t_hash				*parse_path(char *key, int i)
{
	char			**path;
	char			*cat;

	if (ft_findenv("PATH=", globals()->g_env) == -404)
		return (NULL);
	path = ft_strsplit(globals()->g_env[ft_findenv("PATH=",
									globals()->g_env)] + 5, ":");
	if (check_file(key, IS_X) == 1 && !check_file(key, IS_D))
	{
		ft_arrdel(path);
		return (hash_create(ft_strdup(key), ft_strdup(key)));
	}
	else
		while (path[++i])
		{
			cat = slash_cat(path[i], key);
			if (check_file(cat, IS_X) == 1)
			{
				ft_arrdel(path);
				return (hash_create(ft_strdup(key), cat));
			}
			free(cat);
		}
	ft_arrdel(path);
	return (NULL);
}

char				*hash_parse(char *key)
{
	t_hash			*hash;
	int				id;

	id = str_to_hash(key);
	if (!globals()->g_hash[id])
	{
		if ((globals()->g_hash[id] = parse_path(key, -1)))
			return (globals()->g_hash[id]->value);
		else
			return (NULL);
	}
	else
	{
		hash = globals()->g_hash[id];
		while (hash->next)
		{
			if (!ft_strcmp(hash->value, key))
				return (hash->value);
			hash = hash->next;
		}
		if (!ft_strcmp(hash->key, key))
			return (hash->value);
		return ((hash->next = parse_path(key, -1)) ? hash->next->value : NULL);
	}
}

void				hash_clear(void)
{
	t_hash			*hash;
	t_hash			*to_free;
	int				id;

	id = -1;
	while (++id < MAX_HASH)
		if (globals()->g_hash[id])
		{
			hash = globals()->g_hash[id];
			while (hash)
			{
				to_free = hash;
				hash = hash->next;
				free_hash(&to_free);
			}
			globals()->g_hash[id] = NULL;
		}
}

char				*hash_get(char *key, int no_error)
{
	char			*var;

	if (key[0] == '\0')
		return (hash_error(2, key, no_error));
	if (is_builtin(key))
		return (key);
	if (ft_strchr(key, '/'))
	{
		if (check_file(key, IS_X) == -1)
			return (hash_error(1, key, no_error));
		if (!check_file(key, IS_D) && check_file(key, IS_X) == 1)
			return (key);
		return (hash_error(3, key, no_error));
	}
	var = hash_parse(key);
	if (!var)
		return (hash_error(2, key, no_error));
	else if (check_file(var, IS_X) == 1 && !check_file(var, IS_D))
		return (var);
	else
	{
		hash_free_by_key(key);
		return (hash_error(3, key, no_error));
	}
}
