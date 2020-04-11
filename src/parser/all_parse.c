/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 11:45:44 by plettie           #+#    #+#             */
/*   Updated: 2020/02/06 11:45:52 by plettie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

t_exectoken		*all_parse(char *cmd)
{
	t_lextoken	*tmp;
	t_exectoken	*extmp;
	t_dop_str	*t;

	t = NULL;
	if (*cmd == '\0')
		return (NULL);
	ft_change_all_sc(cmd);
	if (!(tmp = do_lexer(cmd)))
		return (NULL);
	tmp = do_zam_bax_and_hist_full(tmp);
	if (tmp == NULL)
		return (NULL);
	if (check_all_errors(tmp) != 1)
	{
		ft_error(5, "\\n");
		ft_distr_lex(tmp);
		return (NULL);
	}
	free(t);
	extmp = do_parser(tmp);
	do_zamena_opt_tokens(extmp);
	do_obr_zamena_slash(extmp);
	ft_distr_lex(tmp);
	return (extmp);
}
