/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 18:29:27 by wstygg            #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int			mas_1(char **mas)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strsub(mas[1], 0, ft_strstr(mas[1], "=") - mas[1]);
	tmp2 = ft_strsub(mas[1], ft_strstr(mas[1], "=") -
	mas[1] + 1, ft_strlen(mas[1]));
	if (has_system_symbol(tmp1) == 1)
		return (alias_error(2, tmp1, tmp2));
	set_new_var(tmp1, tmp2, &globals()->g_alias);
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
	return (0);
}

int			ft_do_change_alias(char **mas)
{
	if (mas[1] == NULL && ft_strcmp(mas[0], "alias") == 0)
		ft_show_env(globals()->g_alias);
	else if (ft_strcmp(mas[0], "unalias") == 0 && mas[1] != NULL &&
	mas[2] == NULL && ft_strstr(mas[1], "=") == NULL)
	{
		unset_var(mas[1], &globals()->g_alias);
		ft_show_env(globals()->g_alias);
	}
	else if (ft_strcmp(mas[0], "alias") == 0 && mas[1] && mas[2] == NULL)
	{
		if (ft_strstr(mas[1], "=") != NULL)
		{
			if (mas_1(mas) == -1)
				return (-1);
		}
		else
			return (alias_error(14, NULL, NULL));
	}
	else
		return (alias_error(15, NULL, NULL));
	return (0);
}
