/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_zam_ravno.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 17:52:35 by mbrella           #+#    #+#             */
/*   Updated: 2020/05/02 13:20:11 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

t_lextoken		*do_zam_dop(t_lextoken *h, t_lextoken **first_token)
{
	t_lextoken	*dop;

	dop = h->next;
	del_one_node(h, first_token);
	return (dop);
}

t_lextoken		*do_zam_ravno(t_lextoken *h, t_lextoken **first_token)
{
	char		*tmp1;
	char		*tmp2;

	if (h != NULL && h->line != NULL && ft_strstr(h->line, "=") && ((h->next ==
	NULL || is_cmd_delim(get_op_type(h->next->line))) && h->prev == NULL))
	{
		tmp1 = ft_strsub(h->line, 0, ft_strstr(h->line, "=") - h->line);
		if (*(ft_strstr(h->line, "=") + 1) == '\0')
			tmp2 = ft_strdup("");
		else
			tmp2 = ft_strsub(h->line, ft_strstr(h->line, "=") -
			h->line + 1, ft_strlen(h->line));
		set_new_var(tmp1, tmp2, &globals()->g_all_var);
		ft_strdel(&tmp1);
		ft_strdel(&tmp2);
		return (do_zam_dop(h, first_token));
	}
	else if (h && h->line != NULL && ft_strstr(h->line, "=") && !h->prev)
		return (do_zam_dop(h, first_token));
	return (h ? h->next : NULL);
}
