/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 00:35:48 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/02 15:23:35 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

char				*get_hist_by_id(int id)
{
	int				i;
	char			*ret;
	t_memory		*last;

	if (id < 0)
		return (NULL);
	i = calc_h_size();
	last = globals()->g_memory_head;
	while (i != id)
	{
		if (last == NULL)
			return (NULL);
		i--;
		last = last->back;
	}
	if (last == NULL)
		return (NULL);
	ret = last->inp;
	return (ret);
}

void				delete_fc_command(void)
{
	t_memory		*to_del;

	to_del = globals()->g_memory_head;
	globals()->g_memory_head = globals()->g_memory_head->back;
	globals()->g_memory_head->next = NULL;
	free(to_del->inp);
	free(to_del);
}

static int			put_name_help(char ***split, int i)
{
	t_memory		*dop;

	ft_dprintf(globals()->fd[1], "%s\n", (*split)[i]);
	if ((*split)[i][0] != '\0')
	{
		if (!(dop = ft_memory(globals()->g_memory_head, (*split) + i))
			&& strdelr((*split) + i))
			return (0);
		globals()->g_memory_head = dop;
	}
	ft_do_zam_alias(&(*split)[i]);
	return (-1);
}

int					launch(char *str, int put_name)
{
	register int	i;
	char			**split;
	t_exectoken		*start_token;

	i = -1;
	split = ft_strsplit1(str, '\n');
	while (split[++i])
	{
		if (put_name)
			if (!put_name_help(&split, i))
				return (-1);
		if ((start_token = all_parse(split[i])) == NULL)
			return (!ft_distruct_tree(start_token));
		if (ft_main_what(start_token) == -1)
			return (-1);
		ft_distruct_tree(start_token);
	}
	ft_free_split(split);
	return (0);
}
