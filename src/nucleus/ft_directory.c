/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_tab_funs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 19:36:44 by mbrella           #+#    #+#             */
/*   Updated: 2020/05/12 15:40:48 by pro              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_find_dir(char *dir, char *name, t_readline *p)
{
	DIR				*mydir;
	struct dirent	*myfile;

	mydir = opendir(dir);
	if (mydir != NULL)
	{
		while ((myfile = readdir(mydir)) != 0)
		{
			if (is_cmp(name, myfile->d_name) && myfile->d_name[0] != '.')
				ft_add_tab(p, myfile->d_name);
		}
		closedir(mydir);
	}
}

char	*ft_directory(char *str, int *flag_tab)
{
	int		k;
	char	*tmp;
	char	*hp;
	char	*tmp1;

	k = ft_strlen(str);
	while (--k >= 0)
		if (str[k] == '/')
		{
			if (str[0] == '~')
			{
				if (!(hp = ft_get_var("HOME", globals()->g_env)))
					ft_error_q(5);
				tmp = ft_strndup(&str[1], k - 1);
				tmp1 = ft_strjoin(hp, tmp);
				free(hp);
				ft_strdel(&tmp);
				return (tmp1);
			}
			else
				return (ft_strndup(str, k + 1));
		}
	*flag_tab = (*flag_tab <= 1 ? 0 : *flag_tab);
	return (ft_strdup("./"));
}
