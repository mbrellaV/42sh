/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 17:28:48 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/12 17:28:00 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/fshell.h"

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

void		ft_do_export(char **mas)
{
	char	*dop;

	if (mas == NULL)
		ft_dprintf(globals()->fd[2], "an error ocured\n");
	else if (mas[1] == NULL)
		return (ft_show_env(globals()->g_env));
	else if (mas[1] != NULL && mas[2] == NULL)
	{
		if (ft_strstr(mas[1], "=") != NULL)
		{
			ft_parse_and_make_save_to_env(mas[1]);
		}
		else if (ft_findenv(mas[1], globals()->g_all_var) != -404)
		{
			dop = ft_get_var(mas[1], globals()->g_all_var);
			set_new_var(mas[1], dop, &globals()->g_env);
			ft_strdel(&dop);
		}
	}
	else if (mas[1] && mas[2] && mas[3] == NULL)
	{
		set_new_var(mas[1], mas[2], &globals()->g_env);
	}
	else
		ft_dprintf(globals()->fd[2], "parse error\n");
}

void		do_all_var(char **env)
{
	int		i;

	i = -1;
	if (!(globals()->g_all_var = (char **)ft_memalloc(sizeof(char *) *
			(ft_env_len(env) + 2))))
		ft_error_q(1);
	while (env[++i])
	{
		if (!(globals()->g_all_var[i] = ft_strdup(env[i])))
			ft_error_q(1);
	}
	env[i] = NULL;
}
