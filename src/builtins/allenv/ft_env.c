/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 17:28:48 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/02 13:20:11 by wstygg           ###   ########.fr       */
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

void		ft_do_export(char **mas)
{
	if (mas == NULL)
		ft_error(15, "an error ocured");
	else if (mas[1] == NULL)
		return (ft_show_env(globals()->g_env));
	else if (ft_findenv(mas[1], globals()->g_env) != -404 && mas[2] == NULL)
	{
		set_new_var(mas[1], ft_get_var(mas[1], globals()->g_env),
				&globals()->g_env);
	}
	else if (mas[1] && mas[2] && mas[3] == NULL)
	{
		set_new_var(mas[1], mas[2], &globals()->g_env);
	}
	else
		ft_error(15, "parse error");
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
