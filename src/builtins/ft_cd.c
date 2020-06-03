/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:03:14 by qmartina          #+#    #+#             */
/*   Updated: 2020/06/03 20:13:49 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int				ft_cd_error(char *tmp, int err, int to_free)
{
	put_error_to_shell(2);
	(err == 1 && vivod(2)) ? (ft_dprintf(globals()->fd[2],
			"cd: no such file or directory: %s\n", tmp)) : 0;
	(err == 2 && vivod(2)) ? ft_dprintf(globals()->fd[2],
			"cd: %s not set\n", tmp) : 0;
	(err == 3 && vivod(2)) ? (ft_dprintf(globals()->fd[2],
			"cd: not a directory: %s\n", tmp)) : 0;
	(err == 4 && vivod(2)) ? (ft_dprintf(globals()->fd[2],
			"cd: no such file or directory: %s\n", tmp)) : 0;
	(err == 6 && vivod(2)) ? (ft_dprintf(globals()->fd[2],
			"cd: permission denied: %s\n", tmp)) : 0;
	(err == 7 && vivod(2)) ? (ft_dprintf(globals()->fd[2],
			"cd: string not in pwd: %s\n", tmp)) : 0;
	(err == 9 && vivod(2)) ? ft_dprintf(globals()->fd[2],
			"cd: too many arguments\n") : 0;
	to_free ? free(tmp) : 0;
	return (-1);
}

int				flags_cd(char *str, t_builtins *cd, int j)
{
	if (str[j] == 'P')
		cd->cd_p = 1;
	else if (str[j] != 'L')
		return (ft_cd_error(str, 1, 0));
	return (1);
}

int				change_path(char *path, t_builtins *cd)
{
	char		*tmp;
	char		*pwd_env;

	if (path)
	{
		pwd_env = NULL;
		if ((tmp = get_oldpwd(cd)) && chdir(path) == -1 && ft_free(&tmp))
			return (ft_cd_error(path, 6, 0));
		if (cd->cd_p && cd->link && (pwd_env = getcwd(NULL, 0)))
			if (chdir(pwd_env) == -1 && ft_free(&tmp))
				return (ft_cd_error(pwd_env, 6, 1));
		set_new_var("OLDPWD", tmp, &globals()->g_env);
		set_new_var("OLDPWD", tmp, &globals()->g_all_var);
		pwd_env ? set_new_var("PWD", pwd_env, &globals()->g_env) :
		set_new_var("PWD", path, &globals()->g_env);
		pwd_env ? set_new_var("PWD", pwd_env, &globals()->g_all_var) :
		set_new_var("PWD", path, &globals()->g_all_var);
		free(pwd_env);
		free(tmp);
	}
	return (0);
}

int				change_env(char *env, t_builtins *cd)
{
	char		*pwd;
	int			k;

	if ((k = ft_findenv(env, globals()->g_env)) != -404)
	{
		pwd = get_oldpwd(cd);
		if (chdir(globals()->g_env[k] + ft_strlen(env)) == -1)
		{
			free(pwd);
			return (ft_cd_error(globals()->g_env[k] + ft_strlen(env), 6, 0));
		}
		set_new_var("OLDPWD", pwd, &globals()->g_env);
		set_new_var("PWD", globals()->g_env[k] + ft_strlen(env),
				&globals()->g_env);
		set_new_var("OLDPWD", pwd, &globals()->g_all_var);
		set_new_var("PWD", globals()->g_env[k] + ft_strlen(env),
					&globals()->g_all_var);
		free(pwd);
		return (0);
	}
	return (ft_cd_error(env, 2, 0));
}

int				ft_cd(char **str)
{
	t_builtins	cd;
	int			i;
	int			j;

	i = 0;
	cd.link = 0;
	cd.cd_p = 0;
	while (str[++i] && !(j = 0))
	{
		if (str[i][j] == '-' && ft_strcmp(str[i], "-"))
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
