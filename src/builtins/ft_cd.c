/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:03:14 by qmartina          #+#    #+#             */
/*   Updated: 2019/10/24 20:03:16 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

int			ft_cd_error(char *tmp, int err, int to_free)
{
	err == 1 ? ft_printf("42sh : cd: no such file or directory: %s\n", tmp) : 0;
	err == 2 ? ft_printf("42sh: cd: %s not set\n", tmp) : 0;
	err == 3 ? ft_printf("42sh: cd: not a directory: %s\n", tmp) : 0;
	err == 4 ? ft_printf("42sh: cd: no such file or directory: %s\n", tmp) : 0;
	err == 6 ? ft_printf("42sh: cd: permission denied: %s\n", tmp) : 0;
	err == 7 ? ft_printf("cd: string not in pwd: %s\n", tmp) : 0;
	err == 9 ? ft_printf("42sh: cd: too many arguments\n") : 0;
	to_free ? free(tmp) : 0;
	return (0);
}

int			flags_cd(char *str, t_cd *cd, int j)
{
	if (str[j] == 'P')
		cd->cd_p = 1;
	else if (str[j] != 'L')
		return (ft_cd_error(str, 1, 0));
	return (1);
}

int			change_path(char *path, t_cd *cd)
{
	char	*tmp;

	if (path)
	{
		tmp = is_pwd(cd);
		if (chdir(path) == -1)
		{
			free(tmp);
			return (ft_cd_error(path, 6, 0));
		}
		set_new_var("OLDPWD", tmp, &g_env);
		set_new_var("PWD", path, &g_env);
		free(tmp);
		return (0);
	}
	return (0);
}

int			change_env(char *env, t_cd *cd)
{
	char	*tmp;
	int		k;

	if ((k = ft_findenv(env, g_env)) != -404)
	{
		tmp = is_pwd(cd);
		if (!ft_strcmp("OLDPWD=", env))
			ft_printf("%s\n", g_env[k] + ft_strlen(env));
		if (chdir(g_env[k] + ft_strlen(env)) == -1)
		{
			free(tmp);
			return (ft_cd_error(g_env[k] + ft_strlen(env), 6, 0));
		}
		set_new_var("OLDPWD", tmp, &g_env);
		set_new_var("PWD", g_env[k] + ft_strlen(env), &g_env);
		free(tmp);
		return (0);
	}
	return (ft_cd_error(env, 2, 0));
}

int			ft_cd(char **str)
{
	t_cd	cd;
	int		i;
	int		j;

	i = 0;
	cd.link = 0;
	cd.cd_p = 0;
	while (str[++i] && !(j = 0))
	{
		if (!(ft_strcmp(str[i], "-")))
			return (change_env("OLDPWD=", &cd));
		else if (str[i][j] == '-')
		{
			while (str[i][++j])
				if (!flags_cd(str[i], &cd, j))
					return (1);
		}
		else if (str[i] && str[i + 1] && !str[i + 2])
			return (ft_cd_error(str[1], 7, 0));
		else if (str[i] && str[i + 1] && str[i + 2])
			return (ft_cd_error(NULL, 9, 0));
		else
			return (do_cd(&cd, str[i]));
	}
	return (change_env("HOME=", &cd));
}
