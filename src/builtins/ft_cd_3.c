/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 14:16:06 by plettie           #+#    #+#             */
/*   Updated: 2020/06/03 20:13:49 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

char			*ft_cdpath(char *ret, char *all)
{
	char		**str;
	int			i;
	char		*dop;

	i = -1;
	if ((dop = ft_get_var_from_both("CDPATH")))
	{
		str = ft_strsplit1(dop, ':');
		while (str[++i])
		{
			free(ret);
			ret = ft_strjoin_cd(ft_strjoin(str[i], "/"),
								all, 1);
			if (check_file(ret, IS_D) != -1)
			{
				ft_free_split(str);
				ft_strdel(&dop);
				return (ret);
			}
			ft_strdel(&ret);
		}
		ft_free_split(str);
	}
	ft_strdel(&dop);
	return (NULL);
}

char			*ft_strjoin_cd(char const *s1, char const *s2, int to_free)
{
	char		*str;
	size_t		i;
	size_t		k;

	if (!s1 || !s2)
		return (NULL);
	if (!(str = (char*)ft_memalloc(ft_strlen((char*)s1) +
			ft_strlen((char*)s2) + 1)))
		return (NULL);
	i = 0;
	k = 0;
	while (s1[i])
		str[k++] = s1[i++];
	i = 0;
	while (s2[i])
		str[k++] = s2[i++];
	str[k] = '\0';
	(to_free == 1) ? free((void*)s1) : 0;
	(to_free == 2) ? free((void*)s2) : 0;
	if (to_free == 3)
	{
		free((void*)s1);
		free((void*)s2);
	}
	return (str);
}

char			*get_pwd(t_builtins *cd)
{
	int			k;
	int			res_l;

	if (((k = ft_findenv("PWD=", globals()->g_env)) != -404))
		if ((res_l = check_file(globals()->g_env[k] + 4, IS_L)) && res_l != -1)
			cd->link = 1;
	if (cd->link == 1 && !cd->cd_p)
		return (ft_strdup(globals()->g_env[k] + 4));
	else
		return (getcwd(NULL, 0));
}

char			*get_oldpwd(t_builtins *cd)
{
	int			k;
	int			res_l;

	if (((k = ft_findenv("PWD=", globals()->g_env)) != -404))
	{
		if ((res_l = check_file(globals()->g_env[k] + 4, IS_L)) && res_l != -1)
			cd->link = 1;
	}
	if (cd->link == 1 && ((k = ft_findenv("PWD=", globals()->g_env)) != -404))
		return (ft_strdup(globals()->g_env[k] + 4));
	else
		return (getcwd(NULL, 0));
}

int				do_cd(t_builtins *cd, char *str)
{
	char		*full_path;
	int			res_d;
	int			res_l;
	int			k;

	if ((full_path = create_full_path(str, cd)))
	{
		if ((res_l = check_file(full_path, IS_L)) && res_l != -1)
			cd->link = 1;
		if ((res_d = check_file(full_path, IS_D)) == 1 || res_l == 1)
			change_path(full_path, cd);
		else if (res_d == -1 || res_l == -1)
			return (ft_cd_error(full_path, 3, 1));
		else
		{
			free(full_path);
			return (!res_d ? ft_cd_error(str, 3, 0) : ft_cd_error(str, 6, 0));
		}
	}
	if (!ft_strcmp(str, "-") &&
	(k = ft_findenv("PWD=", globals()->g_env)) != -404 && vivod(1))
		ft_dprintf(globals()->fd[1], "%s\n", globals()->g_env[k] + 4);
	free(full_path);
	return (0);
}
