/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 18:54:17 by wstygg            #+#    #+#             */
/*   Updated: 2020/04/16 16:47:13 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int				check_opt_tokens(t_lextoken *tmp)
{
	while (tmp != NULL)
	{
		if (tmp->next && is_cmd_redirect(get_op_type(tmp->line)) &&
			is_cmd_redirect(get_op_type(tmp->next->line)))
		{
			ft_error(5, tmp->line);
			return (-1);
		}
		if (is_cmd_redirect(get_op_type(tmp->line)) &&
				tmp->next->line == NULL)
		{
			ft_error(5, tmp->line);
			return (-1);
		}
		if (tmp->next && is_cmd_redirect(get_op_type(tmp->line)) &&
			get_op_type(tmp->next->line) >= 0)
		{
			ft_error(5, tmp->line);
			return (-1);
		}
		tmp = tmp->next;
	}
	return (1);
}

t_exectoken		*all_parse(char *cmd)
{
	t_lextoken	*tmp;
	t_exectoken	*extmp;
	t_lextoken	*dop_tmp;

	if (*cmd == '\0')
		return (NULL);
	ft_change_all_sc(cmd);
	if (!(tmp = do_lexer(cmd)))
		return (NULL);
	dop_tmp = tmp;
	if (!(tmp = do_zam_bax_and_hist_full(tmp)) && ft_distr_lex(dop_tmp))
		return (NULL);
	if (check_all_errors(tmp) != 1)
	{
		ft_error(5, "\\n");
		ft_distr_lex(tmp);
		return (NULL);
	}
	if (check_opt_tokens(tmp) == -1 && ft_distr_lex(tmp))
		return (NULL);
	extmp = do_parser(tmp);
	do_zamena_opt_tokens(extmp);
	do_obr_zamena_slash(extmp);
	ft_distr_lex(tmp);
	return (extmp);
}
