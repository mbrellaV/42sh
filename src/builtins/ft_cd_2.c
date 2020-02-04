/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 21:21:32 by plettie           #+#    #+#             */
/*   Updated: 2020/02/02 21:22:27 by plettie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

char		*ft_strjoin_cd(char const *s1, char const *s2, int to_free)
{
	char		*str;
	size_t		i;
	size_t		k;

	if (!s1 || !s2)
		return (NULL);
	if (!(str = (char*)malloc(ft_strlen((char*)s1) + ft_strlen((char*)s2) + 1)))
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

char		*cd_back(char *old)
{
	int			i;
	char		*new;
	int			j;

	j = 0;
	if (old)
	{
		i = ft_strlen(old);
		while (old[i] != '/')
			i--;
		if (!(new = malloc(sizeof(char *) * i + 1)))
			return (NULL);
		while (j < i)
		{
			new[j] = old[j];
			j++;
		}
		j++;
		new[j] = '\0';
		free(old);
		return (new);
	}
	return (NULL);
}

char		*full_path_helper(char *ret, char *all, char *path)
{
	if (!ft_strcmp(all, ".."))
		ret = cd_back(ret);
	else if (ft_strcmp(all, "."))
	{
		ft_strcmp(ret, "/") ? ret = ft_strjoin_cd(ret, "/", 1) : 0;
		ret = ft_strjoin_cd(ret, all, 1);
	}
	if ((check_file(ret, IS_D)) == -1)
	{
		ft_cd_error(path, 4, 0);
		free(ret);
		return (NULL);
	}
	return (ret);
}

char		*full_path_helper_2(char *path, char **all_path, t_cd *cd)
{
	char		*ret;

	if (!all_path[0])
	{
		ft_free_str(all_path);
		return (ft_strdup("/"));
	}
	if (path[0] != '/')
		ret = is_pwd(cd);
	else
		ret = ft_strdup("/");
	return (ret);
}

char		*create_full_path(char *path, t_cd *cd)
{
	int			i;
	char		*ret;
	char		**all_path;

	i = -1;
	if (path)
	{
		all_path = ft_strsplit1(path, '/');
		if ((ret = full_path_helper_2(path, all_path, cd)) && !all_path[0])
			return (ret);
		while (all_path[++i])
			if (!(ret = full_path_helper(ret, all_path[i], path)))
			{
				ft_free_str(all_path);
				return (NULL);
			}
		ft_free_str(all_path);
		if (!(check_file(ret, IS_E)))
		{
			ft_cd_error(ret, 6, 1);
			return (NULL);
		}
		return (ret);
	}
	return (NULL);
}
