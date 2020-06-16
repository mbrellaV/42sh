/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_env_table.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:44:37 by qmartina          #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

void			ft_add_to_del_env_table(char *tmp)
{
	char	**new_del_env;
	int		i;
	int		size;

	i = 0;
	if (globals()->env_del == NULL)
		size = 0;
	else
		size = ft_env_len(globals()->env_del);
	if (!(new_del_env = ft_memalloc((sizeof(char *) * (size + 2)))))
		ft_error_q(2);
	while (globals()->env_del && globals()->env_del[i] != NULL)
	{
		new_del_env[i] = ft_strdup(globals()->env_del[i]);
		i++;
	}
	new_del_env[i++] = ft_strdup(tmp);
	new_del_env[i] = NULL;
	ft_free_str(globals()->env_del);
	globals()->env_del = new_del_env;
}

void			ft_free_env_table(void)
{
	int		i;

	i = 0;
	if (globals()->env_del == NULL)
		return ;
	while (globals()->env_del[i] != NULL)
	{
		unset_var(globals()->env_del[i], &globals()->g_env);
		i++;
	}
	ft_free_str(globals()->env_del);
	globals()->env_del = NULL;
}

int		ft_show_env_with_export(char **env)
{
	int		i;

	i = 0;
	if (!vivod(1) || env == NULL)
		return (1);
	while (env[i])
	{
		ft_dprintf(globals()->fd[1], "export %s\n", env[i]);
		i++;
	}
	return (0);
}