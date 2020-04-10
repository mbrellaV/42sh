/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 16:19:10 by mbrella           #+#    #+#             */
/*   Updated: 2020/01/25 16:19:12 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

char				*do_obr_zamena(char *line)
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

void			do_obr_zamena_slash(t_exectoken *tmp)
{
	int i;

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

char				*do_zamena_slash(char *line)
{
	int		i;
	char	*tmp;
	char	*new;
	int		size;

	i = 0;
	if (line == NULL)
		return (ft_strnew(130000));
	if (!(new = ft_memalloc(130000)))
		ft_error_q(2);
	while (i < ft_strlen(line) && line[i] != '\0')
	{
		if (ispar(line[i]))
		{
			size = c_size(&line[i], line[i]);
			if (size == -2)
				size = 2;
			tmp = ft_strsub(line, i, size + 2);
			ft_strcat(new, tmp);
			i += size + 1;
			ft_strdel(&tmp);
			//exit(0);
		}
		else if (line[i] == '\\' && line[i + 1] != '\0')
		{
			tmp = ft_strdup(" ");
			tmp[0] = -1 * line[i + 1];
			ft_strcat(new, tmp);
			ft_strdel(&tmp);
			i++;
		}
		else
		{
			tmp = ft_strdup(" ");
			tmp[0] = line[i];
			ft_strcat(new, tmp);
			ft_strdel(&tmp);
		}
		i++;
	}
	//dprintf(2, "\nsas: |%s|\n", new);
	return (new);
}
