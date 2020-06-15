/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 17:28:48 by qmartina          #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

char		*ft_get_var_from_both(char *str)
{
	char	*res;

	if ((res = ft_get_var(str, globals()->g_env)) != NULL)
		return (res);
	if ((res = ft_get_var(str, globals()->g_all_var)) != NULL)
		return (res);
	return (NULL);
}

char		*ft_get_var(char *dop, char **env)
{
	int		i;
	char	*dopd;

	i = 0;
	if (env == NULL)
		return (NULL);
	dopd = ft_strjoin(dop, "=");
	while (env[i])
	{
		if (ft_strstr(env[i], dopd) == env[i])
		{
			if (!(dop = ft_strsub(env[i], ft_strlen(dopd),
					ft_strlen(env[i]) - ft_strlen(dopd))))
				return (NULL);
			ft_strdel(&dopd);
			return (dop);
		}
		i++;
	}
	ft_strdel(&dopd);
	return (NULL);
}

void		ft_parse_and_make_save_to_env(char *arg)
{
	char	*name;
	char	*res;
	int		len;

	len = (int)(ft_strstr(arg, "=") - arg);
	name = ft_strsub(arg, 0, len);
	res = ft_strsub(arg, len + 1, ft_strlen(arg) - len);
	set_new_var(name, res, &globals()->g_env);
	set_new_var(name, res, &globals()->g_all_var);
	ft_strdel(&name);
	ft_strdel(&res);
}

static int	do_save_to_env(char **mas)
{
	char	*dop;

	if (ft_strstr(mas[1], "=") != NULL)
	{
		ft_parse_and_make_save_to_env(mas[1]);
		return (0);
	}
	else if (ft_findenv(mas[1], globals()->g_all_var) != -404)
	{
		dop = ft_get_var(mas[1], globals()->g_all_var);
		set_new_var(mas[1], dop, &globals()->g_env);
		ft_strdel(&dop);
		return (0);
	}
	vivod(2) ? ft_dprintf(globals()->fd[2], "no such var\n") : 0;
	return (1);
}

int			ft_do_export(char **mas)
{
	if (mas == NULL)
		return (vivod(2) ? (ft_dprintf(globals()->fd[2],
				"an error ocured\n")) : 1);
	else if (mas[1] == NULL && !ft_show_env(globals()->g_env))
		return (0);
	else if (mas[1] && !ft_strcmp("-p", mas[1]) &&
	mas[2] == NULL && !ft_show_env(globals()->g_env))
		return (0);
	else if (mas[1] != NULL && mas[2] == NULL && ft_strcmp("-p", mas[1]))
		return (do_save_to_env(mas));
	else if (mas[1] && mas[2] && mas[3] == NULL && ft_strcmp("-p", mas[1]))
		set_new_var(mas[1], mas[2], &globals()->g_env);
	else
	{
		vivod(2) ? ft_dprintf(globals()->fd[2], "parse error\n") : 0;
		return (2);
	}
	return (0);
}
