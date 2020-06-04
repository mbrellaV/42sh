/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 19:59:12 by mbrella           #+#    #+#             */
/*   Updated: 2020/06/03 20:13:50 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

void	do_all_var(char **env)
{
	int		i;

	i = -1;
	if (!(globals()->g_all_var = (char **)ft_memalloc(sizeof(char *) *
			(ft_env_len(env) + 2))))
		ft_error_q(1);
	while (env[++i])
	{
		if (!(globals()->g_all_var[i] = ft_strdup(env[i])))
			ft_error_q(1);
	}
	env[i] = NULL;
}

void	ft_global_env(char **env, int argc)
{
	int		i;
	int		k;

	i = -1;
	k = argc;
	if (!(globals()->g_env = (char **)ft_memalloc(sizeof(char *) *
			(ft_env_len(env) + 2))))
		ft_error_q(1);
	while (env[++i])
	{
		if (!(globals()->g_env[i] = ft_strdup(env[i])))
			ft_error_q(1);
		k++;
	}
	globals()->g_env[i] = NULL;
	if (((k = ft_findenv("HOME=", globals()->g_env)) != -404))
		set_new_var("OLDPWD", &globals()->g_env[k][5], &globals()->g_env);
	do_all_var(env);
	globals()->g_cp = ft_strnew(1);
}

int		ft_env_len(char **env)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (env[++i])
		count++;
	return (count);
}

int		ft_show_env(char **env)
{
	int		i;

	i = 0;
	if (!vivod(1) || env == NULL)
		return (1);
	while (env[i])
	{
		ft_dprintf(globals()->fd[1], "%s\n", env[i]);
		i++;
	}
	return (0);
}

int		ft_findenv(char *s, char **env)
{
	int i;

	i = -1;
	while (env[++i])
	{
		if (ft_strcmp_start(env[i], s) == 1)
			return (i);
	}
	return (-404);
}
