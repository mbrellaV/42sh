/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 18:29:17 by wstygg            #+#    #+#             */
/*   Updated: 2020/04/15 18:36:54 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

char	*do_reverse_zamena(char *str)
{
	int		i;
	char	*newstr;
	char	*tmp;

	i = -1;
	if (!(newstr = ft_memalloc(ft_strlen(str) * 2 + 1)))
		ft_error_q(15);
	while (str[++i] != '\0')
	{
		if (str[i] < 0)
		{
			tmp = ft_strdup("\\ ");
			tmp[1] = -1 * str[i];
			ft_strcat(newstr, tmp);
			ft_strdel(&tmp);
		}
		else
		{
			tmp = ft_strdup(" ");
			tmp[0] = str[i];
			ft_strcat(newstr, tmp);
			ft_strdel(&tmp);
		}
	}
	ft_strdel(&str);
	return (newstr);
}

int		ft_main_what(t_exectoken *tmp)
{
	t_job	*job;
	int		sas;
	char	*str_to_del;

	sas = 0;
	while (tmp)
	{
		if ((tmp->file_args == NULL) && (tmp->file_opt == NULL))
		{
			tmp = tmp->right;
			continue ;
		}
		if ((tmp->file_args != NULL && is_builtin(tmp->file_args[0]) == 0)
			|| tmp->file_opt != NULL)
		{
			str_to_del = ft_get_var("?", g_all_var);
			if (tmp->should_wait_and == 1 && ft_atoi(str_to_del) > 0)
			{
				ft_strdel(&str_to_del);
				tmp = tmp->right;
				continue ;
			}
			else if (tmp->should_wait_or == 1 && ft_atoi(str_to_del) == 0)
			{
				ft_strdel(&str_to_del);
				tmp = tmp->right;
				continue ;
			}
			job = create_job(tmp);
			if (f_job != NULL)
				get_last_job()->next = job;
			else
				f_job = job;
			sas = launch_job(job, job->foreground);
			ft_strdel(&str_to_del);
		}
		else if (tmp->left == NULL && is_builtin(tmp->file_args[0]) == 1)
			sas = ft_whatis4(tmp);
		if (sas == -1)
			return (-1);
		tmp = tmp->right;
	}
	do_job_del();
	return (1);
}

int			ck_br(const char *str)
{
	char	*s;
	int		i;
	int		k;
	char	c;

	k = 0;
	s = ft_strdup(str);
	i = -1;
	while (s[++i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			c = s[i];
			s[i] = 'F';
			while (s[++i] != c)
				s[i] = 'a';
			s[i] = 'F';
		}
	}
	if ((i = check_bracket(s)) && i != 1 && strdelr(&s))
		return (i);
	while (1)
	{
		i = -1;
		while (s[++i])
			if (s[i] == '(')
				k = i;
		if (s[k] && s[k] == '(')
		{
			i = k;
			while (s[++i] && s[i] != ')')
				;
		}
		else
			break ;
		if (s[i] && s[i] == ')')
		{
			s[k] = 'A';
			s[i] = 'A';
		}
		else if (strdelr(&s))
			return (0);
	}
	i = -1;
	while (s[++i])
		if (s[i] == ')')
		{
			ft_strdel(&s);
			return (-2);
		}
	ft_strdel(&s);
	return(1);
}
