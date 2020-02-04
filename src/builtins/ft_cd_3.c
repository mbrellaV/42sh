/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 14:16:06 by plettie           #+#    #+#             */
/*   Updated: 2020/02/04 14:16:11 by plettie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

char		*is_pwd(t_cd *cd)
{
	int			k;

	if (cd->link == 1 && (k = ft_findenv("PWD=", g_env)) != -404 && !cd->cd_p)
		return (ft_strdup(g_env[k] + 4));
	else
		return (getcwd(NULL, 0));
}

int			do_cd(t_cd *cd, char *str)
{
	char		*full_path;
	int			res_d;
	int			res_l;

	if ((full_path = create_full_path(str, cd)))
	{
		if ((res_l = check_file(full_path, IS_L))
			&& res_l != -1 && cd->cd_p == 0)
			cd->link = 1;
		if ((res_d = check_file(full_path, IS_D)) == 1 || res_l == 1)
			change_path(full_path, cd);
		else if (res_d == -1 || res_l == -1)
			return (ft_cd_error(full_path, 3, 1));
		else if (res_d == 0)
			return (ft_cd_error(str, 3, 0));
		else
			return (ft_cd_error(str, 6, 0));
	}
	free(full_path);
	return (0);
}
