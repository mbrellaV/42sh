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

void	ft_cd_error(char *tmp)
{
	if (access(tmp, 0) == -1)
		ft_putstr("cd: no such file or directory: ");
	else if (access(tmp, 3) == -1)
		ft_putstr("cd: permission denied: ");
	else
		ft_putstr("cd: not a directory: ");
	ft_putendl(tmp);
}

void	ft_global_dir(int flag, char *str)
{
	int		k;
	char	tmp[4097];

	getcwd(tmp, 4096);
	if (flag == 2)
	{
		k = chdir(str);
		if (k == -1)
			ft_cd_error(str);
		else
		{
			set_new_var("OLDPWD", tmp, &g_env);
			getcwd(tmp, 4096);
			set_new_var("PWD", tmp, &g_env);
		}
	}
	else if (flag == 3)
	{
		if ((k = ft_findenv("OLDPWD=", g_env)) == -404)
			ft_putendl("cd: no such OLDPWD directory");
		else
			ft_global_dir(2, &g_env[k][7]);
	}
	else if (flag == 0 && ((k = ft_findenv("HOME=", g_env)) != -404))
		set_new_var("OLDPWD", &g_env[k][5], &g_env);
}

void	ft_cd1(void)
{
	int k;

	k = ft_findenv("HOME=, g_env", g_env);
	if (k == -404)
		ft_putendl("cd: no such HOME directory");
	else
		ft_global_dir(2, &g_env[k][5]);
}

void	ft_cd(char **str)
{
	char	*tmp;
	int		i;

	i = 0;
	while (str[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putendl_fd(str[1], 2);
		return ;
	}
	if (!str[1])
		return (ft_cd1());
	if (str[1][0] == '~')
		tmp = ft_cd_home(str[1]);
	else if (str[1][0] == '-')
		return (ft_global_dir(3, NULL));
	else
		tmp = ft_strdup(str[1]);
	ft_global_dir(2, tmp);
	free(tmp);
}
