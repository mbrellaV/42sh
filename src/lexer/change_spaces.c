/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 16:19:10 by mbrella           #+#    #+#             */
/*   Updated: 2020/05/12 19:15:22 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

char		*do_obr_zamena(char *line)
{
	int		i;
	int		d;
	char	*new;

	d = 0;
	if (line == NULL)
		return (ft_strnew(1));
	if (!(new = ft_memalloc(ft_strlen(line) * sizeof(char) + 1)))
		ft_error_q(2);
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] < 0)
			new[d++] = -1 * (line[i++]);
		else
			new[d++] = line[i++];
	}
	new[d] = '\0';
	ft_strdel(&line);
	return (new);
}

void		do_obr_zamena_slash(t_exectoken *tmp)
{
	int		i;

	i = 0;
	if (tmp == NULL)
		return ;
	while (tmp->file_args && tmp->file_args[i])
	{
		tmp->file_args[i] = do_obr_zamena(tmp->file_args[i]);
		i++;
	}
	i = 0;
	while (tmp->file_opt && tmp->file_opt[i])
	{
		tmp->file_opt[i] = do_obr_zamena(tmp->file_opt[i]);
		i++;
	}
	do_obr_zamena_slash(tmp->right);
	do_obr_zamena_slash(tmp->left);
}

char		*do_reverse_zamena(char *str)
{
	int		i;
	char	*newstr;
	char	*tmp;

	i = -1;
	if (!(newstr = ft_memalloc(ft_strlen(str) + 1000)))
		ft_error_q(15);
	while (str[++i] != '\0')
	{
		if (str[i] < 0)
		{
			tmp = ft_strdup("\\ ");
			tmp[1] = -1 * str[i];
		}
		else
		{
			tmp = ft_strdup(" ");
			tmp[0] = str[i];
		}
		ft_strcat(newstr, tmp);
		ft_strdel(&tmp);
	}
	ft_strdel(&str);
	return (newstr);
}
