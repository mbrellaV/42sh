/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_lexer_struct.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 18:53:05 by wstygg            #+#    #+#             */
/*   Updated: 2020/06/03 20:13:49 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

t_dop_str		*cr_dop_str(char **line1)
{
	t_dop_str	*tmp;
	char		*line;

	line = *line1;
	if (line == NULL)
		return (NULL);
	if (line[0] == '\0')
		return (NULL);
	if (!(tmp = ft_memalloc(sizeof(t_dop_str))))
		ft_error_q(2);
	tmp->tmp_c = NULL;
	tmp->dop_c = 0;
	tmp->d_c = 0;
	tmp->i_c = 0;
	tmp->doptail_c = NULL;
	tmp->tail_c = NULL;
	return (tmp);
}
