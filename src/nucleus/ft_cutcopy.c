/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cutcopy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 20:52:13 by qmartina          #+#    #+#             */
/*   Updated: 2019/12/09 20:52:15 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_cut(char **input, t_flag **flag, int **len)
{
	free(g_cp);
	g_cp = ft_strdup(*input);
	free(*input);
	*input = ft_strnew(1);
	ft_cleanstr((*flag)->i + 1 + **len);
	**len = ft_main_norm((*flag)->mod);
	**flag = (t_flag){0, 0, (*flag)->rt, (*flag)->sum,
							(*flag)->a, (*flag)->mod};
}

void	ft_putcut(char **input, t_flag **flag, int **len)
{
	char	*tmp;

	tmp = *input;
	*input = ft_strjoin_i(tmp, g_cp, (*flag)->i, (*flag)->max);
	(*flag)->i += ft_strlen(g_cp);
	(*flag)->max = ft_strlen(*input);
	free(tmp);
	ft_cleanstr((*flag)->i + 1 + **len);
	**len = ft_main_norm((*flag)->mod);
	ft_putstr_fd(*input, 2);
	ft_setcursor((*flag)->i, (*flag)->max);
}

void	ft_do_delch(t_flag **flag, char **input, int **len)
{
	char	*tmp;

	if ((*flag)->i > 0)
	{
		tmp = *input;
		(*flag)->i--;
		*input = ft_strdelch(tmp, (*flag)->i, (*flag)->max);
		free(tmp);
		(*flag)->max = ft_strlen(*input);
		ft_cleanstr((*flag)->i + 1 + **len);
		**len = ft_main_norm((*flag)->mod);
		ft_putstr_fd(*input, 2);
		ft_setcursor((*flag)->i, (*flag)->max);
	}
}

char	*ft_cut_copy(char *input, t_flag *flag,
						int *len, int buf)
{
	char	*tmp;

	if (buf == 25)
		ft_putcut(&input, &flag, &len);
	else if (buf == 23)
	{
		free(g_cp);
		g_cp = ft_strndup(input, flag->i);
		tmp = input;
		input = ft_strdup(&tmp[flag->i]);
		free(tmp);
		ft_cleanstr(flag->i + 1 + *len);
		*len = ft_main_norm(flag->mod);
		*flag = (t_flag){0, ft_strlen(input), flag->rt, flag->sum,
											flag->a, flag->mod};
		ft_putstr_fd(input, 2);
		ft_setcursor(0, flag->max);
	}
	else if (buf == 21)
		ft_cut(&input, &flag, &len);
	else if (buf == 127 && flag->i > 0)
		ft_do_delch(&flag, &input, &len);
	return (input);
}

void	ft_do_copy(char *input, t_flag *flag)
{
	if (flag->sum == 27)
		flag->a = 1;
	else if (flag->sum == 119)
	{
		free(g_cp);
		g_cp = ft_strdup(input);
		flag->a = 0;
	}
}
