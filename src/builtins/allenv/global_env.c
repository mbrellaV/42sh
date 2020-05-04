/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 19:59:12 by mbrella           #+#    #+#             */
/*   Updated: 2020/05/02 13:20:11 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/fshell.h"

void	ft_global_env(char **env, int argc)
{
	int		i;
	int		k;

	i = -1;
	k = argc;
	if (!(globals()->g_env = (char **)ft_memalloc(sizeof(char *) *
			(ft_env_len(env) + 1))))
		ft_error_q(1);
	while (env[++i])
	{
		if (!(globals()->g_env[i] = ft_strdup(env[i])))
			ft_error_q(1);
		k++;
	}
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

void	ft_show_env(char **env)
{
	int		i;

	i = 0;
	if (env == NULL)
		return ;
	while (env[i])
	{
		ft_dprintf(globals()->fd[1], "%s\n", env[i]);
		i++;
	}
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
